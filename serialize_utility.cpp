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

    typedef map<string, int>::iterator it_type;
    for(it_type iterator = hash_map.begin(); iterator != hash_map.end(); iterator++) {

        string word = iterator->first;
        str_sizes += word.length();
    }

    // buf_size = length of all strings + length of all counts + all NULLs
    // + an extra int in the beginning
    buf_size = str_sizes + (hash_map.size() * sizeof(int)) + hash_map.size();
    buf_size += sizeof(int);
    char *buf = (char*)calloc(1, buf_size);

    // add the elem size to buf
    *((int*)buf) = hash_map.size();
    char *buf_ptr = buf+sizeof(int);
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

    *out_size = buf_size;
    return buf;
}


map<string, int>* map_deserialize(char *buf)
{
    int elem_size = *((int*)buf);
    map<string, int> *ret_map = new map<string, int>();

    char *buf_ptr = buf+sizeof(int);
    for (int i = 0; i < elem_size; i++) {
        string str(buf_ptr);
        buf_ptr += str.length() + 1;
        int count = *((int*)buf_ptr);
        buf_ptr += sizeof(int);

        (*ret_map)[str] = count;
    }

    return ret_map;
}

