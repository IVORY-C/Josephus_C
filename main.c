#include <stdio.h>
#include <stdlib.h>

#include "domain/person.h"
#include "domain/josephus.h"
#include "domain/readers.h"


int main(){
    int start = 2;
    int step = 2;
    int number = 5;
    char *path = (char *)malloc(100 * sizeof(char));
    path = "data/people.csv";

    Person **people = (Person **)malloc(number * sizeof(Person*));
    for(int i; i < number; i++){
        person_init(people[i]);
    }//只有people里边含有具体数据，别的数组均仅包含指针。

    Person **results = (Person **)malloc(number * sizeof(Person*));

    readers_create_people_from_txt_or_csv(people, path);
    
    Josephus *ring;
    josephus_init(ring);
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
    free(people);
    free(results);

    return 0;
}