#include "avr_rpc_utils.h"

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

int fetch_rpc_response(char* message, unsigned short (*get_data)()) {
    return fetch_rpc_request(message, get_data);
}
