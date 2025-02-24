#include "hashTable.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Node* createNode(const char* key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    newNode->key = strdup(key);
    if (newNode->key == NULL) {
        perror("Memory allocation failed");
        free(newNode);
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void freeNode(Node* node) {
    if (node) {
        free(node->key);
        free(node);
    }
}

HashTable* createHashTable() {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if (hashTable == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    for (int i = 0; i < 7; i++) {
        hashTable->dataMap[i] = NULL;
    }
    return hashTable;
}

void freeHashTable(HashTable* hashTable) {
    if (hashTable == NULL) return;
    for (int i = 0; i < 7; i++) {
        Node* head = hashTable->dataMap[i];
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            freeNode(temp);
        }
    }
    free(hashTable);
}

void printTable(HashTable* hashTable) {
    if (hashTable == NULL) return;
    for (int i = 0; i < 7; i++) {
        printf("Index %d: ", i);
        if (hashTable->dataMap[i]) {
            printf("Contains => ");
            Node* temp = hashTable->dataMap[i];
            while (temp) {
                printf("{%s, %d}", temp->key, temp->value);
                temp = temp->next;
                if (temp) printf(", ");
            }
            printf("\n");
        } else {
            printf("Empty\n");
        }
    }
}

int hash(const char* key) {
    int hashVal = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashVal = (hashVal * 23 + key[i]) % 7;
    }
    return hashVal;
}

void set(HashTable* hashTable, const char* key, int value) {
    int index = hash(key);
    Node* newNode = createNode(key, value);
    if (hashTable->dataMap[index] == NULL) {
        hashTable->dataMap[index] = newNode;
    } else {
        Node* temp = hashTable->dataMap[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int get(HashTable* hashTable, const char* key) {
    int index = hash(key);
    Node* temp = hashTable->dataMap[index];
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return 0;
}

char** keys(HashTable* hashTable) {
    int count = 0;
    for(int i = 0; i < 7; i++){
        Node* temp = hashTable->dataMap[i];
        while(temp != NULL){
            count++;
            temp=temp->next;
        }
    }

    char** allKeys = (char**)malloc((count + 1) * sizeof(char*));
    if (allKeys == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    int index = 0;
    for (int i = 0; i < 7; i++) {
        Node* temp = hashTable->dataMap[i];
        while (temp != NULL) {
            allKeys[index++] = strdup(temp->key);
            temp = temp->next;
        }
    }
    allKeys[index] = NULL;
    return allKeys;
}

void freeKeys(char** keys) {
    if (keys == NULL) return;
    for (int i = 0; keys[i] != NULL; i++) {
        free(keys[i]);
    }
    free(keys);
}

bool itemInCommon(int* vect1, int size1, int* vect2, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (vect1[i] == vect2[j]) {
                return true;
            }
        }
    }
    return false;
}

int* findDuplicates(int* nums, int size, int* resultSize) {
    int* counts = (int*)calloc(201, sizeof(int));
    int* duplicates = (int*)malloc(size * sizeof(int));
    if (counts == NULL || duplicates == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    int dupCount = 0;
    for (int i = 0; i < size; i++) {
        counts[nums[i] + 100]++;
    }
    for (int i = 0; i < 201; i++) {
        if (counts[i] > 1) {
            duplicates[dupCount++] = i - 100;
        }
    }
    free(counts);
    *resultSize = dupCount;
    return duplicates;
}
