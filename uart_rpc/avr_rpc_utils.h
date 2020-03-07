#ifndef AVR_RPC_UTILS_H
#define AVR_RPC_UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Fetch and stores UART-RPC request message in a char array.

If not UART-RPC message returns with a code of 0, in which case message
contains the received character.

Returns -1 if error 
*/
int fetch_rpc_request(char* message, unsigned short (*get_data)());

int fetch_rpc_response(char* message, unsigned short (*get_data)());

#endif