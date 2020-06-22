#include <stdio.h>
#include <stdlib.h>

#include "../include/macro.h"
#include "../include/person.h"
#include "../include/m-array.h"
#include "../include/josephus.h"

ARRAY_DEF(array_people, Person *, M_POD_OPLIST)

struct _Josephus
{
    int start;
    int step;
    int capacity;
    int _current;
    array_people_t people;
};

//所有计数都从1开始

Josephus *josephus_create(void){
    Josephus *self = (struct _Josephus *)malloc(sizeof(struct _Josephus));
    array_people_init(self->people);
    return self;
}

int josephus_destroy(Josephus *self){
    array_people_clear(self->people);
    free(self);
    return SUCCESS;
}

int josephus_init(Josephus *self, int start, int step, int capacity){
    if(capacity <= 0){
        return INVALID_CAPACITY;
    }

    if(start <= 0 || start > capacity){
        return INVALID_START;
    }

    if(step <= 0){
        return INVALID_STEP;
    }

    self->start = start;
    self->step = step;
    self->capacity = capacity;
    self->_current = 0;

    return SUCCESS;
}

int josephus_append(Josephus *self, Person *someone){
    if(array_people_size(self->people) == self->capacity){
        return FAILURE;
    }
    
    array_people_push_back(self->people, someone);

    return SUCCESS;
}

Person *josephus_pop(Josephus *self, int pop_number){
    if(array_people_size(self->people) <= 0){
        return FAILURE;
    }

    Person **pop_person;
    array_people_pop_at(pop_person, self->people, pop_number);
    
    return *pop_person;
}

int josephus_query(Josephus *self){
    if(array_people_size(self->people) == 0){
        return FAILURE;
    }

    for(int i = 0; i < array_people_size(self->people); i++){
        Person *someone = *array_people_get(self->people, i);
        printf("Number: %d\tName: %s\tAge: %d \tGender: %s\n", 
            i+1, person_get_name(someone), person_get_age(someone), person_get_gender(someone));
    }

    return SUCCESS;
}

int josephus_get_start(Josephus *self){
    return self->start;
}

int josephus_get_step(Josephus *self){
    return self->step;
}

int josephus_get_capacity(Josephus *self){
    return self->capacity;
}

int josephus_get_size_of_people(Josephus *self){
    return array_people_size(self->people);
}


Person *josephus_output_next(Josephus *self){
    int next_number = (self->start + self->step + self->_current - 2) % array_people_size(self->people);
    Person *next_one = josephus_pop(self, next_number);
    self->_current = next_number - 1;

    return next_one;
}