// #define F_CPU 16000000

#include "eyfi_mega.h"
#include "uart.h"
#include "avr_rpc_utils.h"
#include "oled.h"

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

int main(void) {
	oled_init(OLED_DISP_ON);
	oled_clrscr();
	oled_charMode(DOUBLESIZE);
	oled_puts("e-Yantra"); 

	uart0_init(UART_BAUD_SELECT(9600, F_CPU));
	uart0_flush();
	uart0_puts("ATMega2560 UART0 says Hi!!\n");

	rgb_led_init();
	
	while(1) {
		int status;
		char request[100], params[100];
		char response[100];
		char method;

		status = fetch_rpc_request(request, uart0_getc);
		sprintf(response, "Request without start-stop [%s]", request);
		uart0_puts(response);

		if (status == -1) {
			continue;
		}

		if (status == 0) {
			// uart0_puts(message);
			continue;
		}

		int success = parse_rpc_request(&method, params, request);
		// sprintf(response, "Is true: %d, m: %d, p: %s\n", success, method, params);
		// uart0_puts(response);

		if (method == 65) {
			encode_params(params, 0,"%lf", get_flow());
    		create_rpc_response(response, method, params);
			uart0_puts(response);
		}
		else if (method == 30) {
			int red_i;
			if (sscanf(params, "d%d", &red_i) == 1) {
				brightness(red_i, 0, 0);
				encode_params(params, 0, "%d", red_i);
				create_rpc_response(response, method, params);
				uart0_puts(response);
			}
		}
		else if (method == 31) {
			int green_i;
			if (sscanf(params, "d%d", &green_i) == 1) {
				brightness(0, green_i, 0);
				encode_params(params, 0, "%d", green_i);
				create_rpc_response(response, method, params);
				uart0_puts(response);
			}
		}
		else if (method == 32) {
			int blue_i;
			if (sscanf(params, "d%d", &blue_i) == 1) {
				brightness(0, 0, blue_i);
				encode_params(params, 0, "d%d", blue_i);
				create_rpc_response(response, method, params);
				uart0_puts(response);
			}
		}
		else if (method == 33) {
			int red_i, green_i, blue_i;
			if (sscanf(params, "d%d,d%d,d%d", &red_i, &green_i, &blue_i) == 3) {
				brightness(red_i, green_i, blue_i);
				encode_params(params, 0, "%d%d%d", red_i, green_i, blue_i);
				create_rpc_response(response, method, params);
				uart0_puts(response);
			}
		}
		else if (method == 40) {
			char message[40];
			if (sscanf(params, "s%s", message) == 1) {
				lcd_print(message);
			}
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
	return 0;
}
