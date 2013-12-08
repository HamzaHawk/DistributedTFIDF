#ifndef FILE_HASHING_HPP
#define FILE_HASHING_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>

using std::map;
using std::vector;
using std::set;
using std::string;

map<string, int> countWordsInFile(string filename);
map<string, int> countDocumentsContainingWords(map<string, map<string, int> >& wordCounts);

#endif
