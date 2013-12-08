#ifndef CALCULATE_TFIDF_HPP
#define CALCULATE_TFIDF_HPP

#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>

using std::map;
using std::string;
using std::log10;
using std::ofstream;

void calculateTFIDFAndOutput(map<string, map<string, int> >& wordFrequencies, map<string, int>& documentFrequencies);
#endif