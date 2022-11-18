#include "RLEList.h"
#include <stdlib.h>
#include <string.h>


struct RLEList_t{
    char letter;
    int consecutiveAppearancesNum;
    struct RLEList_t* next;
};


/**
* handleResult: assign result to the appropirate value according to the RLE list result status
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* @param status - Contains the status of result. if status is:
* 	RLE_LIST_NULL_ARGUMENT - result will be assigned to RLE_LIST_NULL_ARGUMENT.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS - result will be assigned to RLE_LIST_INDEX_OUT_OF_BOUNDS.
* 	LIST_SUCCESS - result will be assigned to LIST_SUCCESS.
*   RLE_LIST_OUT_OF_MEMORY - result will be assigned to RLE_LIST_OUT_OF_MEMORY.
*   RLE_LIST_ERROR - result will be assigned to RLE_LIST_ERROR.
*/
static void handleResult(RLEListResult* result , RLEListResult status){

    if(result == NULL){
        return;
    }
    if(status == RLE_LIST_SUCCESS){
        *result = RLE_LIST_SUCCESS;
    }
    else if(status == RLE_LIST_OUT_OF_MEMORY){
        *result = RLE_LIST_OUT_OF_MEMORY;
    }
    else if(status == RLE_LIST_NULL_ARGUMENT){
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    else if(status == RLE_LIST_INDEX_OUT_OF_BOUNDS){
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else{
        *result = RLE_LIST_ERROR;
    }
}


RLEList RLEListCreate(){

    RLEList newList = malloc(sizeof(*newList));
    if(newList == NULL){
        return NULL;
    }
    newList -> letter = '\0';
    newList -> consecutiveAppearancesNum = 0;
    newList -> next = NULL;
    return newList;

}

void RLEListDestroy(RLEList list){

    while(list != NULL){
        RLEList toRemove = list;
        list = list -> next;
        free(toRemove);
    }
}

RLEListResult RLEListAppend(RLEList list, char value){

    if(list == NULL || value == '\0'){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList endOfList = list;
    while( endOfList -> next != NULL){
        endOfList = endOfList -> next;
    }
    if( (endOfList ->letter) == value ){
        (endOfList->consecutiveAppearancesNum)++;
        return RLE_LIST_SUCCESS;
    }

    RLEList newList = RLEListCreate();
    if(newList == NULL){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    endOfList->next = newList;
    newList -> letter = value;
    newList -> consecutiveAppearancesNum = 1;
    return RLE_LIST_SUCCESS;

}

int RLEListSize(RLEList list){
    if(list == NULL){
        return -1;
    }
    int listSize = 0;
    RLEList currentNode = list;
    while (currentNode != NULL){
        listSize += currentNode -> consecutiveAppearancesNum;
        currentNode = currentNode -> next;
    }
    return listSize;

}

RLEListResult RLEListRemove(RLEList list, int index){

    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listSize = RLEListSize(list);
    if( index < 0 || index >= listSize){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList previousIndexNode = list;
    RLEList indexNode = list;
    int counter =0;
    while(index - counter >= indexNode -> consecutiveAppearancesNum){
        counter += indexNode -> consecutiveAppearancesNum;
        previousIndexNode = indexNode;
        indexNode = indexNode -> next;
    }
    
    if(indexNode->next == NULL && indexNode -> consecutiveAppearancesNum > 1){
        (indexNode -> consecutiveAppearancesNum)--;
    }
    else if(indexNode->next == NULL && indexNode -> consecutiveAppearancesNum == 1){
        previousIndexNode-> next = NULL;
        free(indexNode);
    }
    else{
        RLEList nextIndexNode = indexNode -> next;
        if(indexNode->consecutiveAppearancesNum > 1){
            (indexNode ->consecutiveAppearancesNum)--;
        }
        else{
            if(previousIndexNode -> letter != nextIndexNode -> letter){
                previousIndexNode-> next = nextIndexNode;
                free(indexNode);
            }
            else{
                previousIndexNode -> next = nextIndexNode -> next;
                previousIndexNode -> consecutiveAppearancesNum += nextIndexNode -> consecutiveAppearancesNum;
                free(indexNode);
                free(nextIndexNode);
            }
        }
    }
    return RLE_LIST_SUCCESS;

}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if(list == NULL){
        handleResult(result,RLE_LIST_NULL_ARGUMENT);
        return 0;
    }
    int listSize = RLEListSize(list);
    if(index < 0 || index >= listSize){
        handleResult(result,RLE_LIST_INDEX_OUT_OF_BOUNDS);
        return 0;
    }

    RLEList indexNode = list;
    int counter =0;
    while(index - counter >= indexNode -> consecutiveAppearancesNum){
        counter += indexNode -> consecutiveAppearancesNum;
        indexNode = indexNode -> next;
    }
    handleResult(result,RLE_LIST_SUCCESS);
    return indexNode -> letter;

}


char* RLEListExportToString(RLEList list, RLEListResult* result){
    
    if(list == NULL){
        handleResult(result,RLE_LIST_NULL_ARGUMENT);
        return NULL;
    }
    int listSize = RLEListSize(list);
    const int MAX_INT_LENGTH = 10;
    //string is in the format <letter><num - which can take up to MAX_INT_LENGTH><\n>
    char* initialListAsString = malloc(sizeof(*initialListAsString)*(2*listSize+MAX_INT_LENGTH*listSize+1));
    if(initialListAsString == NULL){
        handleResult(result,RLE_LIST_OUT_OF_MEMORY);
        return NULL;  
    }
    RLEList currentNode = list -> next;
    int index = 0;
    while(currentNode != NULL){
        initialListAsString[index++] = currentNode -> letter;
        char numAsString[MAX_INT_LENGTH + 1];
        sprintf(numAsString, "%d", currentNode -> consecutiveAppearancesNum);
        int numLength = strlen(numAsString);
        strcpy(initialListAsString + index, numAsString);
        index += numLength;
        initialListAsString[index++] = '\n'; // MIGHT NEED TO INCLUDE IF, INCASE NOT NEEDED IN LAST LINE
        currentNode = currentNode -> next;
    }
    initialListAsString[index] = '\0';
    /*int stringLength = strlen(initialListAsString);
    char* finalListAsString = realloc(initialListAsString,sizeof(*finalListAsString)*(stringLength+1));
    if(finalListAsString == NULL){
        if(result != NULL){
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    initialListAsString = NULL; */
    handleResult(result,RLE_LIST_SUCCESS);
    return initialListAsString;

}


RLEListResult RLEListMap(RLEList list, MapFunction map_function){

    if(list == NULL || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList previousNode = list;
    RLEList currentNode = list -> next;
    while (currentNode != NULL){
        currentNode -> letter = map_function(currentNode->letter);
        if(currentNode -> letter == previousNode -> letter){
            previousNode ->consecutiveAppearancesNum += currentNode -> consecutiveAppearancesNum;
            previousNode -> next = currentNode -> next;
            RLEList toRemove = currentNode;
            currentNode = currentNode -> next;
            toRemove -> next = NULL;
            RLEListDestroy(toRemove);
        }
        else{
            previousNode = currentNode;
            currentNode = currentNode -> next;
        }
    }
    return RLE_LIST_SUCCESS;
}