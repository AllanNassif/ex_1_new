#include "AsciiArtTool.h"

#define BUFFER_SIZE 2
#define CHARACTER_INDEX 0

RLEList asciiArtRead(FILE* in_stream){
    if(in_stream == NULL){
        return NULL;
    }
    RLEList streamList = RLEListCreate();
    if(streamList == NULL){
        return NULL;
    }
    char buffer[BUFFER_SIZE]="";
    //goes over all the file , reads character by character and put it on the list
    while( (fgets(buffer,BUFFER_SIZE,in_stream)!=NULL)){
        assert(buffer[CHARACTER_INDEX] != '\0');
        if(RLEListAppend(streamList,buffer[CHARACTER_INDEX])!= RLE_LIST_SUCCESS){
            return NULL;
        }
    }
    return streamList;
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){

    if(out_stream == NULL || list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listSize = RLEListSize(list);
    assert(listSize != -1);
    //puts character by character into the out_stream
    for(int index=0; index<listSize; index++){
        char characterIndex = RLEListGet(list , index , NULL);
        fputc(characterIndex,out_stream);
    }
    
    return RLE_LIST_SUCCESS;

}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){
    if(list == NULL || out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    char* listInString = RLEListExportToString(list,NULL);
    assert(listInString != NULL);
    fputs(listInString,out_stream);
    free(listInString);
    return RLE_LIST_SUCCESS;
}

