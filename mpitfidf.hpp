/*
 *
 */
#ifndef MPITFIDF_HPP
#define MPITFIDF_HPP
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>

#define MASTER 0
#define SUCCESS 0
#define FAILURE 1


#define MAX_TF_TYPE 1000
#define DOC_F_TYPE 1001

#include "file_hashing.hpp"
#include "max_term_finder.hpp"
#include "serialize_utility.hpp"
#include "document_frequency.hpp"
#include "calculate_tfidf.hpp"

using std::map;
using std::vector;
using std::set;
using std::string;

#endif
