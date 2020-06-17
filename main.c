#include <stdio.h>
#include <stdlib.h>

#include "domain/person.h"
#include "domain/josephus.h"
#include "domain/readers.h"


int main() {
    int start = 2;
    int step = 2;
    int number = 5;
    char* path = (char*)"data/people.csv";

    Person people[100];
    Person results[100];

    readers_create_people_from_txt_or_csv(people, path);

    Josephus* ring = (Josephus*)malloc(sizeof(Josephus*));
    josephus_new(ring, 2, 2, 5);
    josephus_input_people(ring, people);

    printf("%s", "The input people:\n");
    josephus_quary(ring); 

    printf("%s", "---------------\n");

    printf("%s", "The output results:\n");
    josephus_output_results(ring, results);

    for(int i = 0; i < ring->number; i++){
        person_print_data(results + i);
    }
    
    josephus_destroy(ring); 

    return 0;
}