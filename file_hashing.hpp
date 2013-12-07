#ifndef FILE_HASHING_HPP
#define FILE_HASHING_HPP
std::map<std::string, int> countWordsInFile(std::string filename);
std::map<std::string, int> countDocumentsContainingWords(std::vector< std::map<std::string, int> >& wordCounts, std::set<std::string>& listOfWords)
#endif
