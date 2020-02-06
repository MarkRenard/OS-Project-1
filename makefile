all: queuetest

queuetest: main.o queue.o
	gcc -o queuetest main.o queue.o

main.o: main.c queue.h
	gcc -c -g main.c

queue.o: queue.c
	gcc -c -g queue.c

clean:
	rm main.o queue.o queuetest
