/**
  ******************************************************************************
  * @file    stm8s_tim2.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   This file contains all the functions for the TIM2 peripheral.
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8s_tim2.h"

/** @addtogroup STM8S_StdPeriph_Driver
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TI1_Config(uint8_t TIM2_ICPolarity, uint8_t TIM2_ICSelection, uint8_t TIM2_ICFilter);
static void TI2_Config(uint8_t TIM2_ICPolarity, uint8_t TIM2_ICSelection, uint8_t TIM2_ICFilter);
static void TI3_Config(uint8_t TIM2_ICPolarity, uint8_t TIM2_ICSelection, uint8_t TIM2_ICFilter);
/**
  * @addtogroup TIM2_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TIM2 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIM2_DeInit(void)
{
  TIM2->CR1 = (uint8_t)TIM2_CR1_RESET_VALUE;
  TIM2->IER = (uint8_t)TIM2_IER_RESET_VALUE;
  TIM2->SR2 = (uint8_t)TIM2_SR2_RESET_VALUE;
  
  /* Disable channels */
  TIM2->CCER1 = (uint8_t)TIM2_CCER1_RESET_VALUE;
  TIM2->CCER2 = (uint8_t)TIM2_CCER2_RESET_VALUE;
  
  
  /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
  TIM2->CCER1 = (uint8_t)TIM2_CCER1_RESET_VALUE;
  TIM2->CCER2 = (uint8_t)TIM2_CCER2_RESET_VALUE;
  TIM2->CCMR1 = (uint8_t)TIM2_CCMR1_RESET_VALUE;
  TIM2->CCMR2 = (uint8_t)TIM2_CCMR2_RESET_VALUE;
  TIM2->CCMR3 = (uint8_t)TIM2_CCMR3_RESET_VALUE;
  TIM2->CNTRH = (uint8_t)TIM2_CNTRH_RESET_VALUE;
  TIM2->CNTRL = (uint8_t)TIM2_CNTRL_RESET_VALUE;
  TIM2->PSCR = (uint8_t)TIM2_PSCR_RESET_VALUE;
  TIM2->ARRH  = (uint8_t)TIM2_ARRH_RESET_VALUE;
  TIM2->ARRL  = (uint8_t)TIM2_ARRL_RESET_VALUE;
  TIM2->CCR1H = (uint8_t)TIM2_CCR1H_RESET_VALUE;
  TIM2->CCR1L = (uint8_t)TIM2_CCR1L_RESET_VALUE;
  TIM2->CCR2H = (uint8_t)TIM2_CCR2H_RESET_VALUE;
  TIM2->CCR2L = (uint8_t)TIM2_CCR2L_RESET_VALUE;
  TIM2->CCR3H = (uint8_t)TIM2_CCR3H_RESET_VALUE;
  TIM2->CCR3L = (uint8_t)TIM2_CCR3L_RESET_VALUE;
  TIM2->SR1 = (uint8_t)TIM2_SR1_RESET_VALUE;
}

/**
  * @brief  Initializes the TIM2 Time Base Unit according to the specified parameters.
  * @param    TIM2_Prescaler specifies the Prescaler from TIM2_Prescaler_TypeDef.
  * @param    TIM2_Period specifies the Period value.
  * @retval None
  */
void TIM2_TimeBaseInit( TIM2_Prescaler_TypeDef TIM2_Prescaler,
                        uint16_t TIM2_Period)
{
  /* Set the Prescaler value */
  TIM2->PSCR = (uint8_t)(TIM2_Prescaler);
  /* Set the Autoreload value */
  TIM2->ARRH = (uint8_t)(TIM2_Period >> 8);
  TIM2->ARRL = (uint8_t)(TIM2_Period);
}


/**
  * @brief  Initializes the TIM2 Channel1 according to the specified parameters.
  * @param   TIM2_OCMode specifies the Output Compare mode  from @ref TIM2_OCMode_TypeDef.
  * @param   TIM2_OutputState specifies the Output State  from @ref TIM2_OutputState_TypeDef.
  * @param   TIM2_Pulse specifies the Pulse width  value.
  * @param   TIM2_OCPolarity specifies the Output Compare Polarity  from @ref TIM2_OCPolarity_TypeDef.
  * @retval None
  */


/**
  * @brief  Initializes the TIM2 Channel2 according to the specified parameters.
  * @param   TIM2_OCMode specifies the Output Compare mode  from @ref TIM2_OCMode_TypeDef.
  * @param   TIM2_OutputState specifies the Output State  from @ref TIM2_OutputState_TypeDef.
  * @param   TIM2_Pulse specifies the Pulse width  value.
  * @param   TIM2_OCPolarity specifies the Output Compare Polarity  from @ref TIM2_OCPolarity_TypeDef.
  * @retval None
  */

/**
  * @brief  Initializes the TIM2 Channel3 according to the specified parameters.
  * @param   TIM2_OCMode specifies the Output Compare mode from @ref TIM2_OCMode_TypeDef.
  * @param   TIM2_OutputState specifies the Output State from @ref TIM2_OutputState_TypeDef.
  * @param   TIM2_Pulse specifies the Pulse width value.
  * @param   TIM2_OCPolarity specifies the Output Compare Polarity  from @ref TIM2_OCPolarity_TypeDef.
  * @retval None
  */

/**
  * @brief  Initializes the TIM2 peripheral according to the specified parameters.
  * @param    TIM2_Channel specifies the Input Capture Channel from @ref TIM2_Channel_TypeDef.
  * @param   TIM2_ICPolarity specifies the Input Capture Polarity from @ref TIM2_ICPolarity_TypeDef.
  * @param   TIM2_ICSelection specifies the Input Capture Selection from @ref TIM2_ICSelection_TypeDef.
  * @param   TIM2_ICPrescaler specifies the Input Capture Prescaler from @ref TIM2_ICPSC_TypeDef.
  * @param   TIM2_ICFilter specifies the Input Capture Filter value (value can be an integer from 0x00 to 0x0F).
  * @retval None
  */

/**
  * @brief  Configures the TIM2 peripheral in PWM Input Mode according to the specified parameters.
    * @param    TIM2_Channel specifies the Input Capture Channel from @ref TIM2_Channel_TypeDef.
  * @param   TIM2_ICPolarity specifies the Input Capture Polarity from @ref TIM2_ICPolarity_TypeDef.
  * @param   TIM2_ICSelection specifies the Input Capture Selection from @ref TIM2_ICSelection_TypeDef.
  * @param   TIM2_ICPrescaler specifies the Input Capture Prescaler from @ref TIM2_ICPSC_TypeDef.
  * @param   TIM2_ICFilter specifies the Input Capture Filter value (value can be an integer from 0x00 to 0x0F).
  * @retval None
  */

/**
  * @brief  Enables or disables the TIM2 peripheral.
  * @param   NewState new state of the TIM2 peripheral. This parameter can
  * be ENABLE or DISABLE.
  * @retval None
  */
void TIM2_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));
  
  /* set or Reset the CEN Bit */
  if (NewState != DISABLE)
  {
    TIM2->CR1 |= (uint8_t)TIM2_CR1_CEN;
  }
  else
  {
    TIM2->CR1 &= (uint8_t)(~TIM2_CR1_CEN);
  }
}

/**
  * @brief  Enables or disables the specified TIM2 interrupts.
  * @param   NewState new state of the TIM2 peripheral.
  * This parameter can be: ENABLE or DISABLE.
  * @param   TIM2_IT specifies the TIM2 interrupts sources to be enabled or disabled.
  * This parameter can be any combination of the following values:
  *                       - TIM2_IT_UPDATE: TIM2 update Interrupt source
  *                       - TIM2_IT_CC1: TIM2 Capture Compare 1 Interrupt source
  *                       - TIM2_IT_CC2: TIM2 Capture Compare 2 Interrupt source
  *                       - TIM2_IT_CC3: TIM2 Capture Compare 3 Interrupt source
  * @param   NewState new state of the TIM2 peripheral.
  * @retval None
  */
void TIM2_ITConfig(TIM2_IT_TypeDef TIM2_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM2_IT_OK(TIM2_IT));
  assert_param(IS_FUNCTIONALSTATE_OK(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIM2->IER |= (uint8_t)TIM2_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIM2->IER &= (uint8_t)(~TIM2_IT);
  }
}

/**
  * @brief  Enables or Disables the TIM2 Update event.
  * @param   NewState new state of the TIM2 peripheral Preload register. This parameter can
  * be ENABLE or DISABLE.
  * @retval None
  */

/**
  * @brief  Selects the TIM2 Update Request Interrupt source.
  * @param   TIM2_UpdateSource specifies the Update source.
  * This parameter can be one of the following values
  *                       - TIM2_UPDATESOURCE_REGULAR
  *                       - TIM2_UPDATESOURCE_GLOBAL
  * @retval None
  */

/**
  * @brief  Selects the TIM2\92s One Pulse Mode.
  * @param   TIM2_OPMode specifies the OPM Mode to be used.
  * This parameter can be one of the following values
  *                    - TIM2_OPMODE_SINGLE
  *                    - TIM2_OPMODE_REPETITIVE
  * @retval None
  */

/**
  * @brief  Configures the TIM2 Prescaler.
  * @param   Prescaler specifies the Prescaler Register value
  * This parameter can be one of the following values
  *                       -  TIM2_PRESCALER_1
  *                       -  TIM2_PRESCALER_2
  *                       -  TIM2_PRESCALER_4
  *                       -  TIM2_PRESCALER_8
  *                       -  TIM2_PRESCALER_16
  *                       -  TIM2_PRESCALER_32
  *                       -  TIM2_PRESCALER_64
  *                       -  TIM2_PRESCALER_128
  *                       -  TIM2_PRESCALER_256
  *                       -  TIM2_PRESCALER_512
  *                       -  TIM2_PRESCALER_1024
  *                       -  TIM2_PRESCALER_2048
  *                       -  TIM2_PRESCALER_4096
  *                       -  TIM2_PRESCALER_8192
  *                       -  TIM2_PRESCALER_16384
  *                       -  TIM2_PRESCALER_32768
  * @param   TIM2_PSCReloadMode specifies the TIM2 Prescaler Reload mode.
  * This parameter can be one of the following values
  *                       - TIM2_PSCRELOADMODE_IMMEDIATE: The Prescaler is loaded
  *                         immediately.
  *                       - TIM2_PSCRELOADMODE_UPDATE: The Prescaler is loaded at
  *                         the update event.
  * @retval None
  */

/**
  * @brief  Forces the TIM2 Channel1 output waveform to active or inactive level.
  * @param   TIM2_ForcedAction specifies the forced Action to be set to the output waveform.
  * This parameter can be one of the following values:
  *                       - TIM2_FORCEDACTION_ACTIVE: Force active level on OC1REF
  *                       - TIM2_FORCEDACTION_INACTIVE: Force inactive level on
  *                         OC1REF.
  * @retval None
  */

/**
  * @brief  Forces the TIM2 Channel2 output waveform to active or inactive level.
  * @param   TIM2_ForcedAction specifies the forced Action to be set to the output waveform.
  * This parameter can be one of the following values:
  *                       - TIM2_FORCEDACTION_ACTIVE: Force active level on OC2REF
  *                       - TIM2_FORCEDACTION_INACTIVE: Force inactive level on
  *                         OC2REF.
  * @retval None
  */

/**
  * @brief  Forces the TIM2 Channel3 output waveform to active or inactive level.
  * @param   TIM2_ForcedAction specifies the forced Action to be set to the output waveform.
  * This parameter can be one of the following values:
  *                       - TIM2_FORCEDACTION_ACTIVE: Force active level on OC3REF
  *                       - TIM2_FORCEDACTION_INACTIVE: Force inactive level on
  *                         OC3REF.
  * @retval None
  */

/**
  * @brief  Enables or disables TIM2 peripheral Preload register on ARR.
  * @param   NewState new state of the TIM2 peripheral Preload register.
  * This parameter can be ENABLE or DISABLE.
  * @retval None
  */

/**
  * @brief  Enables or disables the TIM2 peripheral Preload Register on CCR1.
  * @param   NewState new state of the Capture Compare Preload register.
  * This parameter can be ENABLE or DISABLE.
  * @retval None
  */

/**
  * @brief  Enables or disables the TIM2 peripheral Preload Register on CCR2.
  * @param   NewState new state of the Capture Compare Preload register.
  * This parameter can be ENABLE or DISABLE.
  * @retval None
  */

/**
  * @brief  Enables or disables the TIM2 peripheral Preload Register on CCR3.
  * @param   NewState new state of the Capture Compare Preload register.
  * This parameter can be ENABLE or DISABLE.
  * @retval None
  */

/**
  * @brief  Configures the TIM2 event to be generated by software.
  * @param   TIM2_EventSource specifies the event source.
  * This parameter can be one of the following values:
  *                       - TIM2_EVENTSOURCE_UPDATE: TIM2 update Event source
  *                       - TIM2_EVENTSOURCE_CC1: TIM2 Capture Compare 1 Event source
  *                       - TIM2_EVENTSOURCE_CC2: TIM2 Capture Compare 2 Event source
  *                       - TIM2_EVENTSOURCE_CC3: TIM2 Capture Compare 3 Event source
  * @retval None
  */

/**
  * @brief  Configures the TIM2 Channel 1 polarity.
  * @param   TIM2_OCPolarity specifies the OC1 Polarity.
  * This parameter can be one of the following values:
  *                       - TIM2_OCPOLARITY_LOW: Output Compare active low
  *                       - TIM2_OCPOLARITY_HIGH: Output Compare active high
  * @retval None
  */

/**
  * @brief  Configures the TIM2 Channel 2 polarity.
  * @param   TIM2_OCPolarity specifies the OC2 Polarity.
  * This parameter can be one of the following values:
  *                       - TIM2_OCPOLARITY_LOW: Output Compare active low
  *                       - TIM2_OCPOLARITY_HIGH: Output Compare active high
  * @retval None
  */

/**
  * @brief  Configures the TIM2 Channel 3 polarity.
  * @param   TIM2_OCPolarity specifies the OC3 Polarity.
  * This parameter can be one of the following values:
  *                       - TIM2_OCPOLARITY_LOW: Output Compare active low
  *                       - TIM2_OCPOLARITY_HIGH: Output Compare active high
  * @retval None
  */

/**
  * @brief  Enables or disables the TIM2 Capture Compare Channel x.
  * @param   TIM2_Channel specifies the TIM2 Channel.
  * This parameter can be one of the following values:
  *                       - TIM2_CHANNEL_1: TIM2 Channel1
  *                       - TIM2_CHANNEL_2: TIM2 Channel2
  *                       - TIM2_CHANNEL_3: TIM2 Channel3
  * @param   NewState specifies the TIM2 Channel CCxE bit new state.
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

/**
  * @brief  Selects the TIM2 Output Compare Mode. This function disables the
  * selected channel before changing the Output Compare Mode. User has to
  * enable this channel using TIM2_CCxCmd and TIM2_CCxNCmd functions.
  * @param   TIM2_Channel specifies the TIM2 Channel.
  * This parameter can be one of the following values:
  *                       - TIM2_CHANNEL_1: TIM2 Channel1
  *                       - TIM2_CHANNEL_2: TIM2 Channel2
  *                       - TIM2_CHANNEL_3: TIM2 Channel3
  * @param   TIM2_OCMode specifies the TIM2 Output Compare Mode.
  * This parameter can be one of the following values:
  *                       - TIM2_OCMODE_TIMING
  *                       - TIM2_OCMODE_ACTIVE
  *                       - TIM2_OCMODE_TOGGLE
  *                       - TIM2_OCMODE_PWM1
  *                       - TIM2_OCMODE_PWM2
  *                       - TIM2_FORCEDACTION_ACTIVE
  *                       - TIM2_FORCEDACTION_INACTIVE
  * @retval None
  */

/**
  * @brief  Sets the TIM2 Counter Register value.
  * @param   Counter specifies the Counter register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */

/**
  * @brief  Sets the TIM2 Autoreload Register value.
  * @param   Autoreload specifies the Autoreload register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */

/**
  * @brief  Sets the TIM2 Capture Compare1 Register value.
  * @param   Compare1 specifies the Capture Compare1 register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */

/**
  * @brief  Sets the TIM2 Capture Compare2 Register value.
  * @param   Compare2 specifies the Capture Compare2 register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */

/**
  * @brief  Sets the TIM2 Capture Compare3 Register value.
  * @param   Compare3 specifies the Capture Compare3 register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */

/**
  * @brief  Sets the TIM2 Input Capture 1 Prescaler.
  * @param   TIM2_IC1Prescaler specifies the Input Capture prescaler new value
  * This parameter can be one of the following values:
  *                       - TIM2_ICPSC_DIV1: no prescaler
  *                       - TIM2_ICPSC_DIV2: capture is done once every 2 events
  *                       - TIM2_ICPSC_DIV4: capture is done once every 4 events
  *                       - TIM2_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */

/**
  * @brief  Sets the TIM2 Input Capture 2 prescaler.
  * @param   TIM2_IC2Prescaler specifies the Input Capture prescaler new value
  * This parameter can be one of the following values:
  *                       - TIM2_ICPSC_DIV1: no prescaler
  *                       - TIM2_ICPSC_DIV2: capture is done once every 2 events
  *                       - TIM2_ICPSC_DIV4: capture is done once every 4 events
  *                       - TIM2_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */

/**
  * @brief  Sets the TIM2 Input Capture 3 prescaler.
  * @param   TIM2_IC3Prescaler specifies the Input Capture prescaler new value
  * This parameter can be one of the following values:
  *                       - TIM2_ICPSC_DIV1: no prescaler
  *                       - TIM2_ICPSC_DIV2: capture is done once every 2 events
  *                       - TIM2_ICPSC_DIV4: capture is done once every 4 events
  *                       - TIM2_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */

/**
  * @brief  Gets the TIM2 Input Capture 1 value.
  * @param  None
  * @retval Capture Compare 1 Register value.
  */

/**
  * @brief  Gets the TIM2 Input Capture 2 value.
  * @param  None
  * @retval Capture Compare 2 Register value.
  */

/**
  * @brief  Gets the TIM2 Input Capture 3 value.
  * @param  None
  * @retval Capture Compare 3 Register value.
  */

/**
  * @brief  Gets the TIM2 Counter value.
  * @param  None
  * @retval Counter Register value.
  */

/**
  * @brief  Gets the TIM2 Prescaler value.
  * @param  None
  * @retval Prescaler Register configuration value  @ref TIM2_Prescaler_TypeDef.
  */

/**
  * @brief  Checks whether the specified TIM2 flag is set or not.
  * @param   TIM2_FLAG specifies the flag to check.
  * This parameter can be one of the following values:
  *                       - TIM2_FLAG_UPDATE: TIM2 update Flag
  *                       - TIM2_FLAG_CC1: TIM2 Capture Compare 1 Flag
  *                       - TIM2_FLAG_CC2: TIM2 Capture Compare 2 Flag
  *                       - TIM2_FLAG_CC3: TIM2 Capture Compare 3 Flag
  *                       - TIM2_FLAG_CC1OF: TIM2 Capture Compare 1 over capture Flag
  *                       - TIM2_FLAG_CC2OF: TIM2 Capture Compare 2 over capture Flag
  *                       - TIM2_FLAG_CC3OF: TIM2 Capture Compare 3 over capture Flag
  * @retval FlagStatus The new state of TIM2_FLAG (SET or RESET).
  */

/**
  * @brief  Clears the TIM2\92s pending flags.
  * @param   TIM2_FLAG specifies the flag to clear.
  * This parameter can be one of the following values:
  *                       - TIM2_FLAG_UPDATE: TIM2 update Flag
  *                       - TIM2_FLAG_CC1: TIM2 Capture Compare 1 Flag
  *                       - TIM2_FLAG_CC2: TIM2 Capture Compare 2 Flag
  *                       - TIM2_FLAG_CC3: TIM2 Capture Compare 3 Flag
  *                       - TIM2_FLAG_CC1OF: TIM2 Capture Compare 1 over capture Flag
  *                       - TIM2_FLAG_CC2OF: TIM2 Capture Compare 2 over capture Flag
  *                       - TIM2_FLAG_CC3OF: TIM2 Capture Compare 3 over capture Flag
  * @retval None.
  */

/**
  * @brief  Checks whether the TIM2 interrupt has occurred or not.
  * @param   TIM2_IT specifies the TIM2 interrupt source to check.
  * This parameter can be one of the following values:
  *                       - TIM2_IT_UPDATE: TIM2 update Interrupt source
  *                       - TIM2_IT_CC1: TIM2 Capture Compare 1 Interrupt source
  *                       - TIM2_IT_CC2: TIM2 Capture Compare 2 Interrupt source
  *                       - TIM2_IT_CC3: TIM2 Capture Compare 3 Interrupt source
  * @retval ITStatus The new state of the TIM2_IT(SET or RESET).
  */
ITStatus TIM2_GetITStatus(TIM2_IT_TypeDef TIM2_IT)
{
  ITStatus bitstatus = RESET;
  uint8_t TIM2_itStatus = 0, TIM2_itEnable = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM2_GET_IT_OK(TIM2_IT));
  
  TIM2_itStatus = (uint8_t)(TIM2->SR1 & TIM2_IT);
  
  TIM2_itEnable = (uint8_t)(TIM2->IER & TIM2_IT);
  
  if ((TIM2_itStatus != (uint8_t)RESET ) && (TIM2_itEnable != (uint8_t)RESET ))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return (ITStatus)(bitstatus);
}

/**
  * @brief  Clears the TIM2's interrupt pending bits.
  * @param   TIM2_IT specifies the pending bit to clear.
  * This parameter can be one of the following values:
  *                       - TIM2_IT_UPDATE: TIM2 update Interrupt source
  *                       - TIM2_IT_CC1: TIM2 Capture Compare 1 Interrupt source
  *                       - TIM2_IT_CC2: TIM2 Capture Compare 2 Interrupt source
  *                       - TIM2_IT_CC3: TIM2 Capture Compare 3 Interrupt source
  * @retval None.
  */
void TIM2_ClearITPendingBit(TIM2_IT_TypeDef TIM2_IT)
{
  /* Check the parameters */
  assert_param(IS_TIM2_IT_OK(TIM2_IT));
  
  /* Clear the IT pending Bit */
  TIM2->SR1 = (uint8_t)(~TIM2_IT);
}

/**
  * @brief  Configure the TI1 as Input.
  * @param   TIM2_ICPolarity  The Input Polarity.
  * This parameter can be one of the following values:
  *                       - TIM2_ICPOLARITY_FALLING
  *                       - TIM2_ICPOLARITY_RISING
  * @param   TIM2_ICSelection specifies the input to be used.
  * This parameter can be one of the following values:
  *                       - TIM2_ICSELECTION_DIRECTTI: TIM2 Input 1 is selected to
  *                         be connected to IC1.
  *                       - TIM2_ICSELECTION_INDIRECTTI: TIM2 Input 1 is selected to
  *                         be connected to IC2.
  * @param   TIM2_ICFilter Specifies the Input Capture Filter.
  * This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */

/**
  * @brief  Configure the TI2 as Input.
  * @param   TIM2_ICPolarity  The Input Polarity.
  * This parameter can be one of the following values:
  *                       - TIM2_ICPOLARITY_FALLING
  *                       - TIM2_ICPOLARITY_RISING
  * @param   TIM2_ICSelection specifies the input to be used.
  * This parameter can be one of the following values:
  *                       - TIM2_ICSELECTION_DIRECTTI: TIM2 Input 2 is selected to
  *                         be connected to IC2.
  *                       - TIM2_ICSELECTION_INDIRECTTI: TIM2 Input 2 is selected to
  *                         be connected to IC1.
  * @param   TIM2_ICFilter Specifies the Input Capture Filter.
  * This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */

/**
  * @brief  Configure the TI3 as Input.
  * @param   TIM2_ICPolarity  The Input Polarity.
  * This parameter can be one of the following values:
  *                       - TIM2_ICPOLARITY_FALLING
  *                       - TIM2_ICPOLARITY_RISING
  * @param   TIM2_ICSelection specifies the input to be used.
  * This parameter can be one of the following values:
  *                       - TIM2_ICSELECTION_DIRECTTI: TIM2 Input 3 is selected to
  *                         be connected to IC3.
  * @param   TIM2_ICFilter Specifies the Input Capture Filter.
  * This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */

/**
  * @}
  */
  
  /**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
