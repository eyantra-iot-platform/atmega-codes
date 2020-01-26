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
	// Initialized to input
	DDRH = DDRH & 0xC7;
	DDRE = DDRE & 0x7f;
	// enable pull-up on swithc
	PORTE = PORTE | 0x80;
}

int main(void) {
	rgb_led_init();
	while(1){
	}
	return 0;	
}
