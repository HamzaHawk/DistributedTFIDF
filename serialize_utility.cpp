/*
 * serialize_utility.cpp
 * 
 * For every word, it finds the max frequency across all documents.
 */

#include "serialize_utility.hpp"


char *map_serialize(map <string, int>& hash_map, int *out_size)
{
    int str_sizes = 0;
    int buf_size = 0;

    // Iterate through map to count all string lengths
    typedef map<string, int>::iterator it_type;
    for(it_type iterator = hash_map.begin(); iterator != hash_map.end(); iterator++) {

        string word = iterator->first;
        str_sizes += word.length();
    }

    // Buffer size = all string lengths + NULLs + counts + header int
    buf_size = str_sizes + (hash_map.size() * sizeof(int)) + hash_map.size();
    buf_size += sizeof(int);
    char *buf = (char*)calloc(1, buf_size);

    // Add the elem size (header) to buf, advance ptr
    *((int*)buf) = hash_map.size();
    char *buf_ptr = buf+sizeof(int);

    // Add all strings and counts
    for(it_type iterator = hash_map.begin(); iterator != hash_map.end(); iterator++) {

        string word = iterator->first;
        int count = iterator->second;

        memcpy(buf_ptr, word.c_str(), word.length());
        buf_ptr += word.length();
        *buf_ptr = 0;
        buf_ptr++;
        *((int*)buf_ptr) = count;
        buf_ptr += sizeof(int);
    }

    // for (int i = 0; i < buf_size; i++) {
    //     printf("item %d) %x.\n", i, buf[i]);
    // }

    // Set out_ptr to size of buffer
    *out_size = buf_size;
    return buf;
}


map<string, int>* map_deserialize(char *buf)
{
    // Get header size (num elements), advance ptr
    int elem_size = *((int*)buf);
    char *buf_ptr = buf+sizeof(int);

    map<string, int> *ret_map = new map<string, int>();
    for (int i = 0; i < elem_size; i++) {
        // Create string, advance ptr
        string str(buf_ptr);
        buf_ptr += str.length() + 1;

        // Get count, advance ptr
        int count = *((int*)buf_ptr);
        buf_ptr += sizeof(int);

        // Set entry in map
        (*ret_map)[str] = count;
    }

    return ret_map;
}

