#ifndef READERS_H
#define READERS_H

#include "person.h"

typedef struct _Reader Reader;

Reader *reader_create(void);

int reader_destroy(Reader *self);

int reader_init(Reader *self, int capacity, const char* path);

int reader_get_capacity(Reader *self);

int reader_get_number(Reader *self);

char *reader_get_path(Reader *self);

const char *reader_get_lines(Reader *self, int number);

int reader_append_lines_from_file(Reader *self);

#endif