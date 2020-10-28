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

#include "Driver.h"
#include "GlobalVariables.h"

static int32 MeanLevel;
static int32 MeanIntensity;

void StartPeripherals()
{
    ADC_DelSig_Start();
    Timer_Start();
    Clock_Timer_ADC_Start();
    Clock_PWM_Start();
    PWM_LED_Start();
}

void StopPeripherals()
{
    ADC_DelSig_Stop();
    Timer_Stop();
    Clock_Timer_ADC_Stop();
    Clock_PWM_Stop();
    PWM_LED_Stop(); 
}

void FixedBytes()
{
    DataBuffer[0] = 0xA0; //The first element of the vector DataBuffer is this start byte
    DataBuffer[T_HOLD_MSB] = THRESHOLD_MSB; //putting threshold bytes in DataBuffer
    DataBuffer[T_HOLD_LSB] = THRESHOLD_LSB;
    DataBuffer[TRANSMIT_BUFFER_SIZE - 1] = 0xC0; //The last element of the vector DataBuffer is this stop byte
}

void VariableBytes()
{
    MeanLevel = SumLevel/10;
    MeanIntensity = SumIntensity/10;
    PWM_LED_WriteCompare(MeanIntensity/257);
    
    DataBuffer[PHOT_MSB] = MeanLevel >> 8; //save only the most significant byte
    DataBuffer[PHOT_LSB] = MeanLevel & 0xFF; //save only the least significant byte
    DataBuffer[POT_MSB] = MeanIntensity >> 8; //save only the most significant byte
    DataBuffer[POT_LSB] = MeanIntensity & 0xFF; //save only the least signnificant byte
           
}

/* [] END OF FILE */
