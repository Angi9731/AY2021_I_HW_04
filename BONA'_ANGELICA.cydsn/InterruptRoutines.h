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
    
    #define PHOTORESISTOR 0
    #define POTENTIOMETER 1
    #define BYTES_TO_SEND 4
    #define BRIGHT_MSB 1
    #define BRIGHT_LSB 2
    #define POT_MSB 3
    #define POT_LSB 4
    #define THRESHOLD 3000
    #define THRESHOLD_MSB 0x75
    #define THRESHOLD_LSB 0x30
    #define T_HOLD_MSB 5
    #define T_HOLD_LSB 6
    #define TRANSMIT_BUFFER_SIZE 8
    
    CY_ISR_PROTO(Custom_ISR_UART);
    CY_ISR_PROTO(Custom_ISR_ADC);
    
    uint8 DataBuffer[TRANSMIT_BUFFER_SIZE];
    volatile uint8 SendBytesFlag;
    
    volatile uint8 flag_clock;
    volatile uint8 PacketReadyFlag;
    
#endif
/* [] END OF FILE */
