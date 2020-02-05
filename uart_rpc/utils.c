#include "utils.h"

int fetch_rpc_request(char* message, unsigned short (*get_data)()) {
    int START_PRC = 0;
    int i = 0;
    unsigned char recv_byte;
    unsigned short recv_packet = get_data(); // packet contains error_code and data

    while ((recv_packet & 0xFF00) == 0x0100) {
        recv_packet = get_data();
    }
    
    if ((recv_packet & 0xFF00) != 0)
        return -1;

    recv_byte = recv_packet & 0x00FF;
    
    if (recv_byte != '#') {
        message[0] = recv_byte;
        message[1] = '\0';
        return 0;
    }

    while (recv_byte != '@') {
        recv_packet = get_data();
        
        // if no data, continue
        if ((recv_packet & 0xFF00) == 0x0100)
            continue;

        // if any other error, return -1
        if ((recv_packet & 0xFF00) != 0)
            return -1;
        
        recv_byte = recv_packet & 0x00FF;
        
        if (recv_byte == '\0') {// || recv_byte == '\r' || recv_byte == '\n') {
            break;
        }
        else if (recv_byte == '#') {
            i = 0;
        } 
        else if (recv_byte == '@') {
            START_PRC = 1;
        }
        else {
            message[i++] = recv_byte;
        }
    }
    message[i] = '\0';
    return 1;
}

int parse_rpc_request(char* method, const char* params, const char* message) {
    return (sscanf(message, "%c%s", method, params) == 2);
}

void encode_params(char* params, const char* fmt, ...) {
    // every param has a type and a value
    // supported types
    // int -> i; double -> d; string -> s
    // separator is a hash
    // order of parameters matters
    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0') {
        char str_repr[30], first_char;
        int UNKWN = 0;

        if (*fmt != '%') {
            fmt++;
            continue;
        }

        first_char = *++fmt;

        if (first_char == 'd') {
            int value = va_arg(args, int);
            sprintf(str_repr, "d%d", value);
        } else if (first_char == 's') {
            sprintf(str_repr, "s%s", va_arg(args, char*));
        } else if (first_char == 'c') {
            sprintf(str_repr, "c%c", va_arg(args, int));
        } else if (first_char == 'f') {
            sprintf(str_repr, "f%.3f", va_arg(args, double));
        } else if (first_char == 'l') {
            // NOT TESTED
            if (*(fmt+1) == 'f')
                sprintf(str_repr, "lf%.3lf", va_arg(args, double));
            else if (*(fmt+1) == 'd')
                sprintf(str_repr, "ld%ld", va_arg(args, long));
        } else {
            UNKWN = 1;
        }

        if (UNKWN == 0) {
            // return count for correctly parsed variables; count++;
            if (strlen(params) != 0)
                sprintf(params, "%s,%s", params, str_repr);
            // printf("%d %s\n", strlen(params), str_repr);
            else
                strcpy(params, str_repr);
        }
        
        fmt++;
    }

    va_end(args);
}

int create_rpc_response(char* response, const char method, const char* params) {
    sprintf(response, "#%c%s@", method, params);
}
