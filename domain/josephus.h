#ifndef JOSEPHUS_H
#define JOSEPHUS_H

#include "macro.h"
#include "person.h"


typedef struct Josephus SJosephus;//incomplete type

int josephus_init(SJosephus *self);

int josephus_set(SJosephus *self, int start, int step, int number);

int josephus_destroy(SJosephus *self);

int josephus_append(SJosephus *self, SPerson *someone);

int josephus_pop(SJosephus *self, int pop_number);

int josephus_quary(SJosephus *self);

int josephus_get_start(SJosephus *self);

int josephus_get_step(SJosephus *self);

int josephus_get_number(SJosephus *self);

int josephus_input_people(SJosephus *self, SPerson **inputs);

int josephus_output_results(SJosephus *self, SPerson **results);

#endif