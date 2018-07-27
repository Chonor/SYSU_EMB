/******************************************************
Chip type : ARM TM4C123GH6PM
Program type : Firmware
Core Clock frequency: 80.000000 MHz
*******************************************************/
// definitions & Included Files
#include "tm4c123gh6pm.h"
#define LED_RED 0x02
#define LED_BLUE 0x04
#define LED_GREEN 0x08
unsigned long In; // input from PF4
unsigned long Out; // output to PF2 (blue LED)
int main(void) {
	unsigned long volatile delay;
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF; // enable PORT F GPIO
	while((SYSCTL_PRGPIO_R&0x20)==0){}; // allow time for clock to start
	GPIO_PORTF_LOCK_R = 0x4C4F434B;   // unlock GPIO Port F
	GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
	GPIO_PORTF_DIR_R = 0x0E; // PF4,PF0 in, PF3-1 out
	GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
	GPIO_PORTF_DEN_R = 0x1F; // enable digital PORT F
	GPIO_PORTF_DATA_R = 0; // clear all PORT F
	GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | LED_RED | LED_BLUE | LED_GREEN; // set LED PORT F pins high // 

	while(1){
    In = GPIO_PORTF_DATA_R&0x10;  // read PF0 into Sw1
		Out = In>>2;								// shift into position PF1 red
    //Out = In<<2;                // shift into position PF2 blue
		//Out = In<<3;                  // shift into position PF3 green
		GPIO_PORTF_DATA_R = Out;      // output 
	}
}
