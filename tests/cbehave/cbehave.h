/*
 * Copyright (c) 2011 Tony Bai <bigwhite.cn@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * @file cbehave.h
 *
 */

#ifndef _CBEHAVE_H
#define _CBEHAVE_H

#ifdef _cplusplus
extern "C" {
#endif

#include "apr_ring.h"

#define CBEHAVE_LOGO \
    "*******************************************************************\n\
\tCBEHAVE -- A Behavior Driven Development Framework for C\n\
\t\t\t By Tony Bai\n\
*******************************************************************"

#define CBEHAVE_MAX_NAME_LEN 128

typedef struct cbehave_state {
    int total_features;
    int failed_features;
    int total_scenarios;
    int failed_scenarios;
} cbehave_state;

#define GIVEN(x) \
    cbehave_given_entry(x, _state);
#define GIVEN_END \
    cbehave_given_exit(_state);

#define WHEN(x) \
    cbehave_when_entry(x, _state);
#define WHEN_END \
    cbehave_when_exit(_state);

#define THEN(x) \
    cbehave_then_entry(x, _state);
#define THEN_END \
    cbehave_then_exit(_state);

#define SCENARIO(x) { \
    int _scenario_state = 0; \
    cbehave_scenario_entry(x, _state);

#define SCENARIO_END \
    cbehave_scenario_exit(&_scenario_state, _state); \
}

#define FEATURE(idx, x) static void _cbehave_feature_##idx(void *_state) { \
    cbehave_state _old_state; \
    cbehave_feature_entry(x, &_old_state, _state);

#define FEATURE_END \
_feature_over: \
    cbehave_feature_exit(&_old_state, _state); \
}

#define FEATURE_RETURN(ret) {\
    cbehave_feature_return(__FILE__, __LINE__, ret, _state); \
    goto _feature_over; \
}
    
#define feature_idx(idx) _cbehave_feature_##idx

#define SHOULD_INT_EQUAL(actual, expected) do { \
    should_int_equal((actual), (expected), &_scenario_state, __FILE__, __LINE__); \
} while(0)

#define SHOULD_STR_EQUAL(actual, expected) do { \
    should_str_equal((actual), (expected), &_scenario_state, __FILE__, __LINE__); \
} while(0)

#define SHOULD_MEM_EQUAL(actual, expected, size) do { \
    should_mem_equal((actual), (expected), (size), &_scenario_state, __FILE__, __LINE__); \
} while(0)

#define SHOULD_BE_TRUE(actual) do { \
    should_be_true((actual), &_scenario_state, __FILE__, __LINE__); \
} while(0)

#define cbehave_runner(str, features) \
    _cbehave_runner(str, features, sizeof(features)/sizeof(features[0]))

typedef struct cbehave_feature {
    void (*func)(void *state);
} cbehave_feature;

int _cbehave_runner(const char *description, const cbehave_feature *features, int count);
void should_int_equal(int actual, int expected, 
                      void *state,
                      const char *file, int line);
void should_str_equal(const char *actual, const char *expected, void *state,
                      const char *file, int line);
void should_mem_equal(const void *actual, const void *expected, size_t size, void *state, 
                      const char *file, int line);
void should_be_true(int actual, void *state, const char *file, int line);

void cbehave_given_entry(const char *str, void *state);
void cbehave_when_entry(const char *str, void *state);
void cbehave_then_entry(const char *str, void *state);
void cbehave_scenario_entry(const char *str, void *state);
void cbehave_feature_entry(const char *str, void *old_state, void *state);

void cbehave_given_exit(void *state);
void cbehave_when_exit(void *state);
void cbehave_then_exit(void *state);
void cbehave_scenario_exit(void *scenario_state, void *state);
void cbehave_feature_exit(void *old_state, void *state);
void cbehave_feature_return(const char *file, int line, int ret, void *state);

/*
 * mock symbol list
 *
 * ------------
 * | symbol-#0|-> value_list
 * ------------
 * | symbol-#1|-> value_list
 * ------------
 * | symbol-#2|-> value_list
 * ------------
 * | ... ...  |-> value_list
 * ------------
 * | symbol-#n|-> value_list
 * ------------
 */

typedef struct cbehave_value_t {
    APR_RING_ENTRY(cbehave_value_t)    link;
    void                               *value;
} cbehave_value_t;
typedef APR_RING_HEAD(cbehave_value_head_t, cbehave_value_t) cbehave_value_head_t;

typedef struct cbehave_symbol_t {
    APR_RING_ENTRY(cbehave_symbol_t)   link;
    char                               desc[CBEHAVE_MAX_NAME_LEN];
    int                                obj_type;
    int                                always_return_flag; /* 1: always return the same value; 0(default) */
    void*                              value;
    cbehave_value_head_t               value_list;
} cbehave_symbol_t;
typedef APR_RING_HEAD(cbehave_symbol_head_t, cbehave_symbol_t) cbehave_symbol_head_t;

void* cbehave_mock_obj(const char *fcname, int lineno, const char *fname, int obj_type);
void cbehave_mock_obj_return(const char *symbol_name, void *value, const char *fcname,
                             int lineno, const char *fname, int obj_type, int count);

#define MOCK_ARG     0x0
#define MOCK_RETV    0x1

#define CBEHAVE_MOCK_ARG() cbehave_mock_obj(__FUNCTION__, __LINE__, __FILE__, MOCK_ARG)
#define CBEHAVE_MOCK_RETV() cbehave_mock_obj(__FUNCTION__, __LINE__, __FILE__, MOCK_RETV)

#define CBEHAVE_ARG_RETURN(fcname, value) do { \
    cbehave_mock_obj_return(#fcname, (void*)value, __FUNCTION__, __LINE__, __FILE__, MOCK_ARG, 1); \
} while(0);

#define CBEHAVE_ARG_RETURN_COUNT(fcname, value, count) do { \
    cbehave_mock_obj_return(#fcname, (void*)value, __FUNCTION__, __LINE__, __FILE__, MOCK_ARG, count); \
} while(0);

#define CBEHAVE_RETV_RETURN(fcname, value) do { \
    cbehave_mock_obj_return(#fcname, (void*)value, __FUNCTION__, __LINE__, __FILE__, MOCK_RETV, 1); \
} while(0);

#define CBEHAVE_RETV_RETURN_COUNT(fcname, value, count) do { \
    cbehave_mock_obj_return(#fcname, (void*)value, __FUNCTION__, __LINE__, __FILE__, MOCK_RETV, count); \
} while(0);


#ifdef _cplusplus
}
#endif

#endif /* _CBEHAVE_H */
