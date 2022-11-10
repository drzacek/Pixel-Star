/*
 * leds.c
 *
 *  Created on: Nov 8, 2022
 *      Author: drzacek
 */

// Includes
#include <string.h>
#include "leds.h"


// Variables
SPI_HandleTypeDef hSPI_LED;
uint8_t LED_SPI_INITALIZED = 0;

uint8_t resetBuffer[RESET_LENGTH] = {0};
uint8_t grbData[LED_BUFFER_SIZE];
uint8_t txBuf[RESET_LENGTH + LED_BUFFER_SIZE + RESET_LENGTH];


void ws2813_init(SPI_HandleTypeDef hspi)
{
	hSPI_LED = hspi;
	LED_SPI_INITALIZED = 1;
}

void ws2813_reset()
{
	if (LED_SPI_INITALIZED)
	{

	}
}


// The WS2813 addressable LEDs define 0 and 1 signals as PWM of different duty cycle
// From the datasheet:
//
// 0:    T0H
//  --------|
//			|    T0L
//			|------------
//
// 1:    T1H
//  ------------|
//				|    T1L
//				|--------
//
// Bit "0" needs to have 300-450ns high, followed by 300ns-100us low
// Bit "1" needs to have 750-1000ns high, followed by 300ns-100us low
// With frame reset 300us long
//
// At 8MHz SPI, one bit is 0.125us = 125ns long, so we can use one byte SPI data as PWM signal and vary the duty cycle with 8 bits
// Lets try 2-bit-high-6-bit-low for "0" and 5-bit-high-3-bit-low for 1 - it's not quite like what the table wants, but apparently
// the tolerances are pretty wide and it tolerates that.

uint8_t ws2813_bit(uint8_t bit)
{
	uint8_t byte = 0x80;
	if (LED_SPI_INITALIZED)
	{
		if (bit)
		{
			byte = 0xf8;
		}
		else
		{
			byte = 0xc0;

		}
	}
	return byte;
}

void ws2813_clearAllLed()
{
	memset(grbData, 0xe0, 24 * LED_NUMBER);
}

void ws2813_setLedRGB(uint8_t grb[3], uint32_t led_position)
{
	// Set buffer for GREEN/RED/BLUE color data for LED at [led_position] position - yes, LEDs start at 0, not at 1
	for (int i = 0; i < 3; i++)
	{
		grbData[0 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x01);
		grbData[1 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x02);
		grbData[2 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x04);
		grbData[3 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x08);
		grbData[4 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x10);
		grbData[5 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x20);
		grbData[6 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x40);
		grbData[7 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x80);
	}
}

void ws2813_sendLEDs()
{
	if (LED_SPI_INITALIZED)
	{
		memcpy(txBuf, resetBuffer, RESET_LENGTH);
		memcpy(txBuf+RESET_LENGTH, grbData, LED_BUFFER_SIZE);
		memcpy(txBuf+RESET_LENGTH+LED_BUFFER_SIZE, resetBuffer, RESET_LENGTH);

		HAL_SPI_Transmit(&hSPI_LED, txBuf, RESET_LENGTH + LED_BUFFER_SIZE + RESET_LENGTH, 200);
	}
}
