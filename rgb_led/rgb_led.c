/*
 * TITLE:
 * DATE:
 * AUTHOR:
 */ 


#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

void rgb_led_init() {
	// PORTH 3 - R; 5 - G; 4 - B
	DDRH = DDRH | 0x38;
	PORTH = PORTH | 0x38;
}

void glow_off() {
	PORTH = PORTH | 0x38;
}

void glow_red() {
	glow_off();
	PORTH = PORTH & 0xf7;
}

void glow_green() {
	glow_off();
	PORTH = PORTH & 0xdf;
}

void glow_blue() {
	glow_off();
	PORTH = PORTH & 0xef;
}

int main(void) {
	rgb_led_init();
	while(1){
		glow_red();
		_delay_ms(2000);

		glow_green();
		_delay_ms(2000);

		glow_blue();
		_delay_ms(2000);
	}
	return 0;	
}
