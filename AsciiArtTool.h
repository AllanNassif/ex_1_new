

#ifndef ASCII_ART_TOOL_H
#define ASCII_ART_TOOL_H

#include "RLEList.h"
#include <assert.h>
#include <stdlib.h>

/**
* ASCII ART
*
* Implements reading/writing pictures of ASCII ART type.
*
* The following functions are available:
*   asciiArtRead	        - Reads a given file and compressing it by using RLE method.
*   asciiArtPrint		    - Writes a picture that is represented by RLEList type to a folder.
*   asciiArtPrintEncoded    - Writes into a folder a picture in a compressed version.
*/


/**
* asciiArtRead: Reads a given file and compressing it by using RLE method.

* The function allocates and returns a new RLEList struct containing the picture.
* Note that the user must free the returned list using RLEListDestroy() once it is no longer needed.
* @param in_stream - An FILE* object that contains the picture wanting to compress.
* @return
* NULL if the input in_stream is NULL or if an allocation failled.
* In case of success - A list of RLEList type that contains all the characters in the image.
*/
RLEList asciiArtRead(FILE* in_stream);


/**
 * asciiArtPrint: Writes a picture which is represented by a list of RLEList type into a folder.
 * 
 * @param list - list of RLEList type that contains all the characters in the image.
 * @param out_stream - object of FILE* type which the picture will be written into.
 * @return
 * RLE_LIST_NULL_ARGUMENT if one of the parameters is NULL.
 * RLE_LIST_SUCCESS the RLE list has been successfuly written into the folder.
 * 
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
 * asciiArtPrintEncoded: Writes into a file the picture in a compressed method.
 * 
 * @param list -list of RLEList type that contains all the characters in the image.
 * @param out_stream - object of FILE* type which the compressed picture will be written into.
 * @return
 * RLE_LIST_NULL_ARGUMENT if one of the parameters is NULL.
 * RLE_LIST_SUCCESS incase successed writing into a file the picture in a compressed method.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);



#endif //ASCII_ART_TOOL_H