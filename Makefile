CC=mpic++

OBJ_FLAGS=-O -c -g 
LIBS=-lmpi

all: mpitfidf.o

mpitfidf.o: mpitfidf.cpp file_hashing.cpp max_term_finder.cpp document_frequency.cpp serialize_utility.cpp
	$(CC) $(OBJ_FLAGS) mpitfidf.cpp file_hashing.cpp max_term_finder.cpp document_frequency.cpp serialize_utility.cpp

clean:
	rm -rf mpitfidf *.o

test16big:
	time -p mpirun -n 16 --hostfile hostfile -mca btl_tcp_if_include eth0 ./mpitfidf 
