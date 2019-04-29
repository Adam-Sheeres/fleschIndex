/*
main.c
assignment_2

Created by Adam Sheeres-Paulipulle on 2019-02-01.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void freeArray(char*);
int countWords(char*, long);
int countSyllable(char*, long);
int countSentences(char*, long);

int main() {
    FILE *inputFile;
    double numWords, numSyllables, numSentences;
    double fIndex;
    char* fileAsString;
    long fileSize;
    
    
    numWords = 0;
    numSentences = 0;
    numSyllables = 0;
    fileSize = 0;
    fileAsString = NULL;
    
    
    inputFile = fopen("test.txt", "rb"); /*Set mode to read*/
    
    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    
    fileAsString = malloc(fileSize + 1); /*allocate space in memory for string*/
    
    fread(fileAsString, fileSize, 1, inputFile); /*store into string*/
    
    numWords = countWords(fileAsString, fileSize);
    numSentences = countSentences(fileAsString, fileSize);
    numSyllables = countSyllable(fileAsString, fileSize);
    
    fIndex = ( 206.835 - 84.6 * (numSyllables / numWords) - 1.015 * (numWords / numSentences));
    
    printf("Flesch Index = %0.0lf\n", fIndex);
    printf("Syllable Count = %d\n", (int)numSyllables);
    printf("Word Count = %d\n", (int)numWords);
    printf("Sentence Count = %d\n", (int)numSentences);
    
    freeArray(fileAsString);
    fclose(inputFile);
    return 0;
}
                   
int countWords(char* inputString, long fileSize) {
    int numWords, currentChar, i, buffer;
    
    numWords = 0;
    currentChar = 0;
    buffer = 0;
    
    for (i = 0; i < fileSize; i++) {
            if (strchr(".?! ", inputString[i])) { /*check if there is the end of a sentence*/
                numWords++;
                if (isspace(inputString[i + 1])) { /*if there is a space after the sentence*/
                    numWords--;
                }
            } else if (isspace(inputString[i])) { /*if there is a space*/
                numWords++;
            }
    }
    return numWords;
}

int countSyllable(char* inputString, long fileSize) {
    int syllableCount, i, currentSylCount;
    
    syllableCount = 0;
    currentSylCount = 0;
    
    for (i = 0; i < fileSize; i++) {
        if (strchr("AEIOUYaeiouy", inputString[i])) { /*check if there is a syllable*/
            currentSylCount++;
            
            if (strchr("AEIOUYaeiouy", inputString[i + 1])) { /*check for the sequential syllable*/
                currentSylCount--;
            }
            if (strchr("Ee",  inputString[i]) && isspace(inputString[i + 1])) { /*if there is an 'e' at the end of the word*/
                currentSylCount--;
                if (currentSylCount <= 0) {
                    currentSylCount++;
                }
            }
        } else if (isspace(inputString[i])) {
            syllableCount += currentSylCount;
            currentSylCount = 0;
        }
    }
    return syllableCount;
}

int countSentences(char *inputString, long fileSize) {
    int numSentances, i;
    
    numSentances = 0;
    
    for (i = 0; i < fileSize; i++) {
        
        if (strchr(".?!;", inputString[i])) {
            numSentances++;
        }
    }
    
    return numSentances;
}

void freeArray(char* inputString) {
    free(inputString);
}
