#include "timebase.h"
#include "stm32f4xx.h"

#define CTRL_ENABLE		(1U<<0)
#define CTRL_TICKINT	(1U<<1)
#define CTRL_CLCKSRC	(1U<<2)
#define CTRL_COUNTFLAG	(1U<<16)

#define ONE_SEC_LOAD	 80000000
#define ONE_MSEC_LOAD	 80000

#define MAX_DELAY		 0xFFFFFFFF

#define TICK_FREQ		 1

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;


#define PLL_M  4
#define PLL_N 80
#define PLL_P 2
#define PLL_Q 4

void sys_clck_config_80mhz(void)
{
    uint32_t start_up_counter = 0, hse_status = 0;

    /* Enable HSE */
    RCC->CR |= RCC_CR_HSEON;

    /* Wait until HSE is ready */
    do
    {
        hse_status = RCC->CR & RCC_CR_HSERDY;
        start_up_counter++;
    } while((hse_status == 0) && (start_up_counter != 3000));

    if (hse_status)
    {
    	 /* Enable  inpowerterface clock */
    	  RCC->APB1ENR |= RCC_APB1ENR_PWREN;

          /* Select the Voltage Range 1 (1.8V) */
          PWR->CR &= (uint32_t)~(PWR_CR_VOS);

          /* HCLK = SYSCLK / 1*/
          RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

          /* PCLK2 */
          RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

          /* PCLK1 */
          RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

          /* Configure the main PLL */
            RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                               (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

            /* Enable the main PLL */
            RCC->CR |= RCC_CR_PLLON;

            /* Wait until the main PLL is ready */
            while((RCC->CR & RCC_CR_PLLRDY) == 0)
            {
            }
            /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
            FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_3WS;

            /* Select the main PLL as system clock source */
            RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
            RCC->CFGR |= RCC_CFGR_SW_PLL;

            /* Wait until the main PLL is used as system clock source */
            while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL){}
    }
}

/*Delay in seconds*/
void delay(uint32_t delay)
{
	uint32_t tickstart =  get_tick();
	uint32_t wait =  delay;

	if(wait < MAX_DELAY)
	{
		wait += (uint32_t)TICK_FREQ;
	}

    while((get_tick() - tickstart) < wait){}

}

uint32_t get_tick(void)
{
	__disable_irq();
	g_curr_tick_p = g_curr_tick;
	__enable_irq();

	return g_curr_tick_p;

}
static void tick_increment(void)
{
	g_curr_tick += TICK_FREQ;
}
void timebase_init(void)
{

	/*Disable global interrupts*/
	__disable_irq();

    /*Load the timer with number of clock cycles per second*/
	SysTick->LOAD =  ONE_SEC_LOAD - 1;

    /*Clear systick current value register*/
	SysTick->VAL = 0;

    /*Select internal clock source*/
	SysTick->CTRL = CTRL_CLCKSRC;

    /*Enable interrupt*/
	SysTick->CTRL |= CTRL_TICKINT;

	/*Enable systick*/
	SysTick->CTRL |=CTRL_ENABLE;

	/*Enable global interrupts*/
	__enable_irq();
}

void timebase_msec_init(void)
{

	/*Disable global interrupts*/
	__disable_irq();

    /*Load the timer with number of clock cycles per second*/
	SysTick->LOAD =  ONE_MSEC_LOAD - 1;

    /*Clear systick current value register*/
	SysTick->VAL = 0;

    /*Select internal clock source*/
	SysTick->CTRL = CTRL_CLCKSRC;

    /*Enable interrupt*/
	SysTick->CTRL |= CTRL_TICKINT;

	/*Enable systick*/
	SysTick->CTRL |=CTRL_ENABLE;

	/*Enable global interrupts*/
	__enable_irq();
}


void SysTick_Handler(void)
{
	tick_increment();
}
