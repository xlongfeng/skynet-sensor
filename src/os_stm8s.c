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

void clk_init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

void watchdog(void)
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
    GPIO_WriteHigh(GPIOA, GPIO_PIN_2);
    GPIO_WriteHigh(GPIOA, GPIO_PIN_1);
}

void uart_mode_receive(void)
{
    GPIO_WriteLow(GPIOA, GPIO_PIN_1);
    GPIO_WriteLow(GPIOA, GPIO_PIN_2);
}

void uart_init(void)
{
    UART1_DeInit();
    UART1_Init(38400, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_OD_LOW_SLOW);
    GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_OD_LOW_SLOW);

    uart_mode_receive();
}

void led_init(void)
{
    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_OD_LOW_SLOW);
}

void tim_init(void)
{
    TIM2_DeInit();
    TIM2_TimeBaseInit(TIM2_PRESCALER_16, CONFIG_HZ);
    TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
    TIM2_Cmd(ENABLE);
}

#define FLASH_ID_ADDR       ((uint32_t)((uint32_t)FLASH_DATA_START_PHYSICAL_ADDRESS + (uint32_t)0))
#define FLASH_ID_NE_ADDR    ((uint32_t)((uint32_t)FLASH_DATA_START_PHYSICAL_ADDRESS + (uint32_t)1))

#define FLASH_TYPE_ADDR     ((uint32_t)((uint32_t)FLASH_DATA_START_PHYSICAL_ADDRESS + (uint32_t)2))
#define FLASH_TYPE_NE_ADDR  ((uint32_t)((uint32_t)FLASH_DATA_START_PHYSICAL_ADDRESS + (uint32_t)3))

void write_device_id(uint8_t id)
{
    FLASH_ProgramByte(FLASH_ID_ADDR, id);
    FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
    FLASH_ProgramByte(FLASH_ID_NE_ADDR, (uint8_t)~id);
    FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
}

uint8_t read_device_id(void)
{
    uint8_t id = FLASH_ReadByte(FLASH_ID_ADDR);
    if ((uint8_t)~id == FLASH_ReadByte(FLASH_ID_NE_ADDR))
        return id;
    else
        return 0xff;
}

void write_device_type(uint8_t type)
{
    FLASH_ProgramByte(FLASH_TYPE_ADDR, type);
    FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
    FLASH_ProgramByte(FLASH_TYPE_NE_ADDR, (uint8_t)~type);
    FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
}

uint8_t read_device_type(void)
{
    uint8_t type = FLASH_ReadByte(FLASH_TYPE_ADDR);
    if ((uint8_t)~type == FLASH_ReadByte(FLASH_TYPE_NE_ADDR))
        return type;
    else
        return UnknownDevice;
}

void flash_init(void)
{
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET);
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

void waterlevel_disable(void)
{
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);

    GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
}

void waterlevel_enable(void)
{
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);

    GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_OD_LOW_SLOW);
}

uint16_t query_waterlevel(void)
{
    uint16_t value = 0;

    waterlevel_enable();

    if (GPIO_ReadInputPin(GPIOC, GPIO_PIN_3) == RESET)
        value = 1;

    if (GPIO_ReadInputPin(GPIOC, GPIO_PIN_4) == RESET)
        value = 2;

    if (GPIO_ReadInputPin(GPIOC, GPIO_PIN_5) == RESET)
        value = 3;

    if (GPIO_ReadInputPin(GPIOC, GPIO_PIN_6) == RESET)
        value = 4;

    if (GPIO_ReadInputPin(GPIOC, GPIO_PIN_7) == RESET)
        value = 5;

    if (GPIO_ReadInputPin(GPIOD, GPIO_PIN_1) == RESET)
        value = 6;

    if (GPIO_ReadInputPin(GPIOD, GPIO_PIN_2) == RESET)
        value = 7;

    if (GPIO_ReadInputPin(GPIOD, GPIO_PIN_3) == RESET)
        value = 8;

    waterlevel_disable();

    return value;
}

void waterlevel_init(void)
{
    waterlevel_disable();
}

#define waterlevel_deinit()       waterlevel_disable()

typedef enum {
    UltrasonicTriggerStart,
    UltrasonicTriggerStop,
    UltrasonicEchoWaitHigh,
    UltrasonicEchoWaitLow,
    UltrasonicComplete,
} UltrasonicStage;

static uint16_t ultrasonic_value;
static UltrasonicStage stage = UltrasonicTriggerStart;
static uint32_t delay_time;
static uint32_t timeout;

void ultrasonic_init(void)
{
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_OD_LOW_SLOW);
    GPIO_WriteLow(GPIOD, GPIO_PIN_2);
    ultrasonic_value = 0xffff;
    stage = UltrasonicTriggerStart;
    delay_time = jiffies;
}

void ultrasonic_deinit(void)
{
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_NO_IT);
}

void ultrasonic_task(void)
{
    static uint32_t msec_from, usec_from;
    static int16_t msec_to, usec_to;

    if (time_before(jiffies, delay_time))
        return;

    if (time_after(jiffies, timeout)) {
        stage = UltrasonicTriggerStart;
    }

    switch (stage) {
    case UltrasonicTriggerStart:
        delay_time = jiffies + msecs_to_jiffies(2);
        timeout = jiffies + msecs_to_jiffies(100);
        stage = UltrasonicTriggerStop;
        GPIO_WriteHigh(GPIOD, GPIO_PIN_2);
        break;
    case UltrasonicTriggerStop:
        stage = UltrasonicEchoWaitHigh;
        GPIO_WriteLow(GPIOD, GPIO_PIN_2);
        break;
    case UltrasonicEchoWaitHigh:
        if (GPIO_ReadInputPin(GPIOD, GPIO_PIN_3)) {
            stage = UltrasonicEchoWaitLow;
            msec_from = jiffies_to_msecs(jiffies);
            usec_from = (int16_t)TIM2_GetCounter();
        }
        break;
    case UltrasonicEchoWaitLow:
        if (!GPIO_ReadInputPin(GPIOD, GPIO_PIN_3)) {
            stage = UltrasonicComplete;
            msec_to = jiffies_to_msecs(jiffies);
            usec_to = (int16_t)TIM2_GetCounter();
        }
        break;
    case UltrasonicComplete:
    default:
        stage = UltrasonicTriggerStart;
        delay_time = jiffies + msecs_to_jiffies(1000);
        ultrasonic_value = (uint16_t)((int32_t)((msec_to - msec_from) * 1000) + (usec_to - usec_from));
        break;
    }
}

uint16_t query_ultrasonic(void)
{
    return ultrasonic_value;
}

void device_switch(DeviceType type)
{
    waterlevel_deinit();
    ultrasonic_deinit();

    switch (type) {
    case WaterLevelDevice:
        waterlevel_init();
        break;
    case UltrasonicDevice:
        ultrasonic_init();
        break;
    default:
        break;
    }
}

void os_init(void)
{
    clk_init();
    iwdog_init();
    uart_init();
    led_init();
    tim_init();
    flash_init();
    device_switch(read_device_type());

#ifdef DEBUG
    display_banner();
    reset_status();
#endif

    enableInterrupts();
}

void os_schedule(void)
{
    switch (read_device_type()) {
    case WaterLevelDevice:
        break;
    case UltrasonicDevice:
        ultrasonic_task();
        break;
    default:
        break;
    }
    watchdog();
}

uint16_t query_device(void)
{
    uint16_t value = 0xffff;

    switch (read_device_type()) {
    case WaterLevelDevice:
        value = query_waterlevel();
        break;
    case UltrasonicDevice:
        value = query_ultrasonic();
        break;
    default:
        break;
    }

    return value;
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
