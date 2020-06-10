#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "..\..\domain\adapter\readers\base_function_of_readers.c"

int main(){
    char *test = (char *)"fs, ds13f, dwfa f ";
    
    test = remove_spaces(test);
    printf("%s\n", test);
    // assert(test == "fs,ds13f,dwfaf");

    char *output = split(test, ",");
    int i = 0;
    char *index;
    while(index = output[i]){
        printf("%s\n", index);
        i++;
    }

}

