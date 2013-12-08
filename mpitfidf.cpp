/*
 * Distributed TF*IDF calculation using OpenMPI.
 */

#include "mpitfidf.hpp"
#include "file_hashing.hpp"
#include "max_term_finder.hpp"

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

   //divide up files
   if (me == MASTER) {
      printf("Divided files...\n");
   }

   if (me != MASTER) {
      vector <map <string, int> > fileCounts;
      
      for (i = 0; i < numFiles; i++) {
         // if index % numPRocs-1 +1 is equal to rank, process doc (omits master)
         if ((i%(numProcs-1) + 1) == me) {
            //read document calculate tf for each document i
            map<string, int> wordCount = countWordsInFile(files[i]);
            fileCounts.push_back(wordCount);
         }
      }
      //call count documents with vector
      set<string> listOfWords;
      countDocumentsContainingWords(fileCounts, listOfWords);
            
      //calculate max for each document 
      max_term_finder(fileCounts, listOfWords);
       
      //serialize
      int max_size;
      int doc_size;

      //TODO ADD CALL HERE
      char *max_buf;
      char *doc_buf;

      //send to max master
      COMM_WORLD.send(&max_count, 1, MPI_INT, MASTER, me);
      COMM_WORLD.send(max_buf, &max_count, MPI_BYTE,
                      MASTER, MAX_TF_TYPE);
      
      //send doc counts ot master
      COMM_WORLD.send(&doc_buf, 1, MPI_INT, MASTER, me);
      COMM_WORLD.send(doc_size, &doc_size, MPI_BYTE,
                   MASTER, DOC_F_TYPE);
   }
   
   if (me == MASTER) {
      vector <map <string, int> > buffer;
      int data_sizes[numProcs-1];
      int buf;
      int rank;
            
      for (i = 0; i < numProcs-1; i++) {
         //receive size from child -- tag is rank of node
         COMM_WORLD.recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, rank);
         data_sizes[rank] = buf;
      }

      for (i = 0; i < numProcs-1; i++) {
         
      }
      
      
      //get doc_count from each file
   
      //combine doc counts from each node

      //get tf_max from each node

      //combine tf_max into global max vectors
   } 

   if (me != MASTER) {
      //for d in D
      //for w in d
      //calc normalized tfidf

      //output
   }

   Finalize();
   return 0;
   
}
