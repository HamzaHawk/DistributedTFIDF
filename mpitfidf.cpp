/*
 *
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
      
   for (i = 0; i < argc-1; i++) {
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

   //get doc_count from each file
   
   //combine doc counts from each node

   //get tf_max from each node


   //combine tf_max into global max vectors


   //IN CHILD NODE
   
   //calc tf for each doc

   //calc max for each word

   //send doc count to master

   //send max to doc count

   //for d in D
   //for w in d
   //calc normalized tfidf

   //output
   





   Finalize();
   return 0;
   
}
