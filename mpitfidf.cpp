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

   //divide up files
   if (me == MASTER) {
      printf("Divided files...\n");
   }
   
   for (i = 0; i < numFiles; i++) {
      /* if index % numPRocs-1 +1 to omit master
       */
      if ((i%(numProcs-1) + 1) == me) {
         //calculate tf for each document i

         //calculate max for each document 
         
         //send to master
      }
   }
   
   
   if (me == MASTER) {
      
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
