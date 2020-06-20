#ifndef JOSEPHUS_H
#define JOSEPHUS_H

#include "person.h"

typedef struct _Josephus Josephus;

Josephus *josephus_create(void);

int josephus_init(Josephus *self, int start, int step, int capacity);

int josephus_destroy(Josephus *self);

int josephus_append(Josephus *self, Person *someone);

Person *josephus_pop(Josephus *self, int pop_number);

int josephus_query(Josephus *self);

int josephus_get_start(Josephus *self);

int josephus_get_step(Josephus *self);

int josephus_get_number(Josephus *self);

Person *josephus_output_next(Josephus *self);

#endif