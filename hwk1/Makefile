hwk1: hwk1.o List.o List.h
	cc -o hwk1 hwk1.o List.o
%.o: %.c
	cc -c -o $@ $< -std=c99 -gdwarf-4

clean:
	rm -f hwk1 *.o
format:
	clang-format -i --style=file *.[ch]

