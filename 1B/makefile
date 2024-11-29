main.o: main.c
	gcc -c main.c
MaxHeap.o: MaxHeap.c
	gcc -c MaxHeap.c
prog: main.o MaxHeap.o
	gcc -o prog main.o MaxHeap.o
all: prog
	./prog
clean:
	rm *.o prog