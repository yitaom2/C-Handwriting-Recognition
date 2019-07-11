CC = gcc

vgg16: combine.o
	./combine.o > vgg16

combine.o: combine.c vgg16.o
	$(CC) -o combine.o combine.c vgg16.o -lm

vgg16.o: vgg16.c vgg16.h
	$(CC) -c -o vgg16.o vgg16.c

.PHONY: clean

clean:
	rm vgg16.o combine.o vgg16
