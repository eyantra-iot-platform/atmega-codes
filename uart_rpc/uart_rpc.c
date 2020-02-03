#include "eyfi_mega.h"
#include "uart.h"

uint16_t rx_byte;

int main(void) {
	uart0_init(UART_BAUD_SELECT(9600, F_CPU));
	uart0_flush();
	uart0_puts("ATMega2560 UART0 says Hi!!\n");

	rgb_led_init();
	
	while(1) {
		int i = 0, START_PRC = 0;
		char message[60];
		rx_byte = uart0_getc();
		
		if ((rx_byte & 0xFF00) == UART_NO_DATA)
			continue;
		
		rx_byte = rx_byte & 0x00FF;
		uart0_putc((char)rx_byte);
		if ((char)rx_byte == '#') {
			i = 0;
			do {
				uint8_t recv_byte;
				rx_byte = uart0_getc();
				if ((rx_byte & 0xFF00) != 0)
					continue;
				
				recv_byte = rx_byte & 0x00FF;
				if (recv_byte == '#') {
					i = 0;
					continue;
				} 
				
				if (recv_byte == '@') {
					START_PRC = 1;
					break;
				}
				else {
					message[i++] = recv_byte;
				}
			} while ((char) rx_byte != '@');

			message[i] = '\0';
			uart0_puts(message);

			if (START_PRC == 0)
				continue;

			// start process
			switch (message[0]) {
				case 30:
				{
					red_led_on();
					green_led_off();
					blue_led_off();
					break;
				}
				case 31:
				{
					red_led_off();
					green_led_on();
					blue_led_off();
					break;
				}
				case 32:
				{
					red_led_off();
					green_led_off();
					blue_led_on();
					break;
				}
				default: break;
			}
		}
	}
	return 0;	
}
