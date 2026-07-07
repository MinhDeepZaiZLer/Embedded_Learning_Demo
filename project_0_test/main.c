#include <stdint.h>
#include <stdbool.h>

#include "tm4c123gh6pm.h"

#define RED     0x02    // PF1
#define BLUE    0x04    // PF2
#define GREEN   0x08    // PF3

//-------------------------------------------------
// Delay
//-------------------------------------------------
void delay(void)
{
    volatile uint32_t i;

    for(i = 0; i < 500000; i++);
}

//-------------------------------------------------
// Port F Initialization
//-------------------------------------------------
void PortF_Init(void)
{
    // Enable clock for Port F
    SYSCTL_RCGCGPIO_R |= 0x20;

    // Wait until Port F is ready
    while((SYSCTL_PRGPIO_R & 0x20) == 0);

    // PF1 PF2 PF3 Output
    GPIO_PORTF_DIR_R |= (RED | BLUE | GREEN);

    // Enable Digital Function
    GPIO_PORTF_DEN_R |= (RED | BLUE | GREEN);

    // Turn off LEDs
    GPIO_PORTF_DATA_R &= ~(RED | BLUE | GREEN);
}

//-------------------------------------------------
// LED Control
//-------------------------------------------------
void LED_On(uint8_t color)
{
    GPIO_PORTF_DATA_R |= color;
}

void LED_Off(uint8_t color)
{
    GPIO_PORTF_DATA_R &= ~color;
}

void Blink(uint8_t color)
{
    LED_On(color);
    delay();

    LED_Off(color);
    delay();
}

//-------------------------------------------------
// Main
//-------------------------------------------------
int main(void)
{
    PortF_Init();

    while(1)
    {
        Blink(RED);
        Blink(BLUE);
        Blink(GREEN);
    }
}