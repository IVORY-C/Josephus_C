#include <stdio.h>
#include <stdlib.h>

#include "include/m-array.h"
#include "include/macro.h"
#include "include/person.h"
#include "include/josephus.h"
#include "include/readers.h"


int main(){
    // 创建reader
    Reader *reader = reader_create();
    reader_init(reader, 20, "data/people.csv");
    reader_append_lines_from_file(reader);

    printf("----------\nThe lines:\n");
    for(int i = 0; i < reader_get_number(reader); i++){
        printf("%s", reader_get_lines(reader, i));
    }
    printf("----------\n");

    // 创建ring
    Josephus *ring = josephus_create();
    josephus_init(ring, 2, 2, 10);

    for(int i = 0; i < reader_get_number(reader); i++){
        Person *someone = person_create();
        person_init_from_string(someone, reader_get_lines(reader, i));
        josephus_append(ring, someone);
    }

    printf("The people in ring:\n");
    josephus_query(ring);
    printf("----------\n");

    // 输出结果
    printf("The results:\n");
    Person *next_person = person_create();
    while(josephus_get_size_of_people(ring) > 0){
        next_person = josephus_output_next(ring);
        person_print_data(next_person);
    }

    // destroy
    person_destroy(next_person);
    reader_destroy(reader);
    josephus_destroy(ring);
}
