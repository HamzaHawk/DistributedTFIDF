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

void calculateTFIDFAndOutput(map<string, map<string, int> >& wordFrequencies, map<string, int>& documentFrequencies, int number_of_documents);

map<string, map<string, double> > normalizeTermFrequencies(map<string, map<string, int> >& termFrequencies);

#endif