/*
 * max_term_finder.cpp
 * 
 * For every word, it finds the max frequency across all documents.
 */

#include <map>
#include <string>
#include <vector>
#include <set>
#include <climits>
#include <iostream>
#include <typeinfo>
#include <utility>
#include "file_hashing.hpp"
#include "serialize_utility.hpp"

using std::map;
using std::string;
using std::vector;
using std::set;
using std::cout;
using std::pair;

map<string, int>* max_term_finder(map < string, map <string, int> > & wordCounts, set<string>& words) 
{
    map<string, int> *wordMaxes = new map<string, int>();
    set<string>::iterator word_it;

    for (word_it = words.begin(); word_it != words.end(); ++word_it) {
        string word = *word_it;

        int maxCount = -1;
        for (map< string, map <string, int> >::iterator counts_it = wordCounts.begin(); counts_it != wordCounts.end(); ++counts_it) {

            map <string, int> docCounts = counts_it->second;
            maxCount = std::max(maxCount, docCounts[word]);
        }

        wordMaxes->insert(pair<string,int>(word, maxCount));
    }

    cout << "Maxes:\n";
    typedef map<string, int>::iterator it_type;
    for(it_type iterator = (*wordMaxes).begin(); iterator != (*wordMaxes).end(); iterator++) {
        cout << iterator->first << ": " << iterator->second << "\n";
    }

    return wordMaxes;
}

/*
int main() {
   using namespace std;
   map<string, int> wordCount = countWordsInFile("file_hashing.cpp");
   map<string, int> otherWordCount = countWordsInFile("file_hashing.hpp");
   map< string, map<string,int> > perFileWordCounts;
   perFileWordCounts["file_hashing.cpp"] = wordCount;
   perFileWordCounts["file_hashing.hpp"] = otherWordCount;
   set<string> listOfWords;
   countDocumentsContainingWords(perFileWordCounts, listOfWords);

   map<string, int> *wordMaxes = max_term_finder(perFileWordCounts, listOfWords);

   int size;
   char *buf = map_serialize(*wordMaxes, &size);
   map<string, int> *wordMaxes2 = map_deserialize(buf);

   cout << "Element Size: " << size << "\n";
   cout << "Hash Table Elements: " << "\n";
   typedef map<string, int>::iterator it_type;
    for(it_type iterator = (*wordMaxes2).begin(); iterator != (*wordMaxes2).end(); iterator++) {
        cout << iterator->first << ": " << iterator->second << "\n";
    }
}
*/

