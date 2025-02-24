#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"

void printArray(int* arr, int size) {
    printf("(");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf(")");
}

int compareInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void main() {
    {
        printf("\n----- Test: No Duplicates -----\n");
        int nums[] = {1, 2, 3, 4, 5};
        int expected[] = {};
        int resultSize;
        int* result = findDuplicates(nums, 5, &resultSize);
        printf("EXPECTED: No Duplicates\n");
        printf("RETURNED: ");
        printArray(result, resultSize);
        printf("\n");
        printf("%s\n", resultSize == 0 ? "PASS" : "FAIL");
        free(result);
    }

    {
        printf("\n----- Test: Some Duplicates -----\n");
        int nums[] = {1, 2, 3, 2, 1, 4, 5, 6, 5};
        int expected[] = {1, 2, 5};
        int resultSize;
        int* result = findDuplicates(nums, 9, &resultSize);
        qsort(result, resultSize, sizeof(int), compareInt);
        printf("EXPECTED: Has Duplicates: (1, 2, 5)\n");
        printf("RETURNED: ");
        printArray(result, resultSize);
        printf("\n");
        int pass = (resultSize == 3);
        if (pass) {
            int found1 = 0, found2 = 0, found5 = 0;
            for (int i = 0; i < resultSize; i++) {
                if (result[i] == 1) found1 = 1;
                if (result[i] == 2) found2 = 1;
                if (result[i] == 5) found5 = 1;
            }
            pass = (found1 && found2 && found5);
        }
        printf("%s\n", pass ? "PASS" : "FAIL");
        free(result);
    }

    {
        printf("\n----- Test: All Duplicates -----\n");
        int nums[] = {1, 1, 2, 2, 3, 3};
        int expected[] = {1, 2, 3};
        int resultSize;
        int* result = findDuplicates(nums, 6, &resultSize);
        qsort(result, resultSize, sizeof(int), compareInt);
        printf("EXPECTED: Has Duplicates: (1, 2, 3)\n");
        printf("RETURNED: ");
        printArray(result, resultSize);
        printf("\n");
        int pass = (resultSize == 3);
        if (pass) {
            int found1 = 0, found2 = 0, found3 = 0;
            for (int i = 0; i < resultSize; i++) {
                if (result[i] == 1) found1 = 1;
                if (result[i] == 2) found2 = 1;
                if (result[i] == 3) found3 = 1;
            }
            pass = (found1 && found2 && found3);
        }
        printf("%s\n", pass ? "PASS" : "FAIL");
        free(result);
    }

    {
        printf("\n----- Test: Empty Vector -----\n");
        int nums[] = {};
        int expected[] = {};
        int resultSize;
        int* result = findDuplicates(nums, 0, &resultSize);
        printf("EXPECTED: No Duplicates\n");
        printf("RETURNED: ");
        printArray(result, resultSize);
        printf("\n");
        printf("%s\n", resultSize == 0 ? "PASS" : "FAIL");
        free(result);
    }
}
