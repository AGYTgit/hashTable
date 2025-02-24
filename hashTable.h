#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

Node* createNode(const char* key, int value);
void freeNode(Node* node);

typedef struct HashTable {
    Node* dataMap[7];
} HashTable;

HashTable* createHashTable();
void freeHashTable(HashTable* hashTable);
void printTable(HashTable* hashTable);
int hash(const char* key);
void set(HashTable* hashTable, const char* key, int value);
int get(HashTable* hashTable, const char* key);
char** keys(HashTable* hashTable);
void freeKeys(char** keys);

bool itemInCommon(int* vect1, int size1, int* vect2, int size2);
int* findDuplicates(int* nums, int size, int* resultSize);

#endif // HASH_TABLE_H
