#include <stdio.h>

#include "unity.h"
#include "rpc_common.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_simple(void) {
    int req_id;
    char method, params[100];

    int status = parse_rpc_request(&method, &req_id, params, "!55d-1.25i-45shelloi87");

    TEST_ASSERT_EQUAL_INT(1, status);
    TEST_ASSERT(method == 33);
    TEST_ASSERT_EQUAL_INT(55, req_id);
    TEST_ASSERT_EQUAL_STRING("d-1.25i-45shelloi87", params);
}

void test_failure(void) {
    int req_id;
    char method, params[100];

    int status = parse_rpc_request(&method, &req_id, params, " uid-1.25i-45shelloi87");

    TEST_ASSERT_EQUAL_INT(0, status);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_simple);
    RUN_TEST(test_failure);
    return UNITY_END();
}
