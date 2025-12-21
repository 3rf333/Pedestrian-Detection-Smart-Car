#include "stm32l476xx.h"

volatile uint32_t ms_ticks = 0;  // 1ms tick counter
uint32_t SystemCoreClock = 4000000;

// SysTick interrupt handler
void SysTick_Handler(void) {
    ms_ticks++;
}

void delay_ms(uint32_t delay) {
    uint32_t start = ms_ticks;
    while ((ms_ticks - start) < delay);
}

int main(void) {

    // Enable GPIOC and GPIOB clocks
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN;

    // MOTOR (PC2, PC3)
    GPIOC->MODER &= ~((3U << (2 * 2)) | (3U << (3 * 2)));
    GPIOC->MODER |=  ((1U << (2 * 2)) | (1U << (3 * 2)));

    // USER BUTTON (PC13)
    GPIOC->MODER &= ~(3U << (13 * 2));
    GPIOC->PUPDR &= ~(3U << (13 * 2));
    GPIOC->PUPDR |=  (1U << (13 * 2));   // pull-up

    // PIR SENSOR (PC10)
    GPIOC->MODER &= ~(3U << (10 * 2));
    GPIOC->PUPDR &= ~(3U << (10 * 2));

    // LED (PB4)
    GPIOB->MODER &= ~(3U << (4 * 2));
    GPIOB->MODER |=  (1U << (4 * 2));

    // Configure SysTick
    // SystemCoreClock is usually 80 MHz → / 80000 = 1ms tick
    SysTick->LOAD = (SystemCoreClock / 1000) - 1;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk   |
                    SysTick_CTRL_ENABLE_Msk;

    int motor_state = 0;
    int last_button = 1;

    while (1) {

        // Button handling for motor toggle
        int button = (GPIOC->IDR & (1U << 13)) ? 1 : 0;

        if (button == 0 && last_button == 1) {
            delay_ms(50);  // SysTick-based debounce
            if ((GPIOC->IDR & (1U << 13)) == 0) {
                motor_state ^= 1;
            }
        }
        last_button = button;

        // PIR sensor + LED
        int pir = (GPIOC->IDR & (1U << 10)) ? 1 : 0;

        if (pir == 1) {
            GPIOB->ODR |=  (1U << 4);   // LED ON
        } else {
            GPIOB->ODR &= ~(1U << 4);   // LED OFF
        }

        // Motor control with PIR override
        if (pir == 1) {
            GPIOC->ODR &= ~(1U << 2);
            GPIOC->ODR &= ~(1U << 3);
        } else {
            if (motor_state) {
                GPIOC->ODR &= ~(1U << 2);
                GPIOC->ODR |=  (1U << 3);
            } else {
                GPIOC->ODR &= ~(1U << 2);
                GPIOC->ODR &= ~(1U << 3);
            }
        }
    }
}
