/*
* easygpio.h
*
* Copyright (c) 2015, eadf (https://github.com/eadf)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* * Neither the name of Redis nor the names of its contributors may be used
* to endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef EASYGPIO_INCLUDE_EASYGPIO_EASYGPIO_H_
#define EASYGPIO_INCLUDE_EASYGPIO_EASYGPIO_H_

#include "c_types.h"

typedef enum {
  EASYGPIO_INPUT=0,
  EASYGPIO_OUTPUT=1
} EasyGPIO_PinMode;

typedef enum {
  EASYGPIO_PULLDOWN=2,
  EASYGPIO_PULLUP=3,
  EASYGPIO_NOPULL=4
} EasyGPIO_PullStatus;

/**
 * Returns the gpio name and func for a specific pin.
 */
bool easygpio_getGPIONameFunc(uint8_t gpio_pin, uint32_t *gpio_name, uint8_t *gpio_func);

/**
 * Sets the 'gpio_pin' pin as a GPIO and sets the interrupt to trigger on that pin.
 * The 'interruptArg' is the function argument that will be sent to your interruptHandler
 * (this way you can several interrupts with one interruptHandler)
 */
bool easygpio_attachInterrupt(uint8_t gpio_pin, EasyGPIO_PullStatus pullStatus, void (*interruptHandler)(void *arg), void *interruptArg);

/**
 * Deatach the interrupt handler from the 'gpio_pin' pin.
 */
bool easygpio_detachInterrupt(uint8_t gpio_pin);

/**
 * Returns the number of active pins in the gpioMask.
 */
uint8_t easygpio_countBits(uint32_t gpioMask);

/**
 * Sets the 'gpio_pin' pin as an input GPIO and sets the pull up and
 * pull down registers for that pin.
 * 'pullStatus' has no effect on output pins or GPIO16
 */
bool easygpio_pinMode(uint8_t gpio_pin, EasyGPIO_PullStatus pullStatus, EasyGPIO_PinMode pinMode);

/**
 * Sets the pull up and pull down registers for a pin.
 * This seems to do very little for the actual pull effect
 * - it's always pull-up for both EASYGPIO_PULLUP and EASYGPIO_PULLDOWN.
 * But that is something the SDK needs to fix.
 */
bool easygpio_pullMode(uint8_t gpio_pin, EasyGPIO_PullStatus pullStatus);

/**
 * Uniform way of getting GPIO input value. Handles GPIO 0-16
 * If you know that you won't be using GPIO16 then you'd better off by just using GPIO_INPUT_GET().
 * You can not rely on that this function will switch the gpio to an input like GPIO_INPUT_GET does.
 * So if you have an output gpio you need to switch to input status with GPIO_INPUT_GET or GPIO_DIS_OUTPUT.
 */
uint8_t easygpio_inputGet(uint8_t gpio_pin);

/**
 * Uniform way of setting GPIO output value. Handles GPIO 0-16
 * If you know that you won't be using GPIO16 then you'd better off by just using GPIO_OUTPUT_SET().
 * You can not rely on that this function will switch the gpio to an output like GPIO_OUTPUT_SET does.
 * So if you have an input gpio you need to toggle to output status with GPIO_OUTPUT_SET.
 */
void easygpio_outputSet(uint8_t gpio_pin, uint8_t value);

#endif /* EASYGPIO_INCLUDE_EASYGPIO_EASYGPIO_H_ */
