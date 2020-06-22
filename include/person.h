#ifndef PERSON_H
#define PERSON_H

typedef struct _Person Person;

Person *person_create(void);

int person_init(Person *self, const char *name, int age, const char *gender);

int person_destroy(Person *self);

char *person_get_name(Person *self);

int person_get_age(Person *self);

char *person_get_gender(Person *self);

int person_init_from_string(Person *self, const char *line);

int person_print_data(Person *self); 
#endif 



