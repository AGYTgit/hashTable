compile: makeObject joinObject

makeObject:
	gcc -c hashTable.c -o hashTable.o
	gcc -c main.c -o main.o

joinObject:
	gcc hashTable.o main.o -o out

run:
	./out

