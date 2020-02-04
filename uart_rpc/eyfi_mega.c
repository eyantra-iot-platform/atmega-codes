
/*
* 
* Name:           eYFi-Mega Header file (eyfi_mega.c)
* Version:        0.1
* Author Name:    e-Yantra Team (Rutuja Ekatpure, Kalind Karia)
* Last Modified:  24-01-2020
* 
*/


#include "eyfi_mega.h"


/**************************************************************************************************
								void rgb_led_init()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Initialize the RGB LED (Common Anode) Port Pins and initially turn it OFF
* 
***************************************************************************************************/

static void timer4_init()
{
	cli(); //disable all interrupts
	
	TCCR4B = 0x00;	//Stop
	
	TCNT4H = 0xFF;	//Counter higher 8-bit value to which OCR5xH value is compared with
	TCNT4L = 0x00;	//Counter lower 8-bit value to which OCR5xH value is compared with
	
	OCR4AH = 0x00;	//Output compare register high value for Red Led
	OCR4AL = 0xFF;	//Output compare register low value for Red Led
	
	OCR4BH = 0x00;	//Output compare register high value for Blue Led
	OCR4BL = 0xFF;	//Output compare register low value for Blue Led

	OCR4CH = 0x00;	//Output compare register high value for Green Led
	OCR4CL = 0xFF;	//Output compare register low value for Green Led
	
	//  Clear OC4A, OC4B & OC4C on compare match (set output to low level)
	TCCR4A |= (1 << COM4A1) | (1 << COM4B1) | (1 << COM4C1);
	TCCR4A &= ~((1 << COM4A0) | (1 << COM4B0) | (1 << COM4C0));

	// FAST PWM 8-bit Mode
	TCCR4A |= (1 << WGM40);
	TCCR4A &= ~(1 << WGM41);
	TCCR4B |= (1 << WGM42);
	
	// Set Prescalar to 64
	TCCR4B |= (1 << CS41) | (1 << CS40);
	TCCR4B &= ~(1 << CS42);
	
	sei(); //re-enable interrupts
}

void rgb_led_init()
{
    // update the data directions of RED_LED_PIN, GREEN_LED_PIN, BLUE_LED_PIN as OUTPUT
    update_bit( RGB_LED_DDR_REG, RED_LED_PIN, PIN_OUTPUT );
    update_bit( RGB_LED_DDR_REG, GREEN_LED_PIN, PIN_OUTPUT );
    update_bit( RGB_LED_DDR_REG, BLUE_LED_PIN, PIN_OUTPUT );
    
    // update the initial state of RED_LED_PIN, GREEN_LED_PIN, BLUE_LED_PIN as OFF
    // the RGB LED is Common Anode type
    update_bit( RGB_LED_PORT_REG, RED_LED_PIN, PIN_HIGH );
    update_bit( RGB_LED_PORT_REG, GREEN_LED_PIN, PIN_HIGH );
    update_bit( RGB_LED_PORT_REG, BLUE_LED_PIN, PIN_HIGH );

    // PWM
    timer4_init();
}


/**************************************************************************************************
								void red_led_on()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Turn the RED LED ON
* 
***************************************************************************************************/
void red_led_on()
{
    // update the state of RED_LED_PIN as ON
    // the RGB LED is Common Anode type
    update_bit( RGB_LED_PORT_REG, RED_LED_PIN, PIN_LOW );
}


/**************************************************************************************************
								void red_led_off()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Turn the RED LED OFF
* 
***************************************************************************************************/
void red_led_off()
{
    // update the state of RED_LED_PIN as OFF
    // the RGB LED is Common Anode type
    update_bit( RGB_LED_PORT_REG, RED_LED_PIN, PIN_HIGH );
}


/**************************************************************************************************
								void green_led_on()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Turn the GREEN LED ON
* 
***************************************************************************************************/
void green_led_on()
{
    // update the state of GREEN_LED_PIN as ON
    // the RGB LED is Common Anode type
    update_bit( RGB_LED_PORT_REG, GREEN_LED_PIN, PIN_LOW );
}


/**************************************************************************************************
								void green_led_off()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Turn the GREEN LED OFF
* 
***************************************************************************************************/
void green_led_off()
{
    // update the state of GREEN_LED_PIN as OFF
    // the RGB LED is Common Anode type
    update_bit( RGB_LED_PORT_REG, GREEN_LED_PIN, PIN_HIGH );
}


/**************************************************************************************************
								void blue_led_on()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Turn the BLUE LED ON
* 
***************************************************************************************************/
void blue_led_on()
{
    // update the state of BLUE_LED_PIN as ON
    // the RGB LED is Common Anode type
    update_bit( RGB_LED_PORT_REG, BLUE_LED_PIN, PIN_LOW );
}


/**************************************************************************************************
								void blue_led_off()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Turn the BLUE LED OFF
* 
***************************************************************************************************/
void blue_led_off()
{
    // update the state of BLUE_LED_PIN as OFF
    // the RGB LED is Common Anode type
    update_bit( RGB_LED_PORT_REG, BLUE_LED_PIN, PIN_HIGH );
}


/**************************************************************************************************
								void user_sw_init()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Initialize the USER_SW (Push Button) Port Pin and activate its pull-up resistor
* 
***************************************************************************************************/
void user_sw_init()
{
    // update the data directions of USER_SW_PIN as INPUT
    update_bit( USER_SW_DDR_REG, USER_SW_PIN, PIN_INPUT );
    
    // activate the pull-up resistor of USER_SW_PIN
    update_bit( USER_SW_PORT_REG, USER_SW_PIN, PIN_HIGH );
}


/**************************************************************************************************
							unsigned char get_user_sw_status()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Get the USER_SW (Push Button) Pin status whether it is in released state
* 
***************************************************************************************************/
unsigned char get_user_sw_status()
{
    // get the USER_SW (Push Button) status whether it is in released state
    return get_bit_status( USER_SW_PIN_REG, USER_SW_PIN );
}


/**************************************************************************************************
				void adc_input(unsigned char *channels, unsigned char no_channels)
***************************************************************************************************
* 
* Input arguments:  Array of channels, Number of Channels
* Return value:     None
* Description:      Initialize all ADC channel pins as Input
* 
***************************************************************************************************/
void adc_input(unsigned char *channels, unsigned char no_channels)
{
    int i;
    
    // Initialise all channels as Input
    for (i = 0; i < no_channels; i++)
    {
        if (channels[i] > 15);
        // Initialise DDRF Register if channels is less than 9
        else if (channels[i] < 8)
            update_bit(ADC_DDR_REG_LOW, channels[i], PIN_LOW);
        
        // Initialise DDRk Register if channels is greater than 8
        else
            update_bit(ADC_DDR_REG_HIGH, channels[i], PIN_LOW);
    }
}


/**************************************************************************************************
								void adc_init()
***************************************************************************************************
* 
* Input arguments:  None
* Return value:     None
* Description:      Initialize the ADC with left adjustment result readout
* 
***************************************************************************************************/
void adc_init()
{
    // Disable Analog Comparator; else ADC wont work
    update_bit(ACSR, ACD, PIN_HIGH);
    
    // Enable Left Adjustment to read only 8 bit data from 10 bit ADC
    update_bit(ADMUX, ADLAR, PIN_HIGH);
    
    // (turn ADC ON) | (set prescalar to 64 110)
    ADCSRA |= ( get_bit_mask(ADEN) | get_bit_mask(ADPS2) | get_bit_mask(ADPS1) );
}


/**************************************************************************************************
				unsigned char get_adc_channel_data(unsigned char channel_no)
***************************************************************************************************
* 
* Input arguments:  Channel Number
* Return value:     ADC 8 bit Converted data
* Description:      Get the input from the channel and convert to digital form
* 
***************************************************************************************************/
unsigned char get_adc_channel_data(unsigned char channel_no)
{
    // Declare a variable to store the converted data
    unsigned char a;
    
    // Extract Last 3 bits from Ch for ADMUX
	channel_no = channel_no & 0b00000111; //0x07
	// (Left Adjusted Output) | (ADMUX4:0)
	ADMUX = 0x20 | channel_no; 
	
	// If channel number is greater than 7 then SET MUX5
	if(channel_no > 7){
		update_bit(ADCSRB, MUX5, PIN_HIGH); // set MUX5 = 1
	}
	
	//Start Conversion 
	update_bit(ADCSRA, ADSC, PIN_HIGH);
	
	// Wait for ADC conversion to complete; ADIF = 0, conversion going on; ADIF = 1, conversion complete
	while(is_bit_cleared(ADCSRA, ADIF));
	
	// store ADC value in variable.
	a = ADCH;
	
	// ADIF is set when ADC conversion is complete and Data Registers are updated
	// ADIF needs to be cleared before starting next conversion. Clear ADIF (ADC Interrupt Flag) by writing 1
	update_bit(ADCSRA, ADIF, PIN_HIGH); 
	// clear MUX5 so that other ADC channels can use this function
	update_bit(ADCSRB, MUX5, PIN_LOW);
	
	return a;
}

// Function for brightness control of all 3 LEDs
void brightness (unsigned char red_led, unsigned char green_led, unsigned char blue_led) {
	OCR4AL = 255 - (unsigned char)red_led; 	// active low thats why subtracting by 255
	OCR4CL = 255 - (unsigned char)green_led;
	OCR4BL = 255 - (unsigned char)blue_led;
}
