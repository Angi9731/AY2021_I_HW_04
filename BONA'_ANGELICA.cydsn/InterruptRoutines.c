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
#include "InterruptRoutines.h"
#include "project.h"

#define ON 1
#define OFF 0

int32 value_digit;
int32 value_mV;
uint8 char_received;
uint8 SendBytesFlag = 0;

CY_ISR(Custom_ISR_ADC)
{
    Timer_ReadStatusRegister();
    if(SendBytesFlag)
    {
        value_digit = ADC_DelSig_Read32();
        if(value_digit < 0)
            value_digit = 0;
        if(value_digit > 65535)
            value_digit = 65535;
        value_mV = ADC_DelSig_CountsTo_mVolts(value_digit);
        if(value_mV < 1000)
        {
            LedON = 1;
        }
        else
            LedON = 0;
            
        sprintf(DataBuffer, "Sample: %ld mV\r\n", value_mV);
        PacketReadyFlag = 1;
    }
}

CY_ISR(Custom_ISR_UART)
{
    char_received = UART_GetChar();
    switch(char_received)
    {
        case 'B':
        case 'b':
            SendBytesFlag = 1;
            Pin_EMBEDDED_LED_Write(ON);
            Timer_Start();
            break;
        case 'S':
        case 's':
            SendBytesFlag = 0;
            Pin_EMBEDDED_LED_Write(OFF);
            Timer_Stop();
            break;  
        default:
            break;
    }
}
        
       
        


/* [] END OF FILE */
