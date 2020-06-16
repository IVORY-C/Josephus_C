#include <stdio.h>
#include <stdlib.h>

#include "domain/shared/person.h"
#include "domain/use_cases/josephus.h"
#include "domain/adapter/readers.h"


int main() {
    int start = 2;
    int step = 2;
    int number = 5;
    char* path = (char*)"data/people.csv";

    Person people[100];
    Person results[100];

    readers_create_people_from_txt_or_csv(people, path);

    Josephus ring;
    josephus_new(&ring, 2, 2, 5);
    josephus_input_people(&ring, people);
    josephus_quary(&ring); 
    printf("%s", "---------------");
    josephus_output_results(&ring, results);

    for(int i = 0; i < ring.number; i++){
        person_print_data(results + i);
    }
    
    josephus_destroy(&ring); 

    return 0;
}