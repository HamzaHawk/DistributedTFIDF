#ifndef SERIALIZE_UTILITY_HPP
#define SERIALIZE_UTILITY_HPP

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>

using std::map;
using std::string;



char *map_serialize(map <string, int>& hash_map, int *out_size);
map<string, int>* map_deserialize(char *buf);

#endif