#include "max7219_7seg.h"
#include "spi.h"
#include "timebase.h"


/*PA9  		   : CS
 * PA7(MOSI)   : DIN
 * PA5		   : CLK
 * GND		   : GND
 * VCC		   : +5V
 * */
SPI_HandleTypeDef hspi1;


static void cs_pin_init(void);
static void cs_enable(void);
static void cs_disable(void);
static void max7219_spi_init(void);



void max7219_init(void)
{

	uint8_t data_buff[2];

	/*Initialize CS pin*/
	cs_pin_init();

	/*Initialize SPI*/
	max7219_spi_init();

	/*Run init sequence*/

	/*Test: LightUp all displays*/
	data_buff[0] = 0x0F;
	data_buff[1] = 0x01;
	cs_enable();
	spi_transmit(&hspi1,data_buff,2,1);
	cs_disable();
	delay(10);

	/*Test: Turnoff all displays*/
	data_buff[0] = 0x0F;
	data_buff[1] = 0x00;
	cs_enable();
	spi_transmit(&hspi1,data_buff,2,1);
	cs_disable();

	/*Enable decode mode B on all displays*/
	data_buff[0] = 0x09;
	data_buff[1] = 0xFF;
	cs_enable();
	spi_transmit(&hspi1,data_buff,2,1);
	cs_disable();

	/*Turn on the chip*/
	data_buff[0] = 0x0C;
	data_buff[1] = 0x01;
	cs_enable();
	spi_transmit(&hspi1,data_buff,2,1);
	cs_disable();

	/*Clear all displays*/
	max7219_clear();
}

static void max7219_spi_init(void)
{
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction =  SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity =  SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase =  SPI_PHASE_1EDGE;
	hspi1.Init.NSS =  SPI_NSS_SOFT;
	hspi1.Init.BuadRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;


	/*Initialize spi*/
	spi_init(&hspi1);


}

void max7219_write_number(uint8_t disp_pos, uint8_t num)
{

	uint8_t data_buff[2];

	data_buff[0] =  disp_pos;
	data_buff[1] =  num;

	cs_enable();
	spi_transmit(&hspi1,data_buff,2,1);
	cs_disable();


}

void max7219_clear(void)
{
	for(int i = 0; i<= NUM_OF_DISPLAYS; i++)
	{
		max7219_write_number(i,0x0F);
	}
}

static void cs_pin_init(void)
{
	/*Set Pa9 as output*/
	GPIOA->MODER |=(1U<<18);
	GPIOA->MODER &=~(1U<<19);
}


static void cs_enable(void)
{
	GPIOA->ODR &=~(1U<<9);
}

static void cs_disable(void)
{
	GPIOA->ODR |=(1U<<9);
}
