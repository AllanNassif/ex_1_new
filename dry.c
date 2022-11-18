#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//This function returns the allocated array. Note that the 
//caller is responsible to free it.
char* stringDuplicator(char* s, int times){
    assert(*s);
    assert(times > 0);
    int len = strlen(s);
    char* out = (char*)malloc(sizeof(*out)*(len*times+1));
    if(out == NULL){
        fprintf(stderr ,"Dynamic allocation failed!\n");
        return NULL;
    }
    for (int i=0; i< times; i++){
        strcpy(out+i*len,s);
    }
    return out;
}

int main(){

    char* str = stringDuplicator("Hello",3);
    printf("%s",str);
    free(str);
    return 0;
}