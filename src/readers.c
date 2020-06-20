#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/macro.h"
#include "../include/readers.h"

struct _Reader{
    int capacity;
    int number;
    char *path;
    char *lines[100];
};

Reader *reader_create(void){
    struct _Reader *self = (struct _Reader *)malloc(sizeof(struct _Reader));
    self->path = (char *)malloc(MAX_CHAR * sizeof(char));
    // self->lines = (char **)malloc(100 * sizeof(char *));

    return self;
}

int reader_destroy(Reader *self){
    for(int i = 0; i < self->number; i++){
        free(self->lines[i]);
    }
    free(self->lines);
    free(self->path);
    free(self);

    return SUCCESS;

}

int reader_init(Reader *self, int capacity, const char* path){
    self->capacity = capacity;
    self->number = 0;
    self->path = (char *)path;
}

int reader_get_capacity(Reader *self){
    return self->capacity;
}

int reader_get_number(Reader *self){
    return self->number;
}

char *reader_get_path(Reader *self){
    return self->path;
}

char **reader_get_lines(Reader *self){
    return self->lines;
}

int reader_append_lines_from_file(Reader *self){
    FILE *fp = fopen(self->path, "r");
    char *buffer = (char *)malloc(MAX_CHAR * sizeof(char));

    while(fgets(buffer, 256, fp) != NULL){
        if(self->number == self->capacity){
            break;
        }
        self->lines[self->number] = (char *)malloc(MAX_CHAR * sizeof(char));
        strcpy(self->lines[self->number], buffer);
        self->number++;
    }

    free(buffer);

    return SUCCESS;
}



// int readers_set_people_from_txt_or_csv(Person **people, char *path){
//     FILE *fp = fopen(path, "r");
//     char *buffer = (char *)malloc(MAX_CHAR * sizeof(char));

//     int count = 0;
//     while(fgets(buffer, 256, fp) != NULL){
//         people[count] = person_create();
//         person_set_from_string(people[count], buffer);
//         count++;
//     }

//     fclose(fp);
//     free(buffer);

//     return SUCCESS;
// }