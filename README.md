# Bare-Metal STM32 – Blinking LED

This is my first bare-metal programming project on an STM32 microcontroller.  
The goal was to learn how to directly access peripheral registers without using HAL or LL libraries.  

## What this project does
- Enables the clock for GPIOA via the RCC AHB1 peripheral clock enable register.
- Configures pin PA5 as an output by writing to the MODER register.
- Toggles the LED connected to PA5 (on the Nucleo board this is the built-in LED).
- Uses simple delay loops for timing.

## What I learned
- How to navigate the STM32 reference manual and datasheet.
- Understanding base addresses, offsets, and how peripheral registers are mapped in memory.
- How to use bitwise operations to configure registers.
- Why volatile is required when working with hardware registers.
- Basics of bare-metal embedded programming (no HAL, no libraries – just direct register access).



