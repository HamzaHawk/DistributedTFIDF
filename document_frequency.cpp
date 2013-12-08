#include <map>
#include <vector>
#include <string>

using std::map;
using std::string;
using std::vector;

map<string, int> * reduceDocumentFrequencies(vector< map<string, int> >& perNodeDocumentFrequencies) {
    map<string, int> *masterDocumentFrequencies = new map<string, int>();

    for (vector< map<string, int> >::iterator it = perNodeDocumentFrequencies.begin();
             it != perNodeDocumentFrequencies.end(); ++it) {
        for(map<string, int>::iterator mapIter = (*it).begin(); mapIter != (*it).end(); ++mapIter) {
            (*masterDocumentFrequencies)[mapIter->first] += mapIter->second;
        }
    }
    return masterDocumentFrequencies;
}

