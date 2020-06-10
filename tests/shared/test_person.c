#include <stdio.h>
#include <assert.h>

#include "..\..\domain\shared\person.h"

int main(){
    struct Person person_one = {"Lisa", 12, "female"};

    assert(person_one.name == "Lisa");
    assert(person_one.age == 12);
    assert(person_one.gender == "female");
}