#include "timebase.h"
#include "stm32f407xx.h"

/* generates an interrupt every second */
void TimebaseInit(void)
{
    /* Disable global interrupts */
    __disable_irq();

    /* Load the timer with number of clock cycles per second */
    SysTick->LOAD = ONE_SECOND_LOAD - 1;  //we are counting from 0

    /* Clear systick current value register */
    SysTick->VAL = 0;

    /* Select internal clock source */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;

    /* Enable interrupt */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    /* Enable systick */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    /* Enable global interrupts */
    __enable_irq();
}

/* generates an interrupt every millisecond */
void TimebaseMsInit(void)
{
    /* Disable global interrupts */
    __disable_irq();

    /* Load the timer with number of clock cycles per second */
    SysTick->LOAD = ONE_MS_SECOND_LOAD - 1;  //we are counting from 0

    /* Clear systick current value register */
    SysTick->VAL = 0;

    /* Select internal clock source */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;

    /* Enable interrupt */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    /* Enable systick */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    /* Enable global interrupts */
    __enable_irq();
}



/* delay in seconds or milliseconds */
void delay(uint32_t delay)
{
    uint32_t tickstart = GetTick();
    uint32_t wait = delay;

    while((GetTick() - tickstart) < wait);
}



uint32_t GetTick(void)
{
    __disable_irq();
    g_currentTick_previous = g_currentTick;
    __enable_irq();
    return g_currentTick_previous;
}

void TickIncrement(void)
{
    g_currentTick += TICK_FREQUENCY;
}

void SysTick_Handler(void)
{
    TickIncrement();
}