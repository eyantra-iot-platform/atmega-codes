#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Fetch and stores UART-RPC request message in a char array.

If not UART-RPC message returns with a code of 0, in which case message
contains the received character.

Returns -1 if error 
*/
int fetch_rpc_request(char* message, unsigned short (*get_data)());

/* Parse UART-RPC request message */
int parse_rpc_request(char* method, const char* params, const char* message);

/*
Encode parameters of a UART-RPC message, both request and response
*/
void encode_params(char* params, const char* fmt, ...);

/* Create UART-RPC response message */
int create_rpc_response(char* response, const char method, const char* params);

#endif
