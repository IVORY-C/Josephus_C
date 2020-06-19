#ifndef PERSON_H
#define PERSON_H

typedef struct Person SPerson;

int person_init(SPerson *self);

int person_set(SPerson *self, const char *name, int age, const char *gender);

int person_destroy(SPerson *self);

char *person_get_name(SPerson *self);

int person_get_age(SPerson *self);

char *person_get_gender(SPerson *self);

int person_create_from_string(SPerson *self, char *line);

int person_print_data(SPerson *self); 
#endif 



