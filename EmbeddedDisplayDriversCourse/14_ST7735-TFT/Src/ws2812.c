#include "stm32f4xx.h"
#include "ws2812.h"
#include "math.h"


#define NUM_COLORS_PER_LED		3  /*Red, Green and Blue*/
#define NUM_OF_CONFIG_PARAMS	(NUM_COLORS_PER_LED + 1)

#define PI 3.14159265

#define MAX_BRIGHTNESS		50

#define DATA_PCKT_SIZE		24
#define END_OF_TX_LEN		50

uint8_t LED_DATA[NUM_OF_LEDS][NUM_OF_CONFIG_PARAMS];
uint8_t LED_MOD[NUM_OF_LEDS][NUM_OF_CONFIG_PARAMS];

uint16_t PWM_DATA[(DATA_PCKT_SIZE *NUM_OF_LEDS) +END_OF_TX_LEN];

volatile uint8_t g_finished;

/*1.Init function :  PWM and DMA*/
/*Frequency = Timer_Clock / (TIM1->PSC + 1) / (TIM1->ARR + 1)*/
/*800kH = 80 000 000 / 1 / 100*/
void ws2812_init(void)
{
	/*Enable clock access to GPIOA and TIM1*/
	RCC->AHB1ENR |=(1U<<0);
	RCC->APB2ENR |=(1U<<0);

	/*Set PA8 as alternate function*/
	GPIOA->MODER &=~(1U<<16);
	GPIOA->MODER |= (1U<<17);

	/*Set alternate function type AF1 (TIM1_CH1)*/
	GPIOA->AFR[1] = (1U<<0);

	/*Configure tim1 for PWM output on channel 1*/
	TIM1->PSC = 0;
	TIM1->ARR = 100 - 1;
	TIM1->CNT =  0;

	/*Enable DMA request*/
	TIM1->DIER |=TIM_DIER_CC1DE;

	   /*
	        This line of code is configuring the PWM mode of the TIM1 channel 1,
	        specifically it configures the output compare module of the channel to PWM mode.
	        TIM_CCMR1_OC1M_2, TIM_CCMR1_OC1M_1, TIM_CCMR1_OC1PE are all flags that
	         are ORed together to configure the compare module
	        TIM_CCMR1_OC1M_2, TIM_CCMR1_OC1M_1 are used together to set the output
	        compare mode, in this case it's set to PWM mode 1.
	        TIM_CCMR1_OC1PE is used to enable preload register on the output
	        compare module, which allows to update the CCR register
	        value without any impact on the PWM output.
	    */
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
    TIM1->CCER |= TIM_CCER_CC1E;
    TIM1->BDTR = TIM_BDTR_MOE;

    /*Enable DMA2 and configure stream1 for TIM1 channel*/

    /*Enable clock access*/
    RCC->AHB1ENR |=(1U<<22);

    /*Disable DMA Stream before configuring*/
    DMA2_Stream1->CR &=~DMA_SxCR_EN;

    /*Configure DMA parameters*/
    DMA2_Stream1->CR |= (0x06 << 25) | DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0 | DMA_SxCR_MINC | DMA_SxCR_DIR_0 | DMA_SxCR_TCIE;

    /*Set peripheral address*/
    DMA2_Stream1->PAR = (uint32_t)(&TIM1->CCR1);

    /*Enable interrupt in NVIC*/
    NVIC_EnableIRQ(DMA2_Stream1_IRQn);



}
/*2.Set LED function*/
void ws2812_set_led( int led_num, int red, int green, int blue)
{
	LED_DATA[led_num][0] = led_num;
	LED_DATA[led_num][1] = red;
	LED_DATA[led_num][2] = green;
	LED_DATA[led_num][3] = blue;

}

/*3.Set Brightness*/

void ws2812_set_brightness(int brightness)
{
	if(brightness >  MAX_BRIGHTNESS)
	{
		brightness =  MAX_BRIGHTNESS;
	}

	for(int i = 0; i < NUM_OF_LEDS; i++)
	{
		LED_MOD[i][0] = LED_DATA[i][0];

		for(int j  = 1; j < NUM_OF_CONFIG_PARAMS; j++)
		{
			float angle =  90 - brightness;
			angle =  angle *PI/180; /*Angle in radians*/
			LED_MOD[i][j] = (LED_DATA[i][j])/(tan(angle));
		}

	}
}

/*4.Display pattern*/

void ws2812_display(void)
{
	uint32_t indx = 0;
	uint32_t color = 0;

	for(int i  =  0; i < NUM_OF_LEDS; i++)
	{
		color = ((LED_MOD[i][1]<<16) | (LED_MOD[i][2]<<8) | (LED_MOD[i][3]));

		for( int i = (DATA_PCKT_SIZE - 1); i  >= 0; i-- )
		{
			if(color &(1<<i))
			{
				PWM_DATA[indx] =  75;  /*2/3 of duty cycle*/
			}
			else
			{
				PWM_DATA[indx] =  25;  /*1/4 of duty cycle*/
			}

			indx++;
		}

	}
	for( int i = 0; i < END_OF_TX_LEN; i++)
	{
		PWM_DATA[indx] = 0;
		indx++;
	}

	/*Place buffer into DMA mememory*/
	DMA2_Stream1->M0AR =  (uint32_t)(&PWM_DATA);

	/*Set number of data items to be transered*/
	DMA2_Stream1->NDTR =  indx;

	/*Clear interrupt flags*/
	DMA2->LIFCR|=DMA_LIFCR_CFEIF1|DMA_LIFCR_CDMEIF1|DMA_LIFCR_CTEIF1|DMA_LIFCR_CHTIF1|DMA_LIFCR_CTCIF1;

	/*Enable TIM1*/
	TIM1->CR1 |= TIM_CR1_CEN;

	/*Enable DMA Stream*/
	DMA2_Stream1->CR |= DMA_SxCR_EN;

	while(g_finished == 0 ){}

	g_finished = 0;

}
/*5.DMA IRhandler*/

void DMA2_Stream1_IRQHandler(void)
{
	if(DMA2->LISR & DMA_LISR_TCIF1)
	{
		g_finished = 1;

		/*Disable TIM1*/
		TIM1->CR1 &= ~TIM_CR1_CEN;
		DMA2->LIFCR |= DMA_LIFCR_CTCIF1;
	}
}
