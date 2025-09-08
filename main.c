// On Nucleo boards the LED is connected to PA5 (sometimes PB13)
// Port A --> check in user manual
// Pin 5  --> check in user manual

// Bare-Metal STM32 essentials:
// System Bus: Connects CPU to memory and peripherals (AHB, APB)
// Peripheral Base Address: Start of all peripheral registers
// GPIO Base Address: Base address for a GPIO port (e.g. GPIOA)
// RCC Base Address: Base of Reset and Clock Control registers
// RCC: Module to enable/disable peripheral clocks
// MODER Register: Configures pin mode (input, output, analog, AF)


#define PERIPH_BASE (0x40000000UL) // Base of peripheral registers
#define AHB1_BASE (0x40020000UL)   // Base of AHB1 peripherals (GPIOA, RCC, etc.)

#define AHB1_PERIPH_OFFSET (0x00020000)
#define GPIOA_OFFSET (0x0000)
#define GPIOA_BASE (AHB1_BASE + GPIOA_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1_BASE + RCC_OFFSET)

// RCC AHB1 enable register (see reference manual)
#define AHB1_ENABLE_REGISTER_OFFSET (0x30UL)
#define RCC_AHB1EN_R (*(volatile unsigned int*)(RCC_BASE + AHB1_ENABLE_REGISTER_OFFSET))

#define GPIOAEN (1U<<0) // Bit 0 enables GPIOA clock

#define MODER_R_OFFSET (0x00UL)
#define GPIOA_MODE_R (*(volatile unsigned int*)(GPIOA_BASE + MODER_R_OFFSET))

#define OUTPUT_DATA_R_OFFSET (0x14UL)
#define GPIOA_OD_R (*(volatile unsigned int*)(GPIOA_BASE + OUTPUT_DATA_R_OFFSET)) // volatile: do not optimize away

#define PIN5 (1U<<5)
#define LED_PIN PIN5


int main(void){
    // 1. Enable GPIOA clock
    RCC_AHB1EN_R |= GPIOAEN;

    // 2. Set PA5 as output (MODER5 = 01)
    GPIOA_MODE_R |=  (1U<<10); // set bit 10
    GPIOA_MODE_R &= ~(1U<<11); // clear bit 11

    while(1){
        // Toggle LED on PA5
        GPIOA_OD_R ^= LED_PIN;

        // Simple delay loop
        for(int i = 0; i < 1000000; i++);
    }
}
