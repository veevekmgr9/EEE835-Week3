#include "systick_config.h"

// Global millisecond counter
static volatile uint32_t sysTick_ms = 0;

// Initialise SysTick for 1ms interrupts
void SysTick_Init(void) {
    // Configure SysTick to interrupt every 1ms
    SysTick->LOAD = (16000000 / 1000) - 1; // 16 MHz / 1000 = 16000 - 1
    SysTick->VAL  = 0;                     // Clear current value
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk   |
                    SysTick_CTRL_ENABLE_Msk;   // Enable SysTick, CPU clock, and interrupt
}

// SysTick Handler (increments ms counter)
void SysTick_Handler(void) {
    sysTick_ms++;
}

// Return system tick in ms
inline uint32_t GetTick(void) {
    return sysTick_ms;
}
