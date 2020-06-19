#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "person.h"
#include "readers.h"s

int readers_create_people_from_txt_or_csv(SPerson **people, char *path){
    FILE *fp = fopen(path, "r");
    char *buffer = (char *)malloc(256 * sizeof(char));

    int count = 0;
    while(fgets(buffer, 256, fp) != NULL){
        person_create_from_string(people[count], buffer);
        count++;
    }

    fclose(fp);
    free(buffer);

    return SUCCESS;
}