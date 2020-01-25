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
	// enable pull-ups
	// PORTH = PORTH | 0x38;
}

int main(void) {
	rgb_led_init();
	while(1){
	}
	return 0;	
}
