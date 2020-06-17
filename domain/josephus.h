#ifndef JOSEPHUS_H
#define JOSEPHUS_H

#include "person.h"

typedef struct josephus
{
    int start;
    int step;
    int number;
    Person* people;
} Josephus;

int josephus_new(Josephus* self, int start, int step, int number);

int josephus_destroy(Josephus* self);

int josephus_append(Josephus* self, Person someone);

int josephus_pop(Josephus* self, int pop_number);

int josephus_quary(Josephus* self);

int josephus_input_people(Josephus* self, Person* inputs);

int josephus_output_results(Josephus* self, Person* results);

#endif