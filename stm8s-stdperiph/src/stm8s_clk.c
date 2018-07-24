/**
  ******************************************************************************
  * @file    stm8s_clk.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   This file contains all the functions for the CLK peripheral.
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

#include "stm8s_clk.h"

/** @addtogroup STM8S_StdPeriph_Driver
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private Constants ---------------------------------------------------------*/

/**
  * @addtogroup CLK_Private_Constants
  * @{
  */

CONST uint8_t HSIDivFactor[4] = {1, 2, 4, 8}; /*!< Holds the different HSI Divider factors */
CONST uint8_t CLKPrescTable[8] = {1, 2, 4, 8, 10, 16, 20, 40}; /*!< Holds the different CLK prescaler values */

/**
  * @}
  */

/* Public functions ----------------------------------------------------------*/
/**
  * @addtogroup CLK_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the CLK peripheral registers to their default reset
  * values.
  * @param  None
  * @retval None
  * @par Warning:
  * Resetting the CCOR register: \n
  * When the CCOEN bit is set, the reset of the CCOR register require
  * two consecutive write instructions in order to reset first the CCOEN bit
  * and the second one is to reset the CCOSEL bits.
  */

/**
  * @brief   Configures the High Speed Internal oscillator (HSI).
  * @par Full description:
  * If CLK_FastHaltWakeup is enabled, HSI oscillator is automatically
  * switched-on (HSIEN=1) and selected as next clock master
  * (CKM=SWI=HSI) when resuming from HALT/ActiveHalt modes.\n
  * @param   NewState this parameter is the Wake-up Mode state.
  * @retval None
  */

/**
  * @brief  Enable or Disable the External High Speed oscillator (HSE).
  * @param   NewState new state of HSEEN, value accepted ENABLE, DISABLE.
  * @retval None
  */

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @param   NewState new state of HSIEN, value accepted ENABLE, DISABLE.
  * @retval None
  */

/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  * @param  NewState new state of LSIEN, value accepted ENABLE, DISABLE.
  * @note   Before using the LSI clock you have to enable the option bytes (LSI_EN option bit is set).
  * @retval None
  */

/**
  * @brief  Enables or disablle the Configurable Clock Output (CCO).
  * @param   NewState : New state of CCEN bit (CCO register).
  * This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */

/**
  * @brief  Starts or Stops manually the clock switch execution.
  * @par Full description:
  * NewState parameter set the SWEN.
  * @param   NewState new state of SWEN, value accepted ENABLE, DISABLE.
  * @retval None
  */

/**
  * @brief  Configures the slow active halt wake up
  * @param   NewState: specifies the Slow Active Halt wake up state.
  * can be set of the following values:
  * - DISABLE: Slow Active Halt mode disabled;
  * - ENABLE:  Slow Active Halt mode enabled.
  * @retval None
  */

/**
  * @brief   Enables or disables the specified peripheral CLK.
  * @param   CLK_Peripheral : This parameter specifies the peripheral clock to gate.
  * This parameter can be any of the  @ref CLK_Peripheral_TypeDef enumeration.
  * @param   NewState : New state of specified peripheral clock.
  * This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */

/**
  * @brief  configures the Switch from one clock to another
  * @param   CLK_SwitchMode select the clock switch mode.
  * It can be set of the values of @ref CLK_SwitchMode_TypeDef
  * @param   CLK_NewClock choice of the future clock.
  * It can be set of the values of @ref CLK_Source_TypeDef
  * @param   NewState Enable or Disable the Clock Switch interrupt.
  * @param   CLK_CurrentClockState current clock to switch OFF or to keep ON.
  * It can be set of the values of @ref CLK_CurrentClockState_TypeDef
  * @note LSI selected as master clock source only if LSI_EN option bit is set.
  * @retval ErrorStatus this shows the clock switch status (ERROR/SUCCESS).
  */

/**
  * @brief  Configures the HSI clock dividers.
  * @param   HSIPrescaler : Specifies the HSI clock divider to apply.
  * This parameter can be any of the @ref CLK_Prescaler_TypeDef enumeration.
  * @retval None
  */
void CLK_HSIPrescalerConfig(CLK_Prescaler_TypeDef HSIPrescaler)
{
  /* check the parameters */
  assert_param(IS_CLK_HSIPRESCALER_OK(HSIPrescaler));

  /* Clear High speed internal clock prescaler */
  CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);

  /* Set High speed internal clock prescaler */
  CLK->CKDIVR |= (uint8_t)HSIPrescaler;
}

/**
  * @brief  Output the selected clock on a dedicated I/O pin.
  * @param   CLK_CCO : Specifies the clock source.
  * This parameter can be any of the  @ref CLK_Output_TypeDef enumeration.
  * @retval None
  * @par Required preconditions:
  * The dedicated I/O pin must be set at 1 in the corresponding Px_CR1 register \n
  * to be set as input with pull-up or push-pull output.
  */

/**
  * @brief   Enables or disables the specified CLK interrupts.
  * @param   CLK_IT This parameter specifies the interrupt sources.
  * It can be one of the values of @ref CLK_IT_TypeDef.
  * @param   NewState New state of the Interrupt.
  * Value accepted ENABLE, DISABLE.
  * @retval None
  */

/**
  * @brief  Configures the HSI and CPU clock dividers.
  * @param   ClockPrescaler Specifies the HSI or CPU clock divider to apply.
  * @retval None
  */

/**
  * @brief  Configures the SWIM clock frequency on the fly.
  * @param   CLK_SWIMDivider Specifies the SWIM clock divider to apply.
  * can be one of the value of @ref CLK_SWIMDivider_TypeDef
  * @retval None
  */

/**
  * @brief  Enables the Clock Security System.
  * @par Full description:
  * once CSS is enabled it cannot be disabled until the next reset.
  * @param  None
  * @retval None
  */

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None
  * @retval  Clock source used.
  * can be one of the values of @ref CLK_Source_TypeDef
  */

/**
  * @brief  This function returns the frequencies of different on chip clocks.
  * @param  None
  * @retval the master clock frequency
  */
uint32_t CLK_GetClockFreq(void)
{
  uint32_t clockfrequency = 0;
  CLK_Source_TypeDef clocksource = CLK_SOURCE_HSI;
  uint8_t tmp = 0, presc = 0;
  
  /* Get CLK source. */
  clocksource = (CLK_Source_TypeDef)CLK->CMSR;
  
  if (clocksource == CLK_SOURCE_HSI)
  {
    tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_HSIDIV);
    tmp = (uint8_t)(tmp >> 3);
    presc = HSIDivFactor[tmp];
    clockfrequency = HSI_VALUE / presc;
  }
  else if ( clocksource == CLK_SOURCE_LSI)
  {
    clockfrequency = LSI_VALUE;
  }
  else
  {
    clockfrequency = HSE_VALUE;
  }
  
  return((uint32_t)clockfrequency);
}

/**
  * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @par Full description:
  * @param   CLK_HSICalibrationValue calibration trimming value.
  * can be one of the values of @ref CLK_HSITrimValue_TypeDef
  * @retval None
  */

/**
  * @brief  Reset the SWBSY flag (SWICR Register)
  * @par Full description:
  * This function reset SWBSY flag in order to reset clock switch operations (target
  * oscillator is broken, stabilization is longing too much, etc.).  If at the same time \n
  * software attempts to set SWEN and clear SWBSY, SWBSY action takes precedence.
  * @param  None
  * @retval None
  */

/**
  * @brief  Checks whether the specified CLK flag is set or not.
  * @par Full description:
  * @param   CLK_FLAG Flag to check.
  * can be one of the values of @ref CLK_Flag_TypeDef
  * @retval FlagStatus, status of the checked flag
  */

/**
  * @brief  Checks whether the specified CLK interrupt has is enabled or not.
  * @param   CLK_IT specifies the CLK interrupt.
  * can be one of the values of @ref CLK_IT_TypeDef
  * @retval ITStatus, new state of CLK_IT (SET or RESET).
  */

/**
  * @brief  Clears the CLK’s interrupt pending bits.
  * @param   CLK_IT specifies the interrupt pending bits.
  * can be one of the values of @ref CLK_IT_TypeDef
  * @retval None
  */

/**
  * @}
  */
  
/**
  * @}
  */
  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
