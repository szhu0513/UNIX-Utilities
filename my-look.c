////////////////////////////////////////////////////////////////////////////////
// Main File:        my-look.c
// This File:        my-look.c
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
#include<ctype.h>
#define BUFFER_SIZE (512)

/*
 * The program my-look is a simple program based on the utility look. 
 * This project take a string as input and return any lines in a file 
 * that contain that string as an input
 */
int main(int argc, char *argv[]) {
    if (argc <= 1 || argc >= 4) {
        printf("my-look: invalid number of arguments\n");
        exit(1);
    }

    FILE *fp;
    if (argc == 2) {
        fp = fopen("/usr/share/dict/words", "r");
    } else {
        // the second argv is the name of file
        fp = fopen(argv[2], "r");
    }

    if (fp == NULL) {
        // if failed to open an file, exit
        printf("my-look: cannot open file\n");
        exit(1);
    }

    // save a new line into buffer
    // calloc will initializes each block with a default value ‘0’.
    char* buffer = calloc(BUFFER_SIZE, sizeof(char));
    char* sub = calloc(BUFFER_SIZE, sizeof(char));
    int n;
    // iterater untill meet the end of the file
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        // the first argv is the string look for
        char* text = argv[1];
        for (n = 0; n < strlen(argv[1]); n++) {
            sub[n] = tolower(buffer[n]);
            text[n] = tolower(text[n]);
        }
        if (strncmp((const char*) sub, (const char*) text,
            strlen(argv[1])) == 0) {
            printf("%s", buffer);
        }
    }
    fclose(fp);
    free(buffer);
    free(sub);
    exit(0);
}
