#ifndef PERSON_H
#define PERSON_H

typedef struct person
{
    char *name;
    int age;
    char *gender; 
}Person;

int person_new(Person* self, const char* name, int age, const char* gender);

int person_destroy(Person* self);

int person_create_from_string(Person* self, char* line);

int person_print_data(Person* self); 
#endif 



