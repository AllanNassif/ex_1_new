//
// Created by Opal on 20/11/2022.
//
#include <string.h>
#include <stdio.h>
#include "AsciiArtTool.h"

#define NUM_OF_FLAGS 2
#define FLAGS 1
#define TARGET 3
#define SOURCE 2
#define INVERTED_FLAG "-i"
#define ENCODED_FLAG "-e"
#define NUM_OF_ARGUMENTS 4

/**
 * mapFunction: swaps only the characters : ' ','@'
 * 
 * @param character - character that will possibly be changed
 */
static char mapFunction(char character){
    if(character == ' '){
        return '@';
    }
    else if(character == '@'){
        return ' ';
    }
    else{
        return character;
    }
}

/**
 * closeTwoFiles: Close two opened files
 * 
 * @param firstFile - file opened number one.
 * @param secondFile - file opened number two.
 */
static void closeTwoFiles(FILE* firstFile , FILE* secondFile){
    assert(firstFile != NULL && secondFile != NULL);
    fclose(firstFile);
    fclose(secondFile);
}

int main(int argc, char** argv)
{
    if (argc != NUM_OF_ARGUMENTS){
        return 0;
    }
    FILE* inStream = fopen(argv[SOURCE],"r");
    if(!inStream){
        return 0;
    }
    FILE* outStream = fopen(argv[TARGET],"w");
    if(!outStream){
        fclose(inStream);
        return 0;
    }

    RLEList asciiArtList = asciiArtRead(inStream);
    if(asciiArtList == NULL){
        closeTwoFiles(inStream,outStream);
        return 0;
    }
    //Writes into out stream the picture in compressed method(encoded)
    if(strcmp(argv[FLAGS], ENCODED_FLAG) == 0){
        asciiArtPrintEncoded(asciiArtList,outStream);
    }
    //Writes into out stream the picture in inverted way
    else if (strcmp(argv[FLAGS], INVERTED_FLAG) == 0) {
        RLEListMap(asciiArtList,mapFunction);
        asciiArtPrint(asciiArtList,outStream);
    }
    
    closeTwoFiles(inStream,outStream);
    RLEListDestroy(asciiArtList);
    return 0;
}
