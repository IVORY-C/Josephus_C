#ifndef JOSEPHUS_H
#define JOSEPHUS_H

#include "values.h"
#include "person.h"

typedef struct Josephus Josephus;

int josephus_init(Josephus *self);

int josephus_set(Josephus *self, int start, int step, int number);

int josephus_destroy(Josephus *self);

int josephus_append(Josephus *self, Person *someone);

int josephus_pop(Josephus *self, int pop_number);

int josephus_quary(Josephus *self);

int josephus_get_start(Josephus *self);

int josephus_get_step(Josephus *self);

int josephus_get_number(Josephus *self);

int josephus_input_people(Josephus *self, Person **inputs);

int josephus_output_results(Josephus *self, Person **results);

#endif