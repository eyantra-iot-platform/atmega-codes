#include <stdio.h>

#include "unity.h"
#include "rpc_common.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_create_rpc_response(void) {
    double flow_readings = 7.65;
    char method = 65;
    char response[100], params[100];
    int req_id = 5601;
    encode_params(params, 0, "%lf", flow_readings);
    create_rpc_response(response, method, req_id, params);
    TEST_ASSERT_EQUAL_STRING("#A5601lf7.650@", response);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_create_rpc_response);
    // RUN_TEST(test_function_encode_params);
    return UNITY_END();
}
