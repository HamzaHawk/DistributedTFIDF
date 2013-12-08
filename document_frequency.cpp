#include <map>
#include <vector>
#include <string>

using std::map;
using std::string;
using std::vector;

map<string, int> * reduceDocumentFrequencies(map<string, map<string, int> >& perNodeDocumentFrequencies) {
    map<string, int> *masterDocumentFrequencies = new map<string, int>();

    for (map<string, map<string, int> >::iterator it = perNodeDocumentFrequencies.begin();
             it != perNodeDocumentFrequencies.end(); ++it) {
        for(map<string, int>::iterator mapIter = (it->second).begin(); mapIter != (it->second).end(); ++mapIter) {
            (*masterDocumentFrequencies)[mapIter->first] += mapIter->second;
        }
    }
    return masterDocumentFrequencies;
}



