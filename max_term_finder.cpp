/*
 * max_term_finder.c
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

using std::map;
using std::string;
using std::vector;
using std::set;
using std::cout;
using std::pair;

map<string, int>* max_term_finder(vector< map <string, int> >& wordCounts, set<string>& words) 
{
    map<string, int> *wordMaxes = new map<string, int>();
    set<string>::iterator word_it;

    for (word_it = words.begin(); word_it != words.end(); ++word_it) {
        string word = *word_it;

        int maxCount = -1;
        for (vector< map <string, int> >::iterator counts_it = wordCounts.begin(); counts_it != wordCounts.end(); ++counts_it) {

            map <string, int> docCounts = *counts_it;
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

int main() {
   using namespace std;
   map<string, int> wordCount = countWordsInFile("file_hashing.cpp");
   map<string, int> otherWordCount = countWordsInFile("file_hashing.hpp");
   vector< map<string,int> > perFileWordCounts;
   perFileWordCounts.push_back(wordCount);
   perFileWordCounts.push_back(otherWordCount);
   set<string> listOfWords;
   countDocumentsContainingWords(perFileWordCounts, listOfWords);

   max_term_finder(perFileWordCounts, listOfWords);
}