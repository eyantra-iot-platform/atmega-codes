#include <stdio.h>

#include "unity.h"
#include "utils.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_encode_params(void) {
    //more test stuff
    char param[50] = "";
    int val = 51;
    long long lng_val = 561551455321;
    char str[10] = "hello";

    encode_params(param, "%d%ld%s", val, lng_val, str);
    TEST_ASSERT_EQUAL_STRING("d51,ld561551455321,shello", param);

    param[0] = '\0';
    encode_params(param, "%d%ld%d%c", 8451, 4294912712, 25, 'a');
    TEST_ASSERT_EQUAL_STRING("d8451,ld4294912712,d25,ca", param);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_encode_params);
    // RUN_TEST(test_function_encode_params);
    return UNITY_END();
}
