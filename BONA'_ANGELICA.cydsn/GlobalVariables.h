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
#include "project.h"

    #define PHOTORESISTOR 0 //AMux Channel for the photoresistor
    #define POTENTIOMETER 1 //AMux Channel for the potentiometer
    
    #define PHOT_MSB 1 //The second element of the vector DataBuffer is the MSB of the photoresistor samples mean
    #define PHOT_LSB 2 //The third element of the vector DataBuffer is the LSB of the photoresistor samples mean
    #define POT_MSB 3 //The fourth element of the vector DataBuffer is the MSB of the potentiometer samples mean
    #define POT_LSB 4 //The fifth element of the vector DataBuffer is the LSB of the potentiometer samples mean
    #define T_HOLD_MSB 5 //The sixth element of the vector DataBuffer is the MSB of the light threshold
    #define T_HOLD_LSB 6 //The seventh element of the vector DataBuffer is the LSB of the light threshold
    #define TRANSMIT_BUFFER_SIZE 8 //DataBuffer has 8 elements in total
    
    #define THRESHOLD 30000 //threshold in decimal notation
    #define THRESHOLD_MSB 0x75 //MSB of the threshold value
    #define THRESHOLD_LSB 0x30 //LSB of the threshold value
    
    uint8 DataBuffer[TRANSMIT_BUFFER_SIZE];
    
    int32 SumLevel; //variable that collects the sum of samples of photoresistor
    int32 SumIntensity; //variable that collects the sum of samples of potentiometer
    
    volatile uint8 SendBytesFlag; //variable put to 1 when 'B' or 'b' is received, to 0 when 'S' or 's' is received
    volatile uint8 flag_clock; //variable incremented every 10ms (frequency of Timer interrupt)
    
/* [] END OF FILE */
