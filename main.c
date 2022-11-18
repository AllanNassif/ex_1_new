
#include "AsciiArtTool.h"
#include "RLEList.h"
#include <string.h>

#define NUM_OF_ARGUMENTS 4
#define FLAG 1
#define SOURCE 2
#define TARGET 3


/**
 * inputCheck: Checks if the input is valid.
 * 
 * @param argc - Integer that indicates how many arguments were entered on the command line.
 * @param argv - Array of pointers to arrays of character objects.
 * @return
 * false if the command entered in the command line is not proper.
 * true if the command entered in the command line is proper.
 */
static bool inputCheck(int argc, char** argv);


/**
 * closeTwoFiles: Close two opened files
 * 
 * @param firstFile - file opened number one.
 * @param secondFile - file opened number two.
 */
static void closeTwoFiles(FILE* firstFile , FILE* secondFile);

/**
 * mapInvert: inverts every @ character into space character, as well as every space character into @ character.
 * The rest of the characters stay the same.
 * 
 * @param character The character wanted to be changed.
 * @return
 * If character is @ , space character will be returned.
 * If character is space , @ character will be returned.
 * Any other case , same character will be returned.
 */
static char mapInvert(char character);

int main(int argc, char** argv){

    if(inputCheck(argc,argv) == false){
        return 0;
    }
    
    FILE* source = fopen(argv[SOURCE],"r");
    if(!source){
        return 0;
    }
    FILE* target = fopen(argv[TARGET],"w");
    if(!target){
        fclose(source);
        return 0;
    }
    RLEList sourceList = asciiArtRead(source);
    if(sourceList == NULL){
        closeTwoFiles(source,target);
        return 0;
    }
    
    RLEListResult result = RLE_LIST_SUCCESS;
    //Writes into target the picture in compressed method
    if(!strcmp(argv[FLAG],"-e")){
        result = asciiArtPrintEncoded(sourceList,target);
        assert(result == RLE_LIST_SUCCESS);
    }
    //Writes into target the picture in inverted way
    else{
        MapFunction invert = mapInvert; 
        result = RLEListMap(sourceList,invert);
        assert(result == RLE_LIST_SUCCESS);
        result = asciiArtPrint(sourceList,target);
        assert(result == RLE_LIST_SUCCESS);

    }
    closeTwoFiles(source,target);
    RLEListDestroy(sourceList);
    return 0;

}


static void closeTwoFiles(FILE* firstFile , FILE* secondFile){
    assert(firstFile != NULL && secondFile != NULL);
    fclose(firstFile);
    fclose(secondFile);
}

static char mapInvert(char character){
    if(character == '@'){
        return ' ';
    }
    if(character == ' '){
        return '@';
    }
    return character;
}


static bool inputCheck(int argc, char** argv){
    if(argc != NUM_OF_ARGUMENTS){
        return false;
    }
    if(strcmp(argv[FLAG],"-e") && strcmp(argv[FLAG],"-i") ){
        return false;
    }
    if(argv[SOURCE]== NULL){
        return false;
    }
    if(argv[TARGET] == NULL){
        return false;
    }
    return true;
}

