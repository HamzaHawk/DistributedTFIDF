CC=mpic++

OBJ_FLAGS=-O -c -g
LIBS=-lmpi

all: mpitfidf

mpitfidf.o: mpitfidf.cpp
	$(CC) $(OBJ_FLAGS) mpitfidf.cpp

clean:
	rm -rf mpitfidf *.o

test16big:
	time -p mpirun -n 16 --hostfile hostfile -mca btl_tcp_if_include eth0 ./mpitfidf 
