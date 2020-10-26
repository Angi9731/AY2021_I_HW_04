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
#include "stdio.h"

#define ON 1
#define OFF 0

int32 level;
int32 intensity;
uint8 char_received;


CY_ISR(Custom_ISR_ADC) //ogni 100ms
{
    flag_clock = 1;
    Timer_ReadStatusRegister();
    
    if(SendBytesFlag)//se è stato inserito 'B' o 'b'
    {
        ADC_DelSig_StopConvert();
        AMux_FastSelect(PHOTORESISTOR);
        ADC_DelSig_StartConvert();
        level = ADC_DelSig_Read32();
        
        if(level < 0)
            level = 0;
        if(level > 65535)
            level = 65535;
        
        DataBuffer[BRIGHT_MSB] = level >> 8;
        DataBuffer[BRIGHT_LSB] = level & 0xFF;
        
        if(level < 25000)
        {
           ADC_DelSig_StopConvert();
           AMux_FastSelect(POTENTIOMETER);
           ADC_DelSig_StartConvert();
           
           intensity = ADC_DelSig_Read32();
        
           if(intensity < 0)
            intensity = 0;
           if(intensity > 65535)
            intensity = 65535;
        
           DataBuffer[POT_MSB] = intensity >> 8;
           DataBuffer[POT_LSB] = intensity & 0xFF;
        
           PWM_LED_WriteCompare(intensity/257);
        }
        
        else 
        {
            PWM_LED_WriteCompare(0);
            DataBuffer[POT_MSB] = 0x00;
            DataBuffer[POT_LSB] = 0x00;
        }
      
        PacketReadyFlag = 1;
    }
    
    else
    {
        
        PWM_LED_WriteCompare(0);
    }
}

////////////////////////////////////////////////

CY_ISR(Custom_ISR_UART)
{
    char_received = UART_GetChar();
    switch(char_received)
    {
        case 'B':
        case 'b':
            SendBytesFlag = 1;
            Pin_EMBEDDED_LED_Write(ON);
            
            break;
        case 'S':
        case 's':
            SendBytesFlag = 0;
            Pin_EMBEDDED_LED_Write(OFF);
            
            break;  
        default:
            break;
    }
}
        
       
        


/* [] END OF FILE */
