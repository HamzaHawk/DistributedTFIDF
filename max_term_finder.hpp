/*
 * max_term_finder.h
 * 
 * For every word, it finds the max frequency across all documents.
 */

#ifndef MAX_TERM_FINDER
#define MAX_TERM_FINDER

map<string, int>* max_term_finder(map < string, map <string, int> > & wordCounts, set<string>& words);
#endif
