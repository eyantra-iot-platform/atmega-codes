#include "eyfi_mega.h"
#include "uart.h"
#include "utils.h"

uint16_t rx_byte;

int main(void) {
	uart0_init(UART_BAUD_SELECT(9600, F_CPU));
	uart0_flush();
	uart0_puts("ATMega2560 UART0 says Hi!!\n");

	rgb_led_init();
	
	while(1) {
		int status;
		char message[100], params[100];
		char method;

		status = fetch_rpc_request(message, uart0_getc);

		if (status == -1)
			continue;

		if (status == 0) {
			uart0_puts(message);
			continue;
		}

		parse_rpc_request(&method, params, message);
		
		if (method == 20) {
			double flow_readings = 7.65;
			char response[100];
			create_rpc_response(response, method, "d7.65");
			uart0_puts(response);
		}
		else if (method == 30) {
			int red_i;
			if (sscanf(params, "i%d", &red_i) == 1) {
				brightness(red_i, 0, 0);
				// uart0_puts("#%ci255@");
			}
		}
		else if (method == 31) {
			int green_i;
			if (sscanf(params, "i%d", &green_i) == 1) {
				brightness(0, green_i, 0);
			}
		}
		else if (method == 32) {
			int blue_i;
			if (sscanf(params, "i%d", &blue_i) == 1) {
				brightness(0, 0, blue_i);
			}
		}
		else if (method == 33) {
			int red_i, green_i, blue_i;
			if (sscanf(params, "i%d,i%d,i%d", &red_i, &green_i, &blue_i) == 3) {
				brightness(red_i, green_i, blue_i);
			}
		}
	}
	return 0;	
}
