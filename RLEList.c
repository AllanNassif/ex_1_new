#include "RLEList.h"

struct RLEList_t{
    char letter;
    int consecutiveAppearancesNum;
    struct RLEList_t* next;
};

/**
* findListIndex: Returns the list that contains character found at specified index in an RLE list
* @param previousList - A list that is previous to the second parameter - list. 
* @param list - The RLE list to retrieve the list from.
* @param index - The index of the character to find the appropiate list.
* @return
* The list that contains the character with the specified index
*/
RLEList findListIndex(RLEList previousList, RLEList list, int index){
    RLEList currentList = list;
    int counter=0;
    while ( index - counter + 1 > currentList -> consecutiveAppearancesNum ){
        counter += currentList ->consecutiveAppearancesNum;
        previousList = currentList;
        currentList = currentList -> next;
    }
    return currentList;
}


/**
* handleResult: assign result to the appropirate value according to the RLE list result status
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* @param status - Contains the status of result. if status is:
* 	RLE_LIST_NULL_ARGUMENT result will be assigned to RLE_LIST_NULL_ARGUMENT.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS result will be assigned to RLE_LIST_INDEX_OUT_OF_BOUNDS.
* 	LIST_SUCCESS result will be assigned to LIST_SUCCESS.
*   RLE_LIST_OUT_OF_MEMORY result will be assigned to RLE_LIST_OUT_OF_MEMORY.
*   RLE_LIST_ERROR result will be assigned to RLE_LIST_ERROR.
*/
void handleResult(RLEListResult* result , RLEListResult status){

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
    while(endOfList->next != NULL){
        endOfList = endOfList -> next;
    }
    //checks if the letter is similar to the current letter in the end of the list
    if((endOfList -> letter)== value || (endOfList -> letter) == '\0' ){
        (endOfList -> letter) = value;
        (endOfList -> consecutiveAppearancesNum)++;
        return RLE_LIST_SUCCESS;
    }
    
    //creates a new list for the new letter
    RLEList newList = RLEListCreate();
    if(!newList){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newList -> letter = value;
    newList -> consecutiveAppearancesNum = 1;
    endOfList -> next = newList;
    return RLE_LIST_SUCCESS;


}

int RLEListSize(RLEList list){

    if( list == NULL){
        return -1;
    }
    int listSize=0;
    RLEList currentList = list;
    while(currentList != NULL){
        listSize += currentList -> consecutiveAppearancesNum;
        currentList = currentList -> next;
    }
    return listSize;

}

RLEListResult RLEListRemove(RLEList list, int index){

    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listSize = RLEListSize(list);
    if(index < 0 || index >= listSize){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList previousList = list;
    RLEList currentList = findListIndex(previousList,list,index);
    //checks if the current list has 1 letter in a row only
    //if so we will have to delete the list because we will stay with 0 letters after removal
    //otherwise decreasing one from the current list
    if(currentList -> consecutiveAppearancesNum == 1){
        previousList->next = currentList-> next;
        currentList->next = NULL;
        RLEListDestroy(currentList);
    }
    else{
        (currentList -> consecutiveAppearancesNum) --;
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

    RLEList listIndex = findListIndex(list,list,index);
    handleResult(result,RLE_LIST_SUCCESS);
    return listIndex->letter;


}


char* RLEListExportToString(RLEList list, RLEListResult* result){

    if(list == NULL){
        handleResult(result,RLE_LIST_NULL_ARGUMENT);
        return NULL;
    }
    int listSize = RLEListSize(list);
    //multiplying by 3 to assure Edge case - format of <letter><1><\n>
    char* stringList = (char*)malloc(sizeof(*stringList)*(3*listSize+1)); 
    if(stringList == NULL){
        handleResult(result,RLE_LIST_OUT_OF_MEMORY);
        return NULL;
    }
    RLEList currentList = list;
    int index=0;
    //assigning string to have the format of <letter><number of consecutive appearence><\n>
    while(currentList!=NULL){

        stringList[index++] = currentList -> letter;
        stringList[index++] = currentList->consecutiveAppearancesNum;
        //avoiding to put new line , if we are at the last list
        if(currentList -> next != NULL){
            stringList[index++] = '\n';
        }
        currentList = currentList -> next;

    }
    stringList[index]='\0';
    handleResult(result,RLE_LIST_SUCCESS);
    
    return stringList;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){

    if(list == NULL || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList currentList = list;
    while(currentList != NULL){
        currentList -> letter = map_function(currentList->letter);
        currentList = currentList -> next;
    }
    return RLE_LIST_SUCCESS;
}



