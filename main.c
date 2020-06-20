#include <stdio.h>
#include <stdlib.h>

#include "domain/m-array.h"
#include "domain/macro.h"
#include "domain/person.h"
#include "domain/josephus.h"
#include "domain/readers.h"


int main(){
    Reader *reader = reader_create();
    reader_init(reader, 20, "data/people.csv");
    reader_append_lines_from_file(reader);

    char **lines = reader_get_lines(reader);
    printf("----------\nThe lines:\n");
    for(int i = 0; i < reader_get_number(reader); i++){
        printf("%s", lines[i]);
    }
    printf("----------\n");

    Josephus *ring = josephus_create();
    josephus_init(ring, 2, 2, 10);

    for(int i = 0; i < reader_get_number(reader); i++){
        Person *someone = person_create();
        person_init_from_string(someone, lines[i]);
        josephus_append(ring, someone);
    }

    printf("The people in ring:\n");
    josephus_query(ring);
    printf("----------\n");

    printf("The results:\n");
    Person *next_person = person_create();
    while(josephus_get_number(ring) > 0){
        next_person = josephus_output_next(ring);
        person_print_data(next_person);
    }

    person_destroy(next_person);
    reader_destroy(reader);
    josephus_destroy(ring);
}
