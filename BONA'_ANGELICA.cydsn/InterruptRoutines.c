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

int32 level; //variable to save the photoresistor sample
int32 intensity; //variable to save the potentiometer sample
uint8 char_received; //variable to save the character to start or stop the system remotely


CY_ISR(Custom_ISR_ADC) //every 100ms the samples of the photoresistor and the potentiometer are saved
{
    flag_clock = 1;
    
    Timer_ReadStatusRegister();
    
    if(SendBytesFlag)//If 'B' o 'b' have been inserted
    {
        ADC_DelSig_StopConvert(); //Stop conversion
        AMux_FastSelect(PHOTORESISTOR); //Select photoresistor channel
        ADC_DelSig_StartConvert(); //Start coversion
        
        level = ADC_DelSig_Read32(); //save sample in level
        
        if(level < 0)
            level = 0;
        if(level > 65535)
            level = 65535;
        
        DataBuffer[PHOT_MSB] = level >> 8; //save only the most significant byte
        DataBuffer[PHOT_LSB] = level & 0xFF; //save only the least significant byte
        
        if(level < THRESHOLD)//if the light in the room is below a certain th
        {
           ADC_DelSig_StopConvert(); //Stop conversion
           AMux_FastSelect(POTENTIOMETER); //Select potetiometer channel
           ADC_DelSig_StartConvert(); //Start coversion
           
           intensity = ADC_DelSig_Read32();//save sample inn itensity
        
           if(intensity < 0)
            intensity = 0;
           if(intensity > 65535)
            intensity = 65535;
        
           DataBuffer[POT_MSB] = intensity >> 8; //save only the most significant byte
           DataBuffer[POT_LSB] = intensity & 0xFF; //save only the least signnificant byte
        
           PWM_LED_WriteCompare(intensity/257); //set Duty Cycle of PWM such that itensity = 65535 --> DC = 255
        }
        
        else //if the light in the room is above a certain th
        {
            PWM_LED_WriteCompare(0);//led switched off
            DataBuffer[POT_MSB] = 0x00; //set to zero to indicate that potentiometer is not being sampled
            DataBuffer[POT_LSB] = 0x00;
        }
      
        
    }
    
    else PWM_LED_WriteCompare(0); // if 'S' or 's' have been inserted the LED is switched off and sample values are no more saved
 
}

//////////////////////////////////////////////////////////////////

CY_ISR(Custom_ISR_UART) //ISR executed on UART byte received
{
    char_received = UART_GetChar(); //save the char received
    
    switch(char_received)
    {
        case 'B':
        case 'b':
            SendBytesFlag = 1;
            Pin_EMBEDDED_LED_Write(ON); //Embedded led ONN
            break;
        case 'S':
        case 's':
            SendBytesFlag = 0;
            Pin_EMBEDDED_LED_Write(OFF); //Embedded led OFF
            break;  
        default:
            break;
    }
}
        
       
        


/* [] END OF FILE */
