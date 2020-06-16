#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readers.h"
#include "..\shared\person.h"

#define SUCCESS 1
#define FAILURE 0
int readers_create_people_from_txt_or_csv(Person* people, char* path){
    FILE* fp = fopen(path, "r");
    char* buffer = (char *)malloc(256*sizeof(char *));

    int count = 0;
    while(fgets(buffer, 256, fp) != NULL){
        person_create_from_string(people + count, buffer);
        count++;
    }

    fclose(fp);
    free(buffer);

    return SUCCESS;
}