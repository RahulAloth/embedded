#include "stm32f4xx.h"  // Include the appropriate header file for your microcontroller
/***************** Operation Mode Examples ************************************/

void SysTick_Handler(void) {
    // ISR code running in Handler Mode
    // Handle SysTick interrupt
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) { // Check if update interrupt flag is set
        TIM2->SR &= ~TIM_SR_UIF; // Clear the update interrupt flag
        // Handle the timer interrupt
    }
}

/*
SysTick_Config(SystemCoreClock / 1000): Configures the SysTick timer to generate an interrupt
every 1 millisecond.
SysTick_Handler: This function is the Interrupt Service Routine (ISR) for the SysTick interrupt,
which runs in Handler Mode.
main: The main function runs in Thread Mode, performing regular application tasks.
*/
int main(void) {
    // Configure SysTick timer to generate an interrupt every 1ms
    SysTick_Config(SystemCoreClock / 1000);
    /*
    Configuring a Timer Interrupt
    Here’s a complete example of configuring a timer interrupt using TIM2:
    This example configures TIM2 to generate an interrupt every 1 second 
    (assuming a 16 MHz clock). When the interrupt occurs,
    the processor switches to Handler Mode to execute the TIM2_IRQHandler function.
    */

    // Enable clock for TIM2 Enable clock for TIM2: RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configure TIM2.Configure TIM2: Set prescaler and auto-reload values, enable update interrupt.
    TIM2->PSC = 16000 - 1; // Prescaler value
    TIM2->ARR = 1000 - 1;  // Auto-reload value
    TIM2->DIER |= TIM_DIER_UIE; // Enable update interrupt
    TIM2->CR1 |= TIM_CR1_CEN;   // Enable TIM2

    // Enable TIM2 interrupt in NVIC Define ISR: TIM2_IRQHandler handles the timer interrupt.
    NVIC_EnableIRQ(TIM2_IRQn);

    // Application code running in Thread Mode
    while (1) {
        // Perform some tasks
    }
}
