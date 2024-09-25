// example based on libopencm3 miniblink/systick_blink/button examples

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

#include "lfsr.h"

// LED is PB0/PB1/PA8/PA11/PA9, and we pick PB0
#define PORT_LED GPIOB
#define PIN_LED GPIO0 // noise pin is PC14/PB7/PB8/PB9, and we pick PB7
#define PORT_NOISE GPIOB
#define PIN_NOISE GPIO7
#define TIM_NOISE TIM3

volatile uint32_t counter = 0;

void tim34_isr(void) {
    if (timer_interrupt_source(TIM_NOISE, TIM_SR_UIF)) {
        static uint32_t lfsr = 0xFFFFFFFF;
        uint32_t output;
        lfsr_step(&lfsr, &output);
        if (output) {
            gpio_set(PORT_NOISE, PIN_NOISE);
        } else {
            gpio_clear(PORT_NOISE, PIN_NOISE);
        }

        timer_clear_flag(TIM_NOISE, TIM_SR_UIF);
    }
}

void sys_tick_handler(void) {
    ++counter;
}

uint32_t millis(void);
uint32_t millis(void) {
    return counter;
}

static void setup(void) {
    rcc_clock_setup(&rcc_clock_config[RCC_CLOCK_CONFIG_HSI_PLL_64MHZ]);

    STK_CVR = 0; // clear systick current value to start immediately

    // every 1 ms (1000 Hz)
    systick_set_frequency(1000, rcc_ahb_frequency);
    systick_counter_enable();
    systick_interrupt_enable();

    // setup LED pins
    rcc_periph_clock_enable(RCC_GPIOB);
    // set LED pins to output push-pull
    gpio_mode_setup(PORT_LED, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED);

    // setup noise pin
    gpio_mode_setup(PORT_NOISE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_NOISE);

    // setup timer
    rcc_periph_clock_enable(RCC_TIM3);
    // rcc_ahb_frequency = 64MHz
    // desired noise frequency = ~300kHz
    // period of 213 - 1 gives 300.5kHz
    timer_set_prescaler(TIM_NOISE, 0);
    timer_set_period(TIM_NOISE, 212);
    timer_enable_irq(TIM_NOISE, TIM_DIER_UIE);
    nvic_enable_irq(NVIC_TIM34_IRQ);
    timer_enable_counter(TIM_NOISE);
}


int main(void) {
    uint32_t last_flash_millis;
    const uint32_t BLINK_DELAY = 500;

    setup();
    last_flash_millis = millis();

    while(1) {
        if ((millis() - last_flash_millis) > BLINK_DELAY) {
            gpio_toggle(PORT_LED, PIN_LED);
            last_flash_millis = millis();
        }
    }

    while (1);
    return 0;
}

