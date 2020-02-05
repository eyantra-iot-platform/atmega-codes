#include <stdio.h>

#include "unity.h"
#include "utils.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_create_rpc_response(void) {
    char method, params[100], response[100];
    double flow_readings = 7.65;
    // create_rpc_response(response, 65, "f-1.25,d-45,shello,d87");
    encode_params(params, "%lf", flow_readings);
    create_rpc_response(response, 65, params);

    TEST_ASSERT_EQUAL_STRING("#Alf7.650@\0", response);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_create_rpc_response);
    // RUN_TEST(test_function_encode_params);
    return UNITY_END();
}
