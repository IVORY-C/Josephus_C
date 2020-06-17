#include <stdio.h>
#include <stdlib.h>

#include "josephus.h"

#define MAX 100
#define SUCCESS 1
#define FAILURE 0
#define INVALID_START -1
#define INVALID_STEP -2
#define INVALID_NUMBER -3

//所有计数都从1开始

int josephus_new(Josephus* self, int start, int step, int number){
    if(number < 1 || number > MAX){
        return INVALID_NUMBER;
    }

    if(start < 1 || start > number){
        return INVALID_START;
    }

    if(step < 1){
        return INVALID_STEP;
    }

    self->start = (int)malloc(sizeof(int));
    self->start = start;
    self->step = (int)malloc(sizeof(int));
    self->step = step;
    self->number = (int)malloc(sizeof(int));
    self->number = number;
    self->people = (Person* )malloc(MAX * sizeof(Person));

    return SUCCESS;
}

int josephus_destroy(Josephus* self){
    free(self->people);
    return SUCCESS;
}

int josephus_append(Josephus* self, Person someone){
    if(self->number == MAX){
        return FAILURE;
    }
    
    self->people[self->number] = someone;
    self->number++;
    return SUCCESS;
}

int josephus_pop(Josephus* self, int pop_number){
    if(self->number < 1){
        return FAILURE;
    }

    Person pop_person = self->people[pop_number-1];
    printf("pop number: %d;\nname: %s, age: %d, gender: %s\n", pop_person.name, pop_person.age, pop_person.gender);

    for(int i = pop_number-1; i < self->number-1; i++){
        self->people[i] = self->people[i+1];
    }

    return SUCCESS;
}

int josephus_quary(Josephus* self){
    if(self->number == 0){
        return FAILURE;
    }

    for(int i = 0; i < self->number; i++){
        Person someone = self->people[i];
        printf("number: %d, name: %s, age: %d, gender: %s\n", 
            i+1, someone.name, someone.age, someone.gender);
    }

    return SUCCESS;
}

int josephus_input_people(Josephus* self, Person* inputs){
    for(int i = 0; i < self->number; i++){
        if(self->number == MAX){
            printf("The number is over MAX!\n");
            break;
        }

        self->people[i] = inputs[i];
    }

    return SUCCESS;
}

int josephus_output_results(Josephus* self, Person* results){
    int current = self->start - 1;
    int count = 1;//计数到step归零
    int results_number = 0;

    int flag[MAX] = {0};

    while(results_number < self->number){
        if(count == self->step){
            count = 0;

            Person someone = self->people[current];
            results[results_number] = someone;
            results_number++;

            flag[current] = 1;
        }

        current = (++current) % self->number;
        if(flag[current] == 0){
            count++;
        }
    }

    return SUCCESS;
}