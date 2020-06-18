#ifndef PERSON_H
#define PERSON_H

#include "values.h"

typedef struct Person Person;

int person_init(Person *self);

int person_set(Person *self, const char *name, int age, const char *gender);

int person_destroy(Person *self);

char *person_get_name(Person *self);

int person_get_age(Person *self);

char *person_get_gender(Person *self);

int person_create_from_string(Person *self, char *line);

int person_print_data(Person *self); 
#endif 



