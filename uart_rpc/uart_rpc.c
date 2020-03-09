#include "eyfi_mega.h"

#include "uart.h"
#include "oled.h"
#include "mcp23017.h"

#include "avr_rpc_utils.h"
#include "rpc_common.h"

uint16_t rx_byte;

/*
Clear and print message
*/
void lcd_print(char* message) {
	oled_clrscr();
	oled_puts(message);
	// oled_display();
}

double get_flow() {
	return 5.72;
}

void rpc_handler(char method, int req_id, char* params) {
	char response[100], response_params[40];

	if (method == 65) {
		encode_params(response_params, 0,"%lf", get_flow());
		create_rpc_response(response, method, req_id, response_params);
		uart0_puts(response);
	}
	else if (method == 30) {
		int red_i;
		if (sscanf(params, "d%d", &red_i) == 1) {
			brightness(red_i, 0, 0);
			encode_params(response_params, 0, "%d", red_i);
			create_rpc_response(response, method, req_id, response_params);
			uart0_puts(response);
		}
	}
	else if (method == 31) {
		int green_i;
		if (sscanf(params, "d%d", &green_i) == 1) {
			brightness(0, green_i, 0);
			encode_params(response_params, 0, "%d", green_i);
			create_rpc_response(response, method, req_id, response_params);
			uart0_puts(response);
		}
	}
	else if (method == 32) {
		int blue_i;
		if (sscanf(params, "d%d", &blue_i) == 1) {
			brightness(0, 0, blue_i);
			encode_params(response_params, 0, "d%d", blue_i);
			create_rpc_response(response, method, req_id, response_params);
			uart0_puts(response);
		}
	}
	else if (method == 33) {
		int red_i, green_i, blue_i;
		if (sscanf(params, "d%d,d%d,d%d", &red_i, &green_i, &blue_i) == 3) {
			brightness(red_i, green_i, blue_i);
			encode_params(response_params, 0, "%d%d%d", red_i, green_i, blue_i);
			create_rpc_response(response, method, req_id, response_params);
			uart0_puts(response);
		}
	}
	else if (method == 40) {
		char message[40];
		if (sscanf(params, "s%s", message) == 1) {
			lcd_print(message);
			encode_params(response_params, 0, "%s", message);
			create_rpc_response(response, method, req_id, response_params);
			uart0_puts(response);
		}
	}
	else if (method == 41) {
		unsigned char lfa = mcp23017_readpinsA(0b000);
		encode_params(response_params, 0, "%d", lfa);
		create_rpc_response(response, method, req_id, response_params);
		uart0_puts(response);
	}
	else {
		uart0_puts("Invalid method!\n");
		sprintf(response, "#%d%s@", method, params);
		uart0_puts(response);
	}
	// Add for OLED
	// Add for Joystick
	// Add for Line Follower Array
}


int main(void) {
	// OLED INIT
	oled_init(OLED_DISP_ON);
	oled_clrscr();
	oled_charMode(NORMALSIZE);
	oled_puts("Init'ed"); 

	// LFA INIT
	mcp23017_init();
	unsigned int address = 0b000;
	mcp23017_setmodeA(address, MCP23017_MODEINPUTALL);
	// mcp23017_setmodeB(address, MCP23017_MODEOUTPUTALL);

	mcp23017_setmodepinB(address, 0, MCP23017_MODEOUTPUT);
	mcp23017_setmodepinB(address, 1, MCP23017_MODEOUTPUT);

	// mcp23017_writepinsB(address, MCP23017_PINSTATEOFFALL);
	mcp23017_writepinB(address, 0, MCP23017_PINSTATEOFF);
	mcp23017_writepinB(address, 1, MCP23017_PINSTATEOFF);

	// UART INIT
	uart0_init(UART_BAUD_SELECT(9600, F_CPU));
	uart0_flush();
	uart0_puts("ATMega2560 UART0 says Hi!!\n");

	rgb_led_init();
	
	while(1) {
		char method;
		int req_id;
		char request[100], params[100], response[100];

		int did_fetch = fetch_rpc_request(request, uart0_getc);
		sprintf(response, "Echo from AVR [%s]", request);
		uart0_puts(response);

		// sprintf(response, "Did fetch: %d", did_fetch);
		// uart0_puts(response);

		if (did_fetch) {
			int success = parse_rpc_request(&method, &req_id, params, request);
			// sprintf(response, "Did parse request succeed: %d", success);
			// uart0_puts(response);
			
			if (!success) continue;
			
			// sprintf(response, "Method: %d Req_id: %d Params: %s", method, req_id, params);
			// uart0_puts(response);
			
			rpc_handler(method, req_id, params);
		}
	}
	return 0;
}
