#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "person.h"

struct _Person
{
    char *name;
    int age;
    char *gender; 
};

Person *person_create(void){
    Person *self = (struct _Person *)malloc(sizeof(struct _Person));
    self->name = (char *)malloc(MAX_CHAR * sizeof(char));
    self->gender = (char *)malloc(MAX_CHAR * sizeof(char));
    return self;
}

int person_destroy(Person *self){
    free(self->name);
    free(self->gender);
    free(self);
    return SUCCESS;
}

int person_init(Person *self, const char *name, int age, const char *gender){
    if(age < 0){
        return INVALID_AGE;
    }

    if(strcmp(gender, "male") && strcmp(gender, "female")){
        return INVALID_GENDER;
    }
    
    strcpy(self->name, name);
    self->age = age;
    strcpy(self->gender, gender);

    return SUCCESS;
}

char *person_get_name(Person *self){
    return self->name;
}

int person_get_age(Person *self){
    return self->age;
}

char *person_get_gender(Person *self){
    return self->gender;
}



//line = "name, age, gender"
int person_init_from_string(Person *self, char *line){
    char index[20] = {0};
    char *data[3];
    for(int i = 0; i < 3; i++){
        data[i] = (char *)malloc(sizeof(char));
    }

    int count_data = 0;
    int count_index = 0;

    for(int i = 0; i < strlen(line) + 1; i++){
        if(line[i] == ' ' || line[i] == '\n'){
            continue;
        }
        
        if(line[i] == ','){
            strcpy(data[count_data], index);
            count_data++;
            count_index = 0;
            memset(index, 0, sizeof(index));
            continue;
        }

        index[count_index] = line[i];
        count_index++;

        if(i == strlen(line)){
            strcpy(data[count_data], index);
        }
    }

    char *name = data[0];
    int age = atoi(data[1]);//to do: try
    char *gender = data[2];
    
    person_init(self, name, age, gender);

    for(int i=0; i<3; i++){
        free(data[i]);
    }

    return SUCCESS;
}

int person_print_data(Person *self){
    printf("Name: %s\tAge: %d \tGender: %s\n",
        self->name, self->age, self->gender);

    return SUCCESS;
}