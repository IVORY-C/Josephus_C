#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\..\shared\person.h"
#include "base_function_of_readers.c"

struct Person *create_from_txt_or_csv(char *path){
    FILE *fp = fopen(path, "r");
    char *buffer;
    char *splited_buffer = (char *)malloc(3*sizeof(char));//to do：使用显式
    struct Person *people = (struct Person *)malloc(100*3*sizeof(int));
    int count = 0;

    if(fp != NULL){
        while(fgets(buffer, 256, fp) != NULL){
            buffer = remove_spaces(buffer);
            splited_buffer = split(buffer, ",");

            char *name = &splited_buffer[0];
            int age = atoi(&splited_buffer[1]);
            char *gender = &splited_buffer[2];
            struct Person some_one = {name, age, gender};
            people[count++] = some_one;
        }
        fclose(fp);
    }
    free(splited_buffer);
    return people;
}