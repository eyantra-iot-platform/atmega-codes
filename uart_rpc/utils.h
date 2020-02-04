#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>

/* Fetch and stores UART-RPC request message in a char array.

If not UART-RPC message returns with a code of 0, in which case message
contains the received character.

Returns -1 if error 
*/
int fetch_rpc_request(char* message, unsigned short (*get_data)());

/* Parse UART-RPC request message */
int parse_rpc_request(char* method, char* params, char* message);

/*
Encode parameters of a UART-RPC message, both request and response
*/
void encode_params(char* param, char* data_type, void* value);

/*
Concatenate parameters of a UART-RPC message, both request and response,
with a delimeter.
*/
void concat_params(char* result, char* param1, char* param2);

/* Create UART-RPC response message */
int create_rpc_response(char* response, char method, char* params);

#endif
