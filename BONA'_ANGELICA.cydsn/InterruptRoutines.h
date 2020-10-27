/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    
    #include "cytypes.h"
    #include "stdio.h"
    
    #define PHOTORESISTOR 0 //AMux Channel for the photoresistor
    #define POTENTIOMETER 1 //AMux Channel for the potentiometer
    
    #define PHOT_MSB 1 //The second element of the vector DataBuffer is the MSB of the photoresistor sample
    #define PHOT_LSB 2 //The third element of the vector DataBuffer is the LSB of the photoresistor sample
    #define POT_MSB 3 //The fourth element of the vector DataBuffer is the MSB of the potentiometer sample
    #define POT_LSB 4 //The fifth element of the vector DataBuffer is the LSB of the potentiometer sample
    #define T_HOLD_MSB 5 //The sixth element of the vector DataBuffer is the MSB of the light threshold
    #define T_HOLD_LSB 6 //The seventh element of the vector DataBuffer is the LSB of the light threshold
    #define TRANSMIT_BUFFER_SIZE 8 //DataBuffer has 8 elements in total
    
    #define THRESHOLD 30000 //threshold in decimal notation
    #define THRESHOLD_MSB 0x75 //MSB of the threshold value
    #define THRESHOLD_LSB 0x30 //LSB of the threshold value
    
    CY_ISR_PROTO(Custom_ISR_UART);
    CY_ISR_PROTO(Custom_ISR_ADC);
    
    uint8 DataBuffer[TRANSMIT_BUFFER_SIZE];
    
    volatile uint8 SendBytesFlag; //variable put to 1 when 'B' or 'b' is received, to 0 when 'S' or 's' is received
    volatile uint8 flag_clock; //variable put to 1 every 100ms (frequency of Timer interrupt)
    
    
#endif
/* [] END OF FILE */
