#include "calculate_tfidf.hpp"

#define ALPHA          0.4

void calculateTFIDFAndOutput(map<string, map<string, int> >& wordFrequencies, map<string, int>& documentFrequencies, int number_of_documents) {
    typedef map<string, map<string, double> >::iterator map_map_iterator;
    typedef map<string, double>::iterator map_iterator;

    map<string, map<string, double> > normalizedWordFreqs = normalizeTermFrequencies(wordFrequencies);

    // For each file
    for (map_map_iterator mm_iter = normalizedWordFreqs.begin(); mm_iter != normalizedWordFreqs.end(); ++mm_iter) {
        string filename = mm_iter->first;
        ofstream output_file;
        string newFname = "data/output/" + filename + "_tfidf.out";
        output_file.open(newFname.c_str(), std::ios::out);
        //For each word in the file
        for(map_iterator m_iter = (mm_iter->second).begin(); m_iter != (mm_iter->second).end(); ++m_iter) {
            string word = m_iter->first;
            double tf = (mm_iter->second)[word];
            double idf = log10(((double)number_of_documents) / (((double)documentFrequencies[word]) ) );
            double tfidf = tf * idf;
            output_file << word << "," << tfidf << "\n";
        }
        output_file.close();
    }
}


map<string, map<string, double> > normalizeTermFrequencies(map<string, map<string, int> >& termFrequencies)
{
    typedef map<string, map<string, int> >::iterator map_map_iterator;
    typedef map<string, int>::iterator map_iterator;
    typedef map<string, double>::iterator map_iterator_d;

    map<string, map<string, double> > normedTermFreqsAll;
    for (map_map_iterator mm_iter = termFrequencies.begin(); mm_iter != termFrequencies.end(); ++mm_iter) {
        int max = 0;

        for(map_iterator m_iter = (mm_iter->second).begin(); m_iter != (mm_iter->second).end(); ++m_iter) {
            string word = m_iter->first;
            max = std::max(max, (mm_iter->second)[word]);
        }

        map<string, double> normedTermFreqs;
        for(map_iterator m_iter = (mm_iter->second).begin(); m_iter != (mm_iter->second).end(); ++m_iter) {
            string word = m_iter->first;
            double unnorm_freq = mm_iter->second[word];
            normedTermFreqs[word] = ALPHA + ((1-ALPHA) * (unnorm_freq / max));
        }
        normedTermFreqsAll[mm_iter->first] = normedTermFreqs;
    }

    return normedTermFreqsAll;
}