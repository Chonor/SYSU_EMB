#include <stdint.h>
#include "tm4c123gh6pm.h"

#define PF3_1   (*((volatile uint32_t *)0x40025038))

// Make PF2 an output, enable digital I/O, ensure alt. functions off
void SSR_Init(void){ 
  SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20)==0){}; // allow time for clock to start
                                    // 2) no need to unlock PF3-1
  GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // 3) regular GPIO
  GPIO_PORTF_AMSEL_R &= ~0x0E;      // 4) disable analog function on PF3-1
  GPIO_PORTF_DIR_R |= 0x0E;         // 5) set direction to output
  GPIO_PORTF_AFSEL_R &= ~0x0E;      // 6) regular port function
  GPIO_PORTF_DEN_R |= 0x0E;         // 7) enable digital port
}

// Make PF3-1 high
void SSR_On(void){
  PF3_1 = 0x0E;
//  GPIO_PORTF_DATA_R |= 0x0E;
}
// Make PF2 low
void SSR_Off(void){
  PF3_1 = 0x00;
//  GPIO_PORTF_DATA_R &= ~0x0E;
}


int main(void){
  SSR_Init();               // initialize PF2 and make it output
	GPIO_PORTF_LOCK_R = 0x4C4F434B;   //unlock GPIO Port F
	GPIO_PORTF_CR_R |= 0x01;           	// allow changes to PF0
  GPIO_PORTF_DIR_R &= ~0x01;// make PF4 in (PF4 built-in button #1)
  GPIO_PORTF_AFSEL_R &= ~0x01;// disable alt funct on PF4
  GPIO_PORTF_PUR_R |= 0x01; // enable pull-up on PF4
  GPIO_PORTF_DEN_R |= 0x01; // enable digital I/O on PF4
                            // configure PF4 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFFFF0)+0x00000000;
  while(1){
		SSR_On();
    while(GPIO_PORTF_DATA_R&0x01);        // wait for button press
    while((GPIO_PORTF_DATA_R&0x01) == 0); // wait for button release
		SSR_Off();
    while(GPIO_PORTF_DATA_R&0x01);        // wait for button press
    while((GPIO_PORTF_DATA_R&0x01) == 0); // wait for button release
  }
}
