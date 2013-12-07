#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

struct letter_only: std::ctype<char> 
{
    letter_only(): std::ctype<char>(get_table()) {}

    static std::ctype_base::mask const* get_table()
    {
        static std::vector<std::ctype_base::mask> 
            rc(std::ctype<char>::table_size,std::ctype_base::space);

        std::fill(&rc['A'], &rc['z'+1], std::ctype_base::alpha);
        return &rc[0];
    }
};

std::map<std::string, int> countWordsInFile(std::string filename) {
     using namespace std;
     map<string, int> wordCount;
     ifstream input;
     input.imbue(std::locale(std::locale(), new letter_only())); //enable reading only letters!
     input.open(filename);
     std::string word;
     while(input >> word)
     {
         ++wordCount[word];
     }
     /* Print code for debugging purposes.
     for (std::map<std::string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it)
     {
           cout << it->first <<" : "<< it->second << endl;
     }
     */
     return wordCount;
}

std::map<string, int> countDocumentsContainingWords(std::vector< std::map<std::string, int> > wordCounts) {
   using namespace std;
   map<string, int> documentCount;
   for(vector< map<string, int> >::iterator it = wordCounts.begin(); it != wordCounts.end(); ++it) {
      for(map<string,int>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter) {
         ++documentCount[iter->first];
      }
   }

   /* Print code for debugging purposes.
   for(map<string, int>::iterator it = documentCount.begin();it != documentCount.end(); ++it) {
      cout << it->first << " : " << it->second << endl;
   }
   */
   return 
}

int main() {
   using namespace std;
   map<string, int> wordCount = countWordsInFile("file_hashing.cpp");
   map<string, int> otherWordCount = countWordsInFile("file_hashing.hpp");
   vector< map<string,int> > perFileWordCounts;
   perFileWordCounts.push_back(wordCount);
   perFileWordCounts.push_back(otherWordCount);
   countDocumentsContainingWords(perFileWordCounts);
}




