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
#define PHOTORESISTOR 0
//#define OFF 0

int main(void)
{
    CyGlobalIntEnable; 
    AMux_FastSelect(PHOTORESISTOR);
    ADC_DelSig_Start();
    UART_Start();
    ISR_ADC_StartEx(Custom_ISR_ADC);
    ISR_UART_StartEx(Custom_ISR_UART);
    PacketReadyFlag = 0;
    ADC_DelSig_StartConvert();
    Clock_PWM_Start();
    //PWM_LED_Start();
    
    

    for(;;)
    {
        if(PacketReadyFlag)//ho letto i due samples
        {
            UART_PutString(DataBuffer_PHOT);
            //UART_PutString(DataBuffer_POT);
            
            PacketReadyFlag = 0;
            
            if(LedON)
            { 
                //PWM_LED_WriteCompare(50);
                PWM_LED_Start();
            }
            else
                PWM_LED_Stop();
                //PWM_LED_WriteCompare(OFF);
        }
        
    }
}

/* [] END OF FILE */
