#include <stdio.h>

#include "unity.h"
#include "avr_rpc_utils.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_fetch_rpc_request_ideal(void) {
    char message[100];
    
    short bytes[] = {0x0023, 'a', 'b', 'd', 87, '@', '\0'};
    unsigned short uart0_getc() {
        static int i = 0;
        return bytes[i++];
    }

    int status = fetch_rpc_request(message, uart0_getc);

    TEST_ASSERT_EQUAL_INT(status, 1);
    TEST_ASSERT_EQUAL_STRING("abdW", message);
}

void test_function_fetch_rpc_request_no_data(void) {
    char message[100];
    
    short bytes[] = {0x0100, 0x0100, 0x0023, 0x001E, 'i', '-',  0x0100, '5', 0x0100, 'd', 87, '@', '\0'};
    unsigned short uart0_getc() {
        static int i = 0;
        return bytes[i++];
    }

    int status = fetch_rpc_request(message, uart0_getc);

    TEST_ASSERT_EQUAL_INT(status, 1);
    TEST_ASSERT_EQUAL_STRING("\x1Ei-5dW", message);
}

void test_function_fetch_rpc_request_exit_on_error(void) {
    char message[100];
    
    short bytes[] = {0x0100, 0x0100, 0x0023, 0x101E, 'i', '-',  0x0100, '5', 0x0100, 'd', 87, '@', '\0'};
    unsigned short uart0_getc() {
        static int i = 0;
        return bytes[i++];
    }

    int status = fetch_rpc_request(message, uart0_getc);

    TEST_ASSERT_EQUAL_INT(status, -1);
    TEST_ASSERT_EQUAL_STRING("", message);
}

void test_function_fetch_rpc_request_double_start(void) {
    char message[100];
    
    short bytes[] = {0x0100, 0x0100, 0x0023, 'i', '-', 0x0023, 'h', 'o', 'l', 'a', 0x0100, '5', 0x0100, 'd', 87, '@', '\0'};
    unsigned short uart0_getc() {
        static int i = 0;
        return bytes[i++];
    }

    int status = fetch_rpc_request(message, uart0_getc);

    TEST_ASSERT_EQUAL_INT(status, 1);
    TEST_ASSERT_EQUAL_STRING("hola5dW", message);
}

void test_function_fetch_rpc_request_ends_with_null(void) {
    char message[100];
    
    short bytes[] = {0x0100, 0x0100, 0x0023, 'i', '-', 0x0023, 'a', 0x0100, 'n', 'd', 'y', 0x0100,
    '5', 0x0100, 'd', 87, '\0', 'a', 'b'};

    unsigned short uart0_getc() {
        static int i = 0;
        return bytes[i++];
    }

    int status = fetch_rpc_request(message, uart0_getc);

    TEST_ASSERT_EQUAL_INT(status, 1);
    TEST_ASSERT_EQUAL_STRING("andy5dW", message);
}

void test_function_fetch_rpc_request_non_rpc_message(void) {
    char message[100];
    
    short bytes[] = {0x0100, 0x0100, 'i', '-', 0x0023, 'a', 0x0100, 'n', 'd', 'y', 0x0100,
    '5', 0x0100, 'd', 87, '\0', 'a', 'b'};

    unsigned short uart0_getc() {
        static int i = 0;
        return bytes[i++];
    }

    int status = fetch_rpc_request(message, uart0_getc);

    TEST_ASSERT_EQUAL_INT(status, 0);
    TEST_ASSERT_EQUAL_STRING("i", message);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_fetch_rpc_request_ideal);
    RUN_TEST(test_function_fetch_rpc_request_no_data);
    RUN_TEST(test_function_fetch_rpc_request_double_start);
    RUN_TEST(test_function_fetch_rpc_request_exit_on_error);
    RUN_TEST(test_function_fetch_rpc_request_ends_with_null);
    RUN_TEST(test_function_fetch_rpc_request_non_rpc_message);
    // RUN_TEST(test_function_encode_params);
    return UNITY_END();
}
