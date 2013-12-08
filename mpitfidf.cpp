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


   map <string, map <string, int> > fileCounts;


   if (me != MASTER) {
      for (i = 0; i < numFiles; i++) {
         // if index % numPRocs-1 +1 is equal to rank, process doc (omits master)
         if ((i%(numProcs-1) + 1) == me) {
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

      //send doc counts ot master
      COMM_WORLD.Send(&doc_size, 1, MPI_INT, MASTER, me);
      COMM_WORLD.Send(doc_buf, doc_size, MPI_BYTE,
                   MASTER, DOC_F_TYPE);

   }

   int global_max_size;   
   char *global_max_buf;

   int global_doc_size;   
   char *global_doc_buf;
   
   if (me == MASTER) {
      map <string, map <string, int> > doc_buffer_map;
      int doc_buf_size;
      
      int rank;
      
      for (i = 0; i < numProcs-1; i++) {
         //get document counts from each node
         COMM_WORLD.Recv(&doc_buf_size, 1, MPI_INT, MPI_ANY_SOURCE, rank);
         int doc_type;

         //make rank a string
         std::stringstream ss;
         ss << rank;
         std::string temp = ss.str();
         
         char *doc_buffer = (char *)malloc(doc_buf_size);         
         COMM_WORLD.Recv(doc_buffer, doc_buf_size, MPI_BYTE, rank, doc_type);
         
         //deserialize
         map <string, int> *doc_map = map_deserialize(doc_buffer);

         //add to vector
         doc_buffer_map[temp] = *doc_map;
      }
      
      //create global doc map
      map <string, int> *global_doc_map = reduceDocumentFrequencies(doc_buffer_map);

      global_doc_buf = map_serialize(*global_doc_map, &global_doc_size);
      
   } 
   //broadcase global_doc_size
   COMM_WORLD.Bcast(&global_doc_size, 1, MPI_INT, me);
   
   //malloc space for buffers
   if (me != MASTER) {
      global_doc_buf = (char *)malloc(global_doc_size);
   }

   //broadcast(global_doc_buf);
   COMM_WORLD.Bcast(&global_doc_buf, global_doc_size, MPI_BYTE, me);

   if (me == MASTER) {
      printf("Calculating and outputting...");
   }

   if (me != MASTER) {
      //deserialize doc_buf
      map <string, int> *global_doc_map = map_deserialize(global_doc_buf);

      //tfidf
      calculateTFIDFAndOutput(fileCounts, *global_doc_map, numFiles);
      
   }
   
   if (me == MASTER) {
      printf("Done.");
   }

   Finalize();
   return 0;
   
}
