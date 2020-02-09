all: queuetest

queuetest: main.o queue.o breadthfirst.o options.o visit.o
	gcc -o queuetest main.o queue.o breadthfirst.o options.o visit.o

main.o: main.c queue.h
	gcc -c -g main.c

queue.o: queue.c
	gcc -c -g queue.c

breadthfirst.o: breadthfirst.c
	gcc -c -g breadthfirst.c	

options.o: options.c
	gcc -c -g options.c

visit.o: visit.c
	gcc -c -g visit.c

clean:
	rm main.o queue.o breadthfirst.o options.o visit.o queuetest

