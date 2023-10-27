manager: formatter.c List.c List.h
	cc -o prog1 -g formatter.c List.c

%.o: %.c
	cc -c -o $@ $< -std=c99 -gdwarf-4

clean:
	rm prog1
format:
	clang-format -i --style=file *.[ch]
