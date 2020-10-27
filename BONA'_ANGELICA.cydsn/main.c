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
#include "stdio.h"
#include "InterruptRoutines.h"

int main(void)
{
    CyGlobalIntEnable;
    ADC_DelSig_Start();
    UART_Start(); 
    Timer_Start();
    Clock_Timer_ADC_Start();
    ISR_ADC_StartEx(Custom_ISR_ADC);
    ISR_UART_StartEx(Custom_ISR_UART);
    Clock_PWM_Start();
    PWM_LED_Start();
    
    DataBuffer[0] = 0xA0; //The first element of the vector DataBuffer is this start byte
    DataBuffer[T_HOLD_MSB] = THRESHOLD_MSB; //putting threshold bytes in DataBuffer
    DataBuffer[T_HOLD_LSB] = THRESHOLD_LSB;
    DataBuffer[TRANSMIT_BUFFER_SIZE - 1] = 0xC0; //The last element of the vector DataBuffer is this stop byte
    
    SendBytesFlag = 0;
    flag_clock = 0;

    for(;;)
    {
       if((SendBytesFlag)&&(flag_clock)) //Every 100ms, if 'B' or 'b' have been received and 'S' or 's' haven't been received yet
        {
            UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE); //transmits the 8 bytes
            flag_clock = 0;
        }
      
    }
}

/* [] END OF FILE */
