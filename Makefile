CC=mpic++

OBJ_FLAGS=-O -c -g 
LIBS=-lmpi

all: mpitfidf
	$(CC) mpitfidf.o file_hashing.o max_term_finder.o document_frequency.o serialize_utility.o calculate_tfidf.o -o mpitfidf

mpitfidf: mpitfidf.cpp file_hashing.cpp max_term_finder.cpp document_frequency.cpp serialize_utility.cpp calculate_tfidf.cpp
	$(CC) $(OBJ_FLAGS) mpitfidf.cpp file_hashing.cpp max_term_finder.cpp document_frequency.cpp serialize_utility.cpp calculate_tfidf.cpp

clean:
	rm -rf mpitfidf *.o

test3nodes:
	time -p mpirun -n 3 --hostfile hostfile -mca btl_tcp_if_include eth0 ./mpitfidf ./data/news/* ./data/books/*
