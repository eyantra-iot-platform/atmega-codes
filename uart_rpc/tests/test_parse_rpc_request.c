#include <stdio.h>

#include "unity.h"
#include "utils.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_parse_rpc_request(void) {
    char method, params[100];
    int status = parse_rpc_request(&method, params, " d-1.25i-45shelloi87");

    TEST_ASSERT_EQUAL_INT(status, 1);
    TEST_ASSERT(method == ' ');
    TEST_ASSERT_EQUAL_STRING("d-1.25i-45shelloi87", params);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_parse_rpc_request);
    // RUN_TEST(test_function_encode_params);
    return UNITY_END();
}
