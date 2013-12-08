/*
 * Distributed TF*IDF calculation using OpenMPI.
 */

#include "mpitfidf.hpp"
#include "file_hashing.hpp"
#include "max_term_finder.hpp"

using namespace MPI;
using std::map;
using std::vector;
using std::set;
using std::string;

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

      //send to master
      
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
