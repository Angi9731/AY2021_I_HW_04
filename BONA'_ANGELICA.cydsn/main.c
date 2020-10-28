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
#include "Driver.h"

int main(void)
{
    CyGlobalIntEnable;
    UART_Start();
    ISR_ADC_StartEx(Custom_ISR_ADC);
    ISR_UART_StartEx(Custom_ISR_UART);
    
    FixedBytes();
    
    SumLevel = 0;
    SumIntensity = 0;
    
    SendBytesFlag = 0;
    flag_clock = 0;

    for(;;)
    {
       if((SendBytesFlag)&&(flag_clock == 10)) //Every 100ms, if 'B' or 'b' have been received and 'S' or 's' haven't been received yet
        {
            VariableBytes();
            UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE); //transmits the 8 bytes
            SumLevel = 0;
            SumIntensity = 0;
            flag_clock = 0;
        }
      
    }
}

/* [] END OF FILE */
