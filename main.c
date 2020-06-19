#include <stdio.h>
#include <stdlib.h>

#include "domain/macro.h"
#include "domain/person.h"
#include "domain/josephus.h"
#include "domain/readers.h"


int main(){
    int start = 2;
    int step = 2;
    int number = 5;
    char *path = (char *)malloc(MAX_CHAR * sizeof(char));
    path = "data/people.csv";

    SPerson **people = (SPerson **)malloc(number * sizeof(SPerson*));
    for(int i; i < number; i++){
        person_create(people[i]);
    // }//只有people里含有具体数据,需分配Person的空间，别的数组均仅包含指针?

    SPerson **results = (SPerson **)malloc(number * sizeof(SPerson *));

    readers_create_people_from_txt_or_csv(people, path);
    
    SJosephus *ring;
    josephus_create(ring);
    josephus_set(ring, start, step, number);
    josephus_input_people(ring, people);

    printf("%s", "The input people:\n");
    josephus_quary(ring); 

    printf("%s", "---------------\n");

    printf("%s", "The output results:\n");
    josephus_output_results(ring, results);

    for(int i = 0; i < josephus_get_number(ring); i++){
        person_print_data(results[i]);
    }
    
    josephus_destroy(ring); 
    free(path);
    free(results);
    free(people);
    for(int i = 0; i < MAX; i++){
        person_destroy(people[i]);
    }

    return 0;
}