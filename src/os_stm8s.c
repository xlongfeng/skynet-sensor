/*
 * skynet sensor
 *
 * Copyright (c) 2018, longfeng.xiao <xlongfeng@126.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os.h"
#include "jiffies.h"

#define CONFIG_CLK_HSI_RC       (16000000)
#define CONFIG_CLK_HSI          (CONFIG_CLK_HSI_RC / 8)
#define CONFIG_CLK_MASTER       (CONFIG_CLK_HSI)
#define CONFIG_HZ               (HZ)

void mdelay(uint32_t ms)
{
    uint32_t delay = jiffies + msecs_to_jiffies(ms);

    while (time_before(jiffies, delay))
        watchdog();
}

void watchdog()
{
    if (jiffies_to_msecs(jiffies) < (7UL * 24 * 60 * 60 * 1000))
        IWDG_ReloadCounter();
}

void iwdog_init(void)
{
    IWDG_Enable();

    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    IWDG_SetPrescaler(IWDG_Prescaler_128);

    /* Set counter reload value to obtain 250ms IWDG Timeout.
     * Counter Reload Value = 250ms / IWDG counter clock period
     *                      = 250ms / (LsiFreq / 128)
     *                      = LsiFreq / (128 * 4)
     *                      = LsiFreq / 512
     */
    IWDG_SetReload((uint8_t)(128000 / 512));

    IWDG_ReloadCounter();
}

void uart_mode_transmit(void)
{
    GPIO_WriteHigh(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_2);
    GPIO_WriteHigh(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_1);
}

void uart_mode_receive(void)
{
    GPIO_WriteLow(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_1);
    GPIO_WriteLow(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_2);
}

void uart_init(void)
{
    UART1_DeInit();
    UART1_Init(19200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_1, GPIO_MODE_OUT_OD_LOW_SLOW);
    GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_2, GPIO_MODE_OUT_OD_LOW_SLOW);

    uart_mode_receive();
}

void led_init(void)
{
    GPIO_Init(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_5, GPIO_MODE_OUT_OD_LOW_SLOW);
}

void tim_init(void)
{
    TIM2_DeInit();
    TIM2_TimeBaseInit(TIM2_PRESCALER_2, CONFIG_HZ);
    TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
    TIM2_Cmd(ENABLE);
}

#ifdef DEBUG
void display_banner(void)
{
    hdprintf("\n\n");
    hdprintf("------------------------------\n");
    hdprintf("| STM8 Skynet Sensor Program |\n");
    hdprintf("------------------------------\n");
}

void reset_status(void)
{
    bool por = TRUE;

    hdprintf("Reset source:");

    if (RST_GetFlagStatus(RST_FLAG_WWDGF) != RESET) {
        hdprintf(" <Window watchdog> ");
        RST_ClearFlag(RST_FLAG_WWDGF);
        por = FALSE;
    }

    if (RST_GetFlagStatus(RST_FLAG_IWDGF) != RESET) {
        hdprintf(" <independent watchdog> ");
        RST_ClearFlag(RST_FLAG_IWDGF);
        por = FALSE;
    }

    if (RST_GetFlagStatus(RST_FLAG_ILLOPF) != RESET) {
        hdprintf(" <Illigal opcode> ");
        RST_ClearFlag(RST_FLAG_ILLOPF);
        por = FALSE;
    }

    if (RST_GetFlagStatus(RST_FLAG_SWIMF) != RESET) {
        hdprintf(" <SWIM reset> ");
        RST_ClearFlag(RST_FLAG_SWIMF);
        por = FALSE;
    }

    if (RST_GetFlagStatus(RST_FLAG_EMCF) != RESET) {
        hdprintf(" <EMC reset> ");
        RST_ClearFlag(RST_FLAG_EMCF);
        por = FALSE;
    }

    if (por) {
        hdprintf(" <Powerup reset> ");
    }

    hdprintf("\n");
}
#endif

void os_init(void)
{
    iwdog_init();
    uart_init();
    led_init();
    tim_init();

#ifdef DEBUG
    display_banner();
    reset_status();
#endif

    enableInterrupts();
}

int getchar(void)
{
    int c = -1;

    if (UART1_GetFlagStatus(UART1_FLAG_RXNE))
        c = UART1_ReceiveData8();

    return c;
}

int putchar(int c)
{
    if (c == '\n')
        putchar('\r');

    UART1_SendData8(c);

    while (UART1_GetFlagStatus(UART1_FLAG_TC) == RESET);

    return c;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
    hdprintf("Assert failed @ file:%s, line %d\n", file, line);

    /* Infinite loop */
    while (1) {
    }
}
#endif
