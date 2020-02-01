#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

void solenoid_init() {
	// PORTA 0, 1, 2
	// Initialized to input
	DDRA = DDRA | 0x07;
	PORTA = PORTA & 0xf8;
	// enable pull-up on swithc
	// PORTE = PORTE | 0x80;
}

int main(void) {
	solenoid_init();
	while(1) {
		PORTA = 0x06;
		_delay_ms(1500);
		PORTA = 0x00;

		_delay_ms(3000);

		PORTA = 0x05;
		_delay_ms(1500);
		PORTA = 0x00;

		_delay_ms(3000);
	}
	return 0;
}
