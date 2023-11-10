simulator: simulator.o PriorityQueue.o Heap.o
	gcc -o prog2 simulator.o PriorityQueue.o Heap.o -gdwarf-4

simulator.o: Heap.h PriorityQueue.h simulator.c 
	gcc -c simulator.c -gdwarf-4

PriorityQueue.o: Heap.h PriorityQueue.h Heap.c PriorityQueue.c
	gcc -c PriorityQueue.c -gdwarf-4

Heap.o: Heap.h Heap.c
	gcc -c Heap.c -gdwarf-4

%.o: %.c
	gcc -c -o $@ $< -std=c99 -gdwarf-4

clean:
	rm -f simulator simulator.o Heap.o PriorityQueue.o

check: 
	valgrind --leak-check=full ./prog2