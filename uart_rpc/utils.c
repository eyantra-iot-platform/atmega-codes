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

int parse_rpc_request(char* method, char* params, char* message) {
    return (sscanf(message, "%c%s", method, params) == 2);
}

void encode_params(char* param, char* data_type, void* value) {
  // every param has a type and a value
  // supported types
  // int -> i; double -> d; string -> s
  // separator is a hash
  // order of parameters matters
  if (!strcmp(data_type, "int")) {
    int* int_val = (int*)value;
    sprintf(param, "i%d", *int_val);
  }
  else if (!strcmp(data_type, "double")) {
    double* dbl_val = (double*)value;
    sprintf(param, "d%.3lf", *dbl_val);
  }
  else if (!strcmp(data_type, "string")) {
    char* conv_val = (char*)value;
    sprintf(param, "s%s", conv_val);
  }
}

void concat_params(char* result, char* param1, char* param2) {
    sprintf(result, "%s,%s", param1, param2);
}

int create_rpc_response(char* response, char method, char* params) {
    sprintf(response, "#%c%s@", method, params);
}