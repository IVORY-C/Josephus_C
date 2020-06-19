#include <stdio.h>
#include <stdlib.h>

#include "macro.h"
#include "person.h"
#include "josephus.h"

struct Josephus
{
    int start;
    int step;
    int number;
    SPerson **people;
};

//所有计数都从1开始

int josephus_create(SJosephus *self){
    self->people = (SPerson **)malloc(MAX * sizeof(SPerson *));
    // for(int i = 0; i< MAX; i++){
    //     self->people[i] = (SPerson *)malloc(sizeof(SPerson *));
    // }
    return SUCCESS;
}

int josephus_set(SJosephus *self, int start, int step, int number){
    if(number < 1 || number > MAX){
        return INVALID_NUMBER;
    }

    if(start < 1 || start > number){
        return INVALID_START;
    }

    if(step < 1){
        return INVALID_STEP;
    }

    self->start = start;
    self->step = step;
    self->number = number;

    return SUCCESS;
}

int josephus_destroy(SJosephus *self){
    // for(int i = 0; i< MAX; i++){
    //     person_destroy(self->people[i]);
    // }
    free(self->people);
    return SUCCESS;
}

int josephus_append(SJosephus *self, SPerson *someone){
    if(self->number == MAX){
        return FAILURE;
    }
    
    self->people[self->number] = someone;
    self->number++;
    return SUCCESS;
}

int josephus_pop(SJosephus *self, int pop_number){
    if(self->number < 1){
        return FAILURE;
    }

    SPerson *pop_person = self->people[pop_number-1];

    printf("Pop number: %d;\nName: %s, Age: %d, Gender: %s\n", 
        pop_number, person_get_name(pop_person), person_get_age(pop_person), person_get_gender(pop_person));

    for(int i = pop_number-1; i < self->number-1; i++){
        self->people[i] = self->people[i+1];
    }

    return SUCCESS;
}

int josephus_quary(SJosephus *self){
    if(self->number == 0){
        return FAILURE;
    }

    for(int i = 0; i < self->number; i++){
        SPerson *someone = self->people[i];
        printf("Number: %d, Name: %s, Age: %d, Gender: %s\n", 
            i+1, person_get_name(someone), person_get_age(someone), person_get_gender(someone));
    }

    return SUCCESS;
}

int josephus_get_start(SJosephus *self){
    return self->start;
}

int josephus_get_step(SJosephus *self){
    return self->step;
}

int josephus_get_number(SJosephus *self){
    return self->number;
}

int josephus_input_people(SJosephus *self, SPerson **inputs){
    for(int i = 0; i < self->number; i++){
        if(self->number == MAX){
            printf("The number is over MAX!\n");
            return FAILURE;
        }

        self->people[i] = inputs[i];
    }

    return SUCCESS;
}

int josephus_output_results(SJosephus *self, SPerson **results){
    int current = self->start - 1;
    int count = 1;//计数到step归零
    int results_number = 0;

    int *flag = (int *)malloc(self->number * sizeof(int));
    for(int i = 0; i < self->number; i++){
        flag[i] = 0;
    }

    while(results_number < self->number){
        if(count == self->step){
            count = 0;

            SPerson *someone = self->people[current];
            results[results_number] = someone;
            results_number++;

            flag[current] = 1;
        }

        current = (++current) % self->number;
        if(flag[current] == 0){
            count++;
        }
    }

    free(flag);
    
    return SUCCESS;
}