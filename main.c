// Where is the led connected, which port, which pin? LED is connected to PA5 or PB13
// Port: A --> Info in user guide
// Pin: 5 --> Info in user guide

// Bare-Metal STM32 Essentials:
// System Bus: Connects CPU to memory and peripherals, e.g., AHB, APB
// Peripheral Base Address: Base address for all peripheral registers in memory space
// GPIO Base Address: Base address for a specific GPIO port, e.g. GPIOA, if you need port a
// RCC Base Address: Base address of the clock control registers
// RCC (Reset and Clock Control): Module to enable/disable clocks for peripherals
// Clock Enable Register: Specific register to turn on the clock for, e.g., GPIOA
// MODER Register: Defines whether a pin is input, output, analog, or alternate function



#define PERIPH_BASE (0x40000000UL) // Starting address of peripheral registers (UL = unsigned long), found in data sheet
#define AHB1_BASE (0x40020000UL) // Starting address  of AHB1. Found in data sheet
// 0x40020000 is also the starting address of GPIOA
// PERIPH_BASE - GPIOA_BASE =0x40020000 - 0x40000000 = 0x00020000
// 0x00020000 is the offset
#define AHB1_PERIPH_OFFSET (0x00020000)
#define GPIOA_OFFSET (0x0000) // the number of 0 does not matter because its all 0
#define GPIOA_BASE (GPIOA_OFFSET + AHB1_BASE)

#define RCC_OFFSET (0x3800UL) // The zeros before the first number != 0 are not needed
#define RCC_BASE (AHB1_BASE + RCC_OFFSET)

// All the information of the addresses are given in the data sheet

#define AHB1_ENABLE_REGISTER_OFFSET (0x30UL) // Information given in the reference manual search "RCC AHB1 enable register"
#define RCC_AHB1EN_R (*(volatile unsigned int*)(RCC_BASE + AHB1_ENABLE_REGISTER_OFFSET)) // EN = enable, R = register
#define GPIOAEN (1U<<0) // Set bit 0 from zero to one. (0 or 1 << position of the bit)
// 0000 0000 0000 0000 0000 0000 0000 0000 is how the address of RCC AHB1 enable register is represented (32-bit)
// 										 ^
// GPIOAEN is represented at bit 0       |
// Shifting this bit to 1 enables IO port A clock
#define MODER_R_OFFSET (0x00UL)
#define GPIOA_MODE_R (*(volatile unsigned int*)(MODER_R_OFFSET + GPIOA_BASE))

#define OUTPUT_DATA_R_OFFSET (0x14)
#define GPIOA_OD_R (*(volatile unsigned int*)(OUTPUT_DATA_R_OFFSET + GPIOA_BASE)) // volatile prevents compiler from optimizing away register access

#define PIN5 (1U<<5)
#define LED_PIN PIN5

typedef struct{

}GPIO_TYPEDEF;


int main(){
	// 1.Enable clock access to GPIOA
	RCC_AHB1EN_R |= GPIOAEN; // | = No other bits will be changed apart from bit 0
	// 2. Set PA5 as output pin
	GPIOA_MODE_R |= (1U<<10); // Set bit 10 to 1
	GPIOA_MODE_R &=~ (1U<<11); // Set bit 11 to 0. |= does not work if you want to set a bit to 0
	// (1U << 11) = 0000100000000000 all bits 0 except bit 11
	// ~(1U << 11) = 1111011111111111 all bits 1 except 11
	// With &= only bit 11 is set to 0, all other bits remain as before

	while(1){
		// Set PA5 high
		// GPIOA_OD_R |= LED_PIN;

		// Set different state for the LED in every new loop:
		 GPIOA_OD_R ^= LED_PIN;

		// Simple delay loop to slow down toggling:
		for(int i = 0; i < 1000000; i++);

		// Without the delay, the LED would switch states too fast
		// (due to the high clock frequency of the STM32) and appear
		// as if it does not blink at all.

	}
}















