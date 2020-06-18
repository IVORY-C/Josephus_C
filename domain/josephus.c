#include <stdio.h>
#include <stdlib.h>

#include "values.h"
#include "person.h"
#include "josephus.h"

struct Josephus
{
    int start;
    int step;
    int number;
    Person **people;
};

//所有计数都从1开始

int josephus_init(Josephus *self){
    self->people = (Person **)malloc(MAX * sizeof(Person *));
    for(int i = 0; i< MAX; i++){
        person_init(self->people[i]);
    }//是否需要？
    return SUCCESS;
}

int josephus_set(Josephus *self, int start, int step, int number){
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

int josephus_destroy(Josephus *self){
    for(int i = 0; i< MAX; i++){
        person_destroy(self->people[i]);
    }
    free(self->people);
    return SUCCESS;
}

int josephus_append(Josephus *self, Person *someone){
    if(self->number == MAX){
        return FAILURE;
    }
    
    self->people[self->number] = someone;
    self->number++;
    return SUCCESS;
}

int josephus_pop(Josephus *self, int pop_number){
    if(self->number < 1){
        return FAILURE;
    }

    Person *pop_person = self->people[pop_number-1];

    printf("Pop number: %d;\nName: %s, Age: %d, Gender: %s\n", 
        pop_number, person_get_name(pop_person), person_get_age(pop_person), person_get_gender(pop_person));

    for(int i = pop_number-1; i < self->number-1; i++){
        self->people[i] = self->people[i+1];
    }

    return SUCCESS;
}

int josephus_quary(Josephus *self){
    if(self->number == 0){
        return FAILURE;
    }

    for(int i = 0; i < self->number; i++){
        Person *someone = self->people[i];
        printf("Number: %d, Name: %s, Age: %d, Gender: %s\n", 
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

int josephus_input_people(Josephus *self, Person **inputs){
    for(int i = 0; i < self->number; i++){
        if(self->number == MAX){
            printf("The number is over MAX!\n");
            return FAILURE;
        }

        self->people[i] = inputs[i];
    }

    return SUCCESS;
}

int josephus_output_results(Josephus *self, Person **results){
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

            Person *someone = self->people[current];
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