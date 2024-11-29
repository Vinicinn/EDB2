main.o: main.c
	gcc -c main.c
No.o: No.c
	gcc -c No.c
prog: main.o No.o
	gcc -o prog main.o No.o -Wall -fsanitize=address
all: prog
	./prog
clean:
	rm *.o prog