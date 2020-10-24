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
    AMux_FastSelect(0);
    ADC_DelSig_Start();
    UART_Start();
    ISR_ADC_StartEx(Custom_ISR_ADC);
    ISR_UART_StartEx(Custom_ISR_UART);
    PacketReadyFlag = 0;
    ADC_DelSig_StartConvert();
    Clock_PWM_Start();
    
    

    for(;;)
    {
        if(PacketReadyFlag)
        {
            UART_PutString(DataBuffer);
            PacketReadyFlag = 0;
            if(LedON)
                PWM_LED_Start();
            else
                PWM_LED_Stop();
        }
        
    }
}

/* [] END OF FILE */
