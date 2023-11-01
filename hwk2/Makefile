#------------------------------------------------------------------------------
#  Makefile for hwk2 
# 
#  make             makes simulator
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#
#  simulator.c		this is where the simulator is implemented

#------------------------------------------------------------------------------
simulator:	simulator.o List.o Queue.o 
	cc -o  hwk2 simulator.o Queue.o List.o  -gdwarf-4

simulator.o: List.h Queue.h simulator.c 
	cc -c simulator.c -gdwarf-4

Queue.o: Queue.h Queue.c
	cc -c Queue.c -gdwarf-4

List.o: List.h List.c
	cc -c List.c -gdwarf-4

%.o: %.c
	cc -c -o $@ $< -std=c99 -gdwarf-4

clean:
	rm -f simulator simulator.o Queue.o stations.o List.o hwk2

check: 
	valgrind --leak-check=full ./hwk2

format:
	clang-format -i --style=file *.[ch]

