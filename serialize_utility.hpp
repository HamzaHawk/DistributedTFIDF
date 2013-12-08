#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

using std::map;
using std::string;

#ifndef MAX_TERM_FINDER
#define MAX_TERM_FINDER

char *map_serialize(map <string, int>& hash_map, int *out_size);
map<string, int>* map_deserialize(char *buf);

#endif