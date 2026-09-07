# MCU Pong Game
Pong game implemented on embedded STM32 based system. The system uses
STM32F446RE as core MCU, two LED matrices with MAX7219 drivers for 
display, MAX98357 class D amplifier as DAC for audio transmission with I2S communication
and buttons handled by external interrupt GPIO pins.

# Features
- Driver for MAX7219 LED display communicating through SPI interface
- Audio player implementation
- Pong game implementation
- 256x512 game mapped to 16x8 LED matrix

# Connections schema

# Demo gameplay
It's harder than it looks!

[![Demo video](/assets/demo_img.jpg)](https://www.youtube.com/watch?v=q84ohqniKxY)
