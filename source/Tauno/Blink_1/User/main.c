/**
 * @file    main.c
 * @author  Florian Schütz (fschuetz@ieee.org)
 * @brief   LED blinking demo for WCH CH32V003 mcu
 * @version 1.0
 * @date    03.11.2023
 *
 * https://ch405-labs.com/ch32v003_intro/
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
#include "main.h"

/**
 * @brief The main function
 * 
 * Initialises the hardware, delays the init and then blinks the LED morsing
 * the message "Hello World".
 * 
 * Warning: Do not remove the init delay or you may no longer be able to flash
 *              the chip.
 * 
 * @return int Never returns
 */
int main(void) {

    // Configure priority grouping
    //
    // 2 bits for pre-emption priority and 2 bits for subpriority.
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // Update system core clock update
    SystemCoreClockUpdate();

    // Initialise the delay function
    Delay_Init();
    
    // Initialise UART printf
    USART_Printf_Init(115200);

    // Enable the high speed peripheral clock
    //
    // For APB2 peripheral GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Initialise GPIO
    //
    // To initialise the GPIO pin and port defined for outputting the blink 
    // signal we need to populate a structure of type GPIO_InitTypeDef by
    // setting the pin, mode (output) and the speed (50MHz). We then call
    // GPIO_Init with the port defined in the header and the init structure
    // as arguments.
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = BLINKY_GPIO_PIN;
    // There are two different output modes:
    // - Open drain output ( GPIO_Mode_Out_OD ) and
    // - push pull output (GPIO_Mode_Out_PP).
    // There are four different input modes:
    // - Floating input (GPIO_Mode_IN_FLOATING),
    // - pull-up input (GPIO_Mode_IPU),
    // - pull-down input (GPIO_Mode_IPD) and
    // - analog input (GPIO_Mode_AIN).
    // The GPIO can also be configured as "alternate function".
    // used for a specific hardware function like for example
    // pulse width mudulation (PWM) or serial peripheral interface (SPI).
    // The modes for alternate functions can be
    // - open drain (GPIO_Mode_AF_OD) or
    // - push-pull (GPIO_Mode_AF_PP). 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // 2Mhz, 10MHz or 50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BLINKY_GPIO_PORT, &GPIO_InitStructure);

    // Set the message to blink as morse code
    const char *msg = "Hello World";

    // Morse the message indefinitely
    while(1) {
        printf("Hello World!\n");
      
        if(morse(msg, BLINKY_GPIO_PORT, BLINKY_GPIO_PIN, BLINK_LENGTH_MS) 
            != OK) {
            printf("An error occurred: Invalid message.\n");
        }
        Delay_Ms(1000);  // 1 second
    }
}

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
int morse(const char *msg, GPIO_TypeDef* port, uint32_t pin, 
    uint32_t unit_ms) {

    // The encoded alphabeth of the binary tree
    const char *alphabeth = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";

    // Pointer to character that is currently processed.
    const char *current_char = msg;

    // Indicator if previously processed character was a whitespace.
    uint8_t prev_was_whitespace = 0;

    // The loop encoding and blinking the message
    while(*current_char != '\0') {

        char c = *current_char;

        // Check if the current character is a space. If yes, we need to pause
        // for an additional four units (we already paused three due to pause)
        // beween characters.
        if(c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            // Only delay for one whitespace, ignore if previous character was
            // whitespace as well
            if(prev_was_whitespace == 0) {
                Delay_Ms(4 * unit_ms);
                prev_was_whitespace = 1;
            }

            // Process next character.
            current_char++;
            continue;
        }

        // If we reach here, the character is not a whitespace and we can reset
        // the whitespace indicator
        prev_was_whitespace = 0;

        // Convert character to uppercase if needed
        if(c >= 'a' && c <= 'z') {
            c -= 32;
        }

        // Check if our (potentially converted) character is valid. If it is 
        // not we abort with an error.
        if(c < 'A' || c > 'Z') {
            return ERR_OUT_OF_RANGE;
        }

        // Find the index of the position of the character in our encoded 
        // alphabeth and convert index in long and short led pulses
        uint8_t index = 0;
        while(alphabeth[++index] != c);

        uint8_t mask = 0b10000000;
        uint8_t i = 0;

        // Search the leftmost bit that is 1 (and ignore it)
        //
        // Note: We omit testing i for <8 as we know the index must contain
        // at least one 1 indicating the encoding start.
        while((((index << i) & mask)) == 0) {
            i++;
        }

        // Now convert 0 to dots and 1 to dashes
        //
        // Note: We do not check i > 0 && i < 8 initially as we know we
        // have at least one digit after the indicator above.
        while(++i < 8) {
            if((index << i) & mask) {
                // dash
                GPIO_WriteBit(port, pin, BLINKY_ON);
                Delay_Ms(3 * unit_ms);
                GPIO_WriteBit(port, pin, BLINKY_OFF);            
            } else {
                // dot
                GPIO_WriteBit(port, pin, BLINKY_ON);
                Delay_Ms(unit_ms);
                GPIO_WriteBit(port, pin, BLINKY_OFF);
            }

            // Pause one unit before next symbol
            Delay_Ms(unit_ms);
        }
        

        // Pause before next letter. We already waited one unit from the
        // blinking of the letter, so we need to wait for two more to 
        // have the pause between letters correct.
        Delay_Ms(2 * unit_ms);

        current_char++;
    }

    return OK;
}
