/*
 * leds.h
 *
 *  Created on: Nov 7, 2022
 *      Author: Jacek.Mainczyk
 */

#ifndef INC_LEDS_H_
#define INC_LEDS_H_

// This file contains declarations of functions and variables
// used for driving LEDs on Pixel-Star PCB.
// Basic low-level driving of the WS2813 protocol, and the complex animations

// Variables
extern HAL_SPI_StateTypeDef hSPI_LED;

void ws2813_init(SPI_HandleTypeDef hspi);	// init SPI handle and variables for ws2813 LEDs

void ws2813_reset();	// send RESET signal

void ws2813_bit0();
void ws2813_bit1();

void ws2813_sendByte(uint8_t byte);
void ws2813_sendRGB(uint8_t rgb[3]);

void led_on(uint8_t ledNumber);
void led_off(uint8_t ledNumber);

void led_effect_0();
void led_effect_1();
void led_effect_2();
void led_effect_3();
void led_effect_4();

#endif /* INC_LEDS_H_ */
