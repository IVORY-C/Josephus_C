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

int person_create_from_string(char* line, Person* someone);

int person_data_to_string(Person* self); 
#endif 



