////////////////////////////////////////////////////////////////////////////////
// Main File:        across.c
// This File:        across.c
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
 * This program is used to find words of a specified length that contain 
 * a specified substring at a specified position
 */
int main(int argc, char *argv[]) {
    if (argc <4 || argc >5) {
        printf("across: invalid number of arguments\n");
        exit(1);
    }

    FILE *fp;
    if (argc == 4) {
        fp = fopen("/usr/share/dict/words", "r");
    } else {
        // the second argv is the name of file
        fp = fopen(argv[4], "r");
    }
    if (fp == NULL) {
        // if failed to open an file, exit
        printf("across: cannot open file\n");
        exit(1);
    }

    char* text = argv[1];
    int length = strlen(argv[1]);

    // transfer the character number to int
    int place;
    sscanf(argv[2], "%d", &place);
    int requiredLength;
    sscanf(argv[3], "%d", &requiredLength);
    if (length + place > requiredLength) {
        printf("across: invalid position\n");
        exit(1);
    }

    // save a new line into buffer
    char buffer[BUFFER_SIZE];
    int flag = 0;
    int bufferSize;
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        bufferSize = strlen(buffer);
        // check if the word in the file with \n
        if (buffer[bufferSize-1] == '\n') {
            for (int n = 0; n < bufferSize -1; n++) {
                if (buffer[n] < 'a' || buffer[n] > 'z') {
                    flag = 1;
                    break;
                }
            }
        } else {
            for (int n = 0; n < bufferSize; n++) {
                if (buffer[n] < 'a' || buffer[n] > 'z') {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0) {
          char sub[512];
          for (int i =0; i< length; i++) {
            sub[i] = buffer[place+i];
          }
        if (buffer[bufferSize-1] =='\n') {
            if (strncmp((const char*) sub, (const char*) text, length) == 0
                && strlen(buffer)-1 == requiredLength) {
                printf("%s", buffer);
            }
        } else {
            if (strncmp((const char*) sub, (const char*) text, length) == 0
                && strlen(buffer) == requiredLength) {
                printf("%s", buffer);
           }
          }
      } else if (flag == 1) {
            flag = 0;
        }
    }

    fclose(fp);
    exit(0);
}
