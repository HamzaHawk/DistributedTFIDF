#include "file_hashing.hpp"

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

map<string, int> countWordsInFile(string filename) {
     using namespace std;
     map<string, int> wordCount;
     ifstream input;
     input.imbue(std::locale(std::locale(), new letter_only())); //enable reading only letters!
     input.open(filename.c_str());
     string word;
     while(input >> word)
     {
         ++wordCount[word];
     }
      // Print code for debugging purposes.
     // for (std::map<std::string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it)
     // {
     //       cout << it->first <<" : "<< it->second << endl;
     // }
     
     return wordCount;
}

map<string, int> countDocumentsContainingWords(map<string, map<string, int> >& wordCounts, set<string>& listOfWords) {
   using namespace std;
   map<string, int> documentCount;
   for(map<string, map<string, int> >::iterator it = wordCounts.begin(); it != wordCounts.end(); ++it) {
      for(map<string,int>::iterator iter = (it->second).begin(); iter != (it->second).end(); ++iter) {
         ++documentCount[iter->first];
         listOfWords.insert(iter->first);
      }
   }

    // Print code for debugging purposes.
   // for(map<string, int>::iterator it = documentCount.begin();it != documentCount.end(); ++it) {
   //    cout << it->first << " : " << it->second << endl;
   // }
   
   return documentCount;
}

void generateVocabulary(map<string, map<string, int> >& wordCounts, set<string>& listOfWords) {
   using namespace std;
   map<string, int> documentCount;
   for(map<string, map<string, int> >::iterator it = wordCounts.begin(); it != wordCounts.end(); ++it) {
      for(map<string,int>::iterator iter = (it->second).begin(); iter != (it->second).end(); ++iter) {
         listOfWords.insert(iter->first);
      }
   }
   return;
}

/*
int main() {
   using namespace std;
   map<string, int> wordCount = countWordsInFile("file_hashing.cpp");
   map<string, int> otherWordCount = countWordsInFile("file_hashing.hpp");
   vector< map<string,int> > perFileWordCounts;
   perFileWordCounts.push_back(wordCount);
   perFileWordCounts.push_back(otherWordCount);
   set<string> listOfWords;
   countDocumentsContainingWords(perFileWordCounts, listOfWords);
}
*/




