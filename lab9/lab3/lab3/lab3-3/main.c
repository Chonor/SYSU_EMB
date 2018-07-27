// Program written by: ***Your Names**update this***
// Date Created: 1/22/2016 
// Last Modified: 1/22/2016 
// Section ***Tuesday 1-2***update this***
// Instructor: ***Ramesh Yerraballi**update this***
// Lab number: 1 (due as HW3)
// Brief description of the program
// The overall objective of this system is a digital lock
// Hardware connections
//  PE0 is switch input  (1 means switch is not pressed, 0 means switch is pressed)
//  PE1 is switch input  (1 means switch is not pressed, 0 means switch is pressed)
//  PE2 is switch input  (1 means switch is not pressed, 0 means switch is pressed)
//  PE4 is LED output (0 means door is locked, 1 means door is unlocked) 
// The specific operation of this system is to 
//   unlock if all three switches are pressed

#include <stdint.h>
#include "tm4c123gh6pm.h"
unsigned long arm,sensor;
void EnableInterrupts(void);
int main(void){ unsigned long volatile delay;
//TExaS_Init();// activate multimeter, 80 MHz
	SYSCTL_RCGC2_R |= 0x10; // Port E clock
	delay = SYSCTL_RCGC2_R;// wait 3-5 bus cycles
	GPIO_PORTE_DIR_R |= 0x10;// PE4 output
	GPIO_PORTE_DIR_R &= ~0x07;// PE2,1,0 input 
	GPIO_PORTE_AFSEL_R &= ~0x17; // not alternative
	GPIO_PORTE_AMSEL_R &= ~0x17;// no analog
	GPIO_PORTE_PCTL_R &= ~0x000F0FFF; // bits for PE4,PE2,PE1,PE0
	GPIO_PORTE_DEN_R |= 0x17;// enable PE4,PE2,PE1,PE0
	while(1){
		arm = GPIO_PORTE_DATA_R&0x04; // arm 0 if deactivated, 1 if activated(PE2)
		sensor = GPIO_PORTE_DATA_R&0x03; // 1 means ok, 0 means break in
		if((arm==0x04)&&(sensor != 0x03)){
			GPIO_PORTE_DATA_R ^= 0x10; // toggle output for alarm
			delay=1000;  // 100ms delay makes a 5Hz period
		}else{
			GPIO_PORTE_DATA_R &= ~0x10; // LED off if deactivated
    }
  }
}
