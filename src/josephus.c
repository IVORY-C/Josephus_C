#include <stdio.h>
#include <stdlib.h>

#include "../include/macro.h"
#include "../include/person.h"
#include "../include/m-array.h"
#include "../include/josephus.h"

struct _Josephus
{
    int start;
    int step;
    int capacity;
    int number;
    int _current;
    Person *people[100];
};

//所有计数都从1开始

// ARRAY_DEF(array-people, Person, M_POD_OPLIST)

Josephus *josephus_create(void){
    Josephus *self = (struct _Josephus *)malloc(sizeof(struct _Josephus));
    // self->people = (char **)malloc()
    // for(int i = 0; i < MAX; i++){
    //     self->people[i] = person_create();
    // }
    return self;
}

int josephus_destroy(Josephus *self){
    for(; self->number > 0; self->number--){
        person_destroy(self->people[self->number - 1]);
    }
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
    self->number = 0;
    self->_current = 0;

    return SUCCESS;
}

int josephus_append(Josephus *self, Person *someone){
    if(self->number == self->capacity){
        return FAILURE;
    }
    
    self->people[self->number] = someone;
    self->number++;
    return SUCCESS;
}

Person *josephus_pop(Josephus *self, int pop_number){
    if(self->number <= 0){
        return FAILURE;
    }

    Person *pop_person = self->people[pop_number];

    // printf("Pop number: %d;\nName: %s, Age: %d, Gender: %s\n", 
    //     pop_number, person_get_name(pop_person), person_get_age(pop_person), person_get_gender(pop_person));//x

    for(int i = pop_number; i < self->number; i++){
        if(i < self->capacity){
            self->people[i] = self->people[i+1];
        }
    }
    
    return pop_person;
}

int josephus_query(Josephus *self){
    if(self->number == 0){
        return FAILURE;
    }

    for(int i = 0; i < self->number; i++){
        Person *someone = self->people[i];
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

int josephus_get_number(Josephus *self){
    return self->number;
}


Person *josephus_output_next(Josephus *self){
    
    int next_number = (self->start + self->step + self->_current - 2) % self->number;
    Person *next_one = josephus_pop(self, next_number);
    self->_current = next_number - 1;
    self->number--;

    return next_one;
}