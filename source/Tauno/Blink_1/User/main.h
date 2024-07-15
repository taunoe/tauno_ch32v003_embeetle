/**
 * @file    main.h
 * @author  Florian Schütz (fschuetz@ieee.org)
 * @brief   LED blinking demo for WCH CH32V003 mcu
 * @version 1.0
 * @date    03.11.2023
 * 
 * @copyright Copyright (c) 2023 Florian Schütz, released under MIT license
 * 
 * This is a short demo how to blink a LED attached to GPIO 1 of port C (PC1)
 * of a WCH CH32V003. The demo is designed to work with the CH32V003F4P6-EVT-RO
 * evaluation board. It will work with any other CH32V003 based setup as long
 * as you have an external clock cristal attached to GPIO 1 and 2 of port A
 * (PA1 / PA2). If you intend to use the internal clock only, then create a
 * custom startup file and set in in platformio.ini as described in 
 * https://pio-ch32v.readthedocs.io/en/latest/none%20os%20sdk.html
 */

#include <ch32v00x.h>
#include <debug.h>

// Definitions to allow easy adjustment
#define BLINKY_GPIO_PORT            GPIOC
#define BLINKY_GPIO_PIN             GPIO_Pin_0
#define BLINKY_ON                   0
#define BLINKY_OFF                  1
#define BLINK_LENGTH_MS             100

// Error codes
#define OK                          0
#define ERR_OUT_OF_RANGE            1


/**
 * @brief Blinks an led to morse the message
 * 
 * This method translates a given message into morse code and blinks a led to
 * display the message.
 * 
 * @param msg       The message to be signaled as morse code
 * @param port      The port for the GPIO that has the led attached
 * @param pin       The pin number of the GPIO that has the led attached
 * @param unit_ms   The duration of a unit in milliseconds
 * 
 * Function that uses the property of the morse alphabeth that it can be 
 * represented as a binary tree. Going left in the tree means we need to
 * write a do, going to the right a dash.
 * 
 *                     *
 *               /           \
 *             E               T
 *           /   \           /   \
 *         I       A       N       M
 *        / \     / \     / \     / \ 
 *       S   U   R   W   D   K   G   O
 *      / \ / \ / \ / \ / \ / \ / \ / \ 
 *      H V F * L * P J B X C Y Z Q * *
 * 
 * If we parse this tree in preorder and list the characters in a sequence
 * (**ETIANMSURWDKGOHVF*L*PJBXCYZQ**), the index for each of these characters 
 * has the property that in its binary representation if we start at the most
 * significant bit that is 1, the following bits are encoding the dashes (1)
 * and dots (0) for the character. https://www.pocketmagic.net/morse-encoder/
 * 
 * Convention from morse code are:
 *  - The length of a dot is one unit
 *  - The length of a dash is three units
 *  - The space between parts of the letter is one unit
 *  - The space between letters is three units
 *  - The space between words is seven units 
 */
int morse(const char *msg, GPIO_TypeDef* port, uint32_t pin, uint32_t unit_ms);
