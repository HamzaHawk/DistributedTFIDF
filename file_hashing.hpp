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

std::map<std::string, int> countWordsInFile(std::string filename);
std::map<std::string, int> countDocumentsContainingWords(std::vector< std::map<std::string, int> >& wordCounts, std::set<std::string>& listOfWords);

#endif
