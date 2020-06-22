#include <stdio.h>
#include <errno.h>

#include "../include/macro.h"
#include "cbehave/cbehave.h"
#include "../include/person.h"

FEATURE(1, "Test person_get_..")
    Person *someone = person_create();

    SCENARIO("The person_get_.. return the data of a Person.")

        GIVEN("There is a Person which have been created.")
        GIVEN_END

        WHEN("We initate someone with valid data.")
            person_init(someone, "Lisa", 12, "female");
        WHEN_END

        THEN("We should get the data of someone by using person_get_..")
            SHOULD_STR_EQUAL(person_get_name(someone), "Lisa");
            SHOULD_INT_EQUAL(person_get_age(someone), 12);
            SHOULD_STR_EQUAL(person_get_gender(someone), "female");
        THEN_END

    SCENARIO_END

    person_destroy(someone);
FEATURE_END


FEATURE(2, "Test person_init")
    Person *someone = person_create();

    SCENARIO("Initiate with valid data.")

        GIVEN("Name : Lisa, age : 12, gender : female.")
        GIVEN_END

        WHEN("We use person_init to initiate a Person.")
            person_init(someone, "Lisa", 12, "female");
        WHEN_END

        THEN("We should get the data of someone.")
            SHOULD_STR_EQUAL(person_get_name(someone), "Lisa");
            SHOULD_INT_EQUAL(person_get_age(someone), 12);
            SHOULD_STR_EQUAL(person_get_gender(someone), "female");
        THEN_END

    SCENARIO_END

    SCENARIO("Initiate with invalid age.")

        GIVEN("Name : Lisa, age : -3, gender : female.")
        GIVEN_END

        WHEN("We initiate someone with age out of range.")
            int state = person_init(someone, "Lisa", -3, "female");
        WHEN_END

        THEN("We should get INVALID_AGE.")
            SHOULD_INT_EQUAL(state, INVALID_AGE);
        THEN_END

    SCENARIO_END

    SCENARIO("Initiate with invalid gender.")

        GIVEN("Name : Lisa, age : 12, gender : fema.")
        GIVEN_END

        WHEN("We initiate someone with age out of range.")
            int state = person_init(someone, "Lisa", 12, "fema");
        WHEN_END

        THEN("We should get INVALID_GENDER.")
            SHOULD_INT_EQUAL(state, INVALID_GENDER);
        THEN_END

    SCENARIO_END

    person_destroy(someone);
FEATURE_END

FEATURE(3, "Test person_init_from_string")
    Person *someone = person_create();

    SCENARIO("Use valid string with 3 parts spilted by 2 commas.")

        GIVEN("There is a const string: Lisa, 12,female.")
            const char *line = "Lisa, 12,female";
        GIVEN_END

        WHEN("We initiate someone with line.")
            person_init_from_string(someone, line);
        WHEN_END

        THEN("We should get someone initiated.")
            SHOULD_STR_EQUAL(person_get_name(someone), "Lisa");
            SHOULD_INT_EQUAL(person_get_age(someone), 12);
            SHOULD_STR_EQUAL(person_get_gender(someone), "female");
        THEN_END

    SCENARIO_END

    person_destroy(someone);
FEATURE_END

int main(){
    cbehave_feature person_features[] = {
        {feature_idx(1)}, {feature_idx(2)}, {feature_idx(3)}
    };

    return cbehave_runner("Person Features are as belows:", person_features);
}