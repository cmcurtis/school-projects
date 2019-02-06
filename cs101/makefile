CC = g++
CFLAGS = -Wall -g

default: encode

encode: encode.o List.o MinHeap.o Huffman.o
		$(CC) $(CFLAGS) -o encode encode.o List.o MinHeap.o Huffman.o

encode.o: List.o MinHeap.o Huffman.o
		$(CC) $(CFLAGS) -c encode.cpp

List.o: Node.h List.h

MinHeap.o: List.h MinHeap.h

Huffman.o: MinHeap.h Huffman.h
