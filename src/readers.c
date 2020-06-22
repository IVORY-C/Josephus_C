#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/macro.h"
#include "../include/m-array.h"
#include "../include/m-string.h"
#include "../include/readers.h"

ARRAY_DEF(array_lines, const char *, M_CSTR_OPLIST)

struct _Reader{
    int capacity;
    int number;
    char *path;
    array_lines_t lines;
};

Reader *reader_create(void){
    struct _Reader *self = (struct _Reader *)malloc(sizeof(struct _Reader));
    self->path = (char *)malloc(MAX_CHAR * sizeof(char));

    array_lines_init(self->lines);
    return self;
}

int reader_destroy(Reader *self){
    array_lines_clear(self->lines);

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

const char *reader_get_lines(Reader *self, int number){
    return *array_lines_get(self->lines, number);
}


/* Helper function strdup */
static char *my_strdup(const char *p)
{
  size_t s = strlen(p);
  char *d= malloc(s+1);
  if(!d) abort();
  strcpy(d, p);
  return d;
}

int reader_append_lines_from_file(Reader *self){
    FILE *fp = fopen(self->path, "r");
    char *buffer = (char *)malloc(MAX_CHAR * sizeof(char));

    while(fgets(buffer, 256, fp) != NULL){
        if(self->number == self->capacity){
            break;
        }
        char *index = my_strdup(buffer);
        array_lines_push_back(self->lines, index);
        self->number++;
    }

    free(buffer);

    return SUCCESS;
}

