#include <fstream>
#include <string>
// c headers
#include <stdio.h>
#include <stdlib.h>

/*
example to read a text file, line by line.
parse line into words
add words to map with <word,count>
*/

namespace jly_tutorials
{
    void main_file_reader_cpp()
    {
        std::ifstream file("textfile.txt");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                // using printf() in all tests for consistency
                printf("%s", line.c_str());
            }
            file.close();
        }
    }

    // c version
    // https://stackoverflow.com/questions/735126/are-there-alternate-implementations-of-gnu-getline-interface/735472#735472
    size_t getline(char** lineptr, size_t* n, FILE* stream) {
        char* bufptr = NULL;
        char* p = bufptr;
        size_t size;
        int c;

        if (lineptr == NULL) {
            return -1;
        }
        if (stream == NULL) {
            return -1;
        }
        if (n == NULL) {
            return -1;
        }
        bufptr = *lineptr;
        size = *n;

        c = fgetc(stream);
        if (c == EOF) {
            return -1;
        }
        if (bufptr == NULL) {
            bufptr = (char *)malloc(128);
            if (bufptr == NULL) {
                return -1;
            }
            size = 128;
        }
        p = bufptr;
        while (c != EOF) {
            if ((unsigned int)(p - bufptr) > (unsigned int)(size - 1)) {  // might be better to use unsigned int
                size = size + 128;
                bufptr = (char*)realloc(bufptr, size);
                if (bufptr == NULL) {
                    return -1;
                }
            }
            *p++ = c;
            if (c == '\n') {
                break;
            }
            c = fgetc(stream);
        }

        *p++ = '\0';
        *lineptr = bufptr;
        *n = size;

        return p - bufptr - 1;
    }

    void main_file_reader_c()
    {
#pragma warning(suppress : 4996)
        FILE* fp = fopen("textfile.txt", "r");
        if (fp == NULL)
            exit(EXIT_FAILURE);

        char* line = NULL;
        size_t len = 0;
        while ((getline(&line, &len, fp)) != -1) {
            // using printf() in all tests for consistency
            printf("%s", line);
        }
        fclose(fp);
        if (line)
            free(line);
    }
}