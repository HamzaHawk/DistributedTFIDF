#include "calculate_tfidf.hpp"

void calculateTFIDFAndOutput(map<string, map<string, int> >& wordFrequencies, map<string, int>& documentFrequencies, int number_of_documents) {
    typedef map<string, map<string, int> >::iterator map_map_iterator;
    typedef map<string, int>::iterator map_iterator;

    // For each file
    for (map_map_iterator mm_iter = wordFrequencies.begin(); mm_iter != wordFrequencies.end(); ++mm_iter) {
        string filename = mm_iter->first;
        ofstream output_file;
        output_file.open(filename + "_tfidf.out", std::ios::out);
        //For each word in the file
        for(map_iterator m_iter = (mm_iter->second).begin(); m_iter != (mm_iter->second).end(); ++m_iter) {
            string word = m_iter->first;
            double tf = (double) (mm_iter->second)[word];
            double idf = log10((double)number_of_documents / (double)documentFrequencies[word]);
            double tfidf = tf / idf;
            output_file << word << "," << tfidf << endl;
        }
        output_file.close();
    }
    
}