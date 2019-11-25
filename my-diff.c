////////////////////////////////////////////////////////////////////////////////
// Main File:        my-diff.c
// This File:        my-diff.c
// Other Files:      none
// Semester:         CS 537 FALL 2019
//
// Author:           Shiyu Zhu
// Email:            szhu227@wisc.edu
// CS Login:         shiyuz
// Copyright [2019] <Shiyu Zhu>
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//
// Online sources:   none
//
////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE (512)
/*
 * This program takes two files as input and then outputs the lines 
 * that are different across the two of them.
 */
int main(int argc, char *argv[]) {
    if (argc !=3) {
        printf("my-diff: invalid number of arguments\n");
        exit(1);
    }

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    if (fp1 == NULL || fp2 ==NULL) {
        // if failed to open an file, exit
        printf("my-diff: cannot open file\n");
        exit(1);
    }

    char *lineptr1 = NULL;
    size_t size1 = 0;
    ssize_t characterNum1;
    characterNum1 = getline(&lineptr1, &size1, fp1);
    char *lineptr2 = NULL;
    size_t size2 = 0;
    ssize_t characterNum2;
    characterNum2 = getline(&lineptr2, &size2, fp2);
    int mistakeHappen = 0;
    int linecount = 0;

    // getline return -1 on failure to read a line or end-of file condition
    while (characterNum1 != -1 || characterNum2 != -1) {
        linecount++;
        if (characterNum1 != -1 && characterNum2 != -1) {
            if (strcmp((const char*) lineptr1, (const char*) lineptr2) != 0) {
                if (linecount-mistakeHappen  > 1 || mistakeHappen == 0) {
                    printf("%d\n", linecount);
                }
                if (lineptr1[characterNum1 -1 ] == '\n') {
                    printf("< %s", lineptr1);
                } else {
                    printf("< %s\n", lineptr1);
                }
                if (lineptr2[characterNum2 -1 ] == '\n') {
                    printf("> %s", lineptr2);
                } else {
                    printf("> %s\n", lineptr2);
                }
                mistakeHappen = linecount;
            }
        }
        // characterNum1 is EOF but characterNum2 Not
        if (characterNum1 == -1 && characterNum2 != -1) {
            if (linecount-mistakeHappen > 1 || mistakeHappen == 0) {
                printf("%d\n", linecount);
            }
            if (lineptr2[characterNum2 -1 ] == '\n') {
                    printf("> %s", lineptr2);
            } else {
                    printf("> %s\n", lineptr2);
            }
            mistakeHappen = linecount;
        }
        // characterNum2 is EOF but characterNum1 Not
        if (characterNum1 != -1 && characterNum2 == -1) {
            if (linecount-mistakeHappen > 1 || mistakeHappen == 0) {
                printf("%d\n", linecount);
            }
            if (lineptr1[characterNum1 -1 ] == '\n') {
                    printf("< %s", lineptr1);
                } else {
                    printf("< %s\n", lineptr1);
                }
            mistakeHappen = linecount;
        }
        characterNum1 = getline(&lineptr1, &size1, fp1);
        characterNum2 = getline(&lineptr2, &size2, fp2);
    }
    free(lineptr1);
    free(lineptr2);
    fclose(fp1);
    fclose(fp2);
    exit(0);
}
