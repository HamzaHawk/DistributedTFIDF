/*
 * Distributed TF*IDF calculation using OpenMPI.
 */

#include "mpitfidf.hpp"

using namespace MPI;

int main(int argc, char *argv[]) 
{   
   if (argc < 2) {
      printf("Usage: mpitfidf <file1> [.... <fileN>]\n");
      return 1;
   }

   int numProcs;
   int me;
   int numFiles = argc-1;
   
   //create array of files
   char *files[argc-1];
   int i;
      
   for (i = 0; i < numFiles; i++) {
      files[i] = argv[i+1];
   }

   
   //parse arguments
   Init(argc,argv);
   me = COMM_WORLD.Get_rank();
   numProcs = COMM_WORLD.Get_size();   

   if (me == MASTER) {
      printf("Initialized...\n");
   }

   if (me == MASTER) {
      printf("numFiles: %d\n", numFiles);
   }

   map <string, map <string, int> > fileCounts;


   if (me != MASTER) {
      for (i = 0; i < numFiles; i++) {
         // if index % numPRocs-1 +1 is equal to rank, process doc (omits master)
         if ((i%(numProcs-1) + 1) == me) {
//            printf("My Rank: %d, my files: %s\n", me, files[i]);
            
            //read document calculate tf for each document i
            map<string, int> wordCount = countWordsInFile(files[i]);
            fileCounts[files[i]]=wordCount;
         }
      }

      //call count documents with vector
      map <string, int> docCounts = countDocumentsContainingWords(fileCounts);
            
      //serialize
      int doc_size;
      char *doc_buf = map_serialize(docCounts, &doc_size);
      //    printf("Sending document counts from %d\n", me);
      

      int doc_size_buf[2] = {doc_size, me};
      
      
      //send doc counts ot master
      COMM_WORLD.Send(doc_size_buf, 2, MPI_INT, MASTER, 0);
      COMM_WORLD.Send(doc_buf, doc_size, MPI_BYTE,
                   MASTER, DOC_F_TYPE);
   }

   int global_doc_size;   
   char *global_doc_buf;
   
   if (me == MASTER) {
      map <string, map <string, int> > doc_buffer_map;
      int doc_buf_size[2];
      
      int rank;
      printf("About to receive from master...\n");
      
      for (i = 0; i < numProcs-1; i++) {
         //get document counts from each node
         COMM_WORLD.Recv(doc_buf_size, 2, MPI_INT, MPI_ANY_SOURCE, 0);
         int doc_type;

         rank = doc_buf_size[1];
         //make rank a string
         std::stringstream ss;
         ss << rank;
         std::string temp = ss.str();
         
         char doc_buffer[doc_buf_size[0]];         
         COMM_WORLD.Recv(doc_buffer, doc_buf_size[0], MPI_BYTE, rank, DOC_F_TYPE);
         
         //deserialize
         map <string, int> *doc_map = map_deserialize(doc_buffer);

         //add to vector
         doc_buffer_map[temp] = *doc_map;
      }
      
      //create global doc map
      map <string, int> *global_doc_map = reduceDocumentFrequencies(doc_buffer_map);

      global_doc_buf = map_serialize(*global_doc_map, &global_doc_size);
      
   } 
   
   if (me == MASTER) {
      printf("Broadcasting....\n");
   }
   
   //broadcase global_doc_size
   COMM_WORLD.Bcast(&global_doc_size, 1, MPI_INT, MASTER);
   
   //malloc space for buffers
   if (me != MASTER) {
      global_doc_buf = new char[global_doc_size];
   }

   //broadcast(global_doc_buf);
   COMM_WORLD.Bcast(global_doc_buf, global_doc_size, MPI_BYTE, MASTER);

   if (me == MASTER) {
      printf("Calculating and outputting...\n");
   }

   if (me != MASTER) {
      //deserialize doc_buf
      map <string, int> *global_doc_map = map_deserialize(global_doc_buf);

      //tfidf
      calculateTFIDFAndOutput(fileCounts, *global_doc_map, numFiles);
      
   }
   
   if (me == MASTER) {
      printf("Done.\n");
   }

   Finalize();
   return 0;
}
