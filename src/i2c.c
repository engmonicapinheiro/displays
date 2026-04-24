#include "i2c.h"

void I2CInit(void)
{
    /* enable clock access to GPIOB */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    /* set PB8 and PB9 to alternate function mode */
    GPIOB->MODER &= ~(GPIO_MODER_MODER8_0);
    GPIOB->MODER |= GPIO_MODER_MODER8_1;

    GPIOB->MODER &= ~(GPIO_MODER_MODER9_0);
    GPIOB->MODER |= GPIO_MODER_MODER9_1;

    /* set PB8 and PB9 output type to open drain */
    GPIOB->OTYPER |= (GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9);

    /* enable pullup resistors for PB8 and PB9 */
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD8_0,
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD8_1);

    GPIOB->PUPDR |= GPIO_PUPDR_PUPD9_0,
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD9_1);

    /* set PB8 and PB9 aternate function type to I2C1 (AF4) */
    GPIOB->AFR[1] |= (4U << GPIO_AFRH_AFSEL8_Pos);
    GPIOB->AFR[1] |= (4U << GPIO_AFRH_AFSEL9_Pos);

    /* enable clock access to I2C1 module */
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    /* enter the reset mode */
    I2C1->CR1 |= I2C_CR1_SWRST;

    /* come out of reset mode */
    I2C1->CR1 &= ~(I2C_CR1_SWRST);

    /* set the I2C clock */
    I2C1->CR2 = (1U << 4); //16MHz

    /* set I2C to standard mode, 100KHz clock  */
    I2C1->CCR = I2C_100KHZ;

    /* set rise time */
    I2C1->TRISE = SD_MODE_MAX_RISE_TIME;

    /* enable I2C module */
    I2C1->CR1 |= I2C_CR1_PE;
}

void I2cByteRead(char slaveAddress, char memAddress, char *data)
{
    volatile int temp;

    /* wait until the bus is not busy */
    while(I2C1->SR2 & I2C_SR2_BUSY);

    /* generate start */
    I2C1->CR1 |= I2C_CR1_START;

    /* wait until start flag is set */
    while (!(I2C1->CR1 & I2C_CR1_START));

    /* transmit slave address + write */
    I2C1->DR = slaveAddress << 1;

    /* wait until address flag is set */
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    /* clear address flag */
    temp = I2C1->SR2;

    /* wait until transmitter is empty */
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    /* send memory address */
    I2C1->DR = memAddress;

    /* generate a restart */
    I2C1->CR1 |= I2C_CR1_START;

    /* wait until start flag is set */
    while(!(I2C1->SR1 & I2C_SR1_SB));

    /* transmit slave address + read */
    I2C1->DR = slaveAddress << 1 | 1;

    /* wait until start flag is set */
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    /* disable the acknowledge */
    I2C1->CR1 &= ~(I2C_CR1_ACK);

    /* clear addr flag */
    temp = I2C1->SR2;

    /* generate stop after data is received */
    I2C1->CR1 |= I2C_CR1_STOP;

    /* wait until RXNE flag is set */
    while(!(I2C1->SR1 & I2C_SR1_RXNE));

    /* read data from DR */
    *data++ = I2C1->DR;
}

void I2cBurstRead(char slaveAddress, char memAddress, char *data, int nrBytes)
{
    volatile int temp;

    /* wait until the bus is not busy */
    while(I2C1->SR2 & I2C_SR2_BUSY);

    /* generate start */
    I2C1->CR1 |= I2C_CR1_START;

    /* wait until start flag is set */
    while (!(I2C1->CR1 & I2C_CR1_START));

    /* transmit slave address + write */
    I2C1->DR = slaveAddress << 1;

    /* wait until address flag is set */
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    /* clear address flag */
    temp = I2C1->SR2;

    /* wait until transmitter is empty */
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    /* send memory address */
    I2C1->DR = memAddress;

    /* generate a restart */
    I2C1->CR1 |= I2C_CR1_START;

    /* wait until start flag is set */
    while(!(I2C1->SR1 & I2C_SR1_SB));

    /* transmit slave address + read */
    I2C1->DR = slaveAddress << 1 | 1;

    /* wait until start flag is set */
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    /* clear addr flag */
    temp = I2C1->SR2;

    /* enable the acknowledge */
    I2C1->CR1 |= (I2C_CR1_ACK);

    while(nrBytes > 0)
    {
        if(nrBytes == 1)
        {
            /* disable the acknowledge */
            I2C1->CR1 &= ~(I2C_CR1_ACK);

            /* generate stop after data is received */
            I2C1->CR1 |= I2C_CR1_STOP;

            /* wait until RXNE flag is set */
            while(!(I2C1->SR1 & I2C_SR1_RXNE));

            /* read data from DR */
            *data++ = I2C1->DR;

            break;
        }
        else
        {
            /* wait until RXNE flag is set */
            while(!(I2C1->SR1 & I2C_SR1_RXNE));

            /* read data from DR */
            *data++ = I2C1->DR;

            nrBytes--;
        }

    }

}


void I2cByteWrite(char slaveAddress, char memAddress, char *data)
{
    volatile int temp;

    /* wait until the bus is not busy */
    while(I2C1->SR2 & I2C_SR2_BUSY);

    /* generate start */
    I2C1->CR1 |= I2C_CR1_START;

    /* wait until start flag is set */
    while (!(I2C1->CR1 & I2C_CR1_START));

    /* transmit slave address + write */
    I2C1->DR = slaveAddress << 1;

    /* wait until address flag is set */
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    /* clear address flag */
    temp = I2C1->SR2;

    /* wait until transmitter is empty */
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    /* send memory address */
    I2C1->DR = memAddress;

    /* send data */
    I2C1->DR = *data;

    /* wait until transfer is finished */
    while(!(I2C1->SR1 & I2C_SR1_BTF));

    /* generate stop after data is transmitted */
    I2C1->CR1 |= I2C_CR1_STOP;
}

void I2cBurstWrite(char slaveAddress, char memAddress, char *data, int nrBytes)
{
    volatile int temp;

    /* wait until the bus is not busy */
    while(I2C1->SR2 & I2C_SR2_BUSY);

    /* generate start */
    I2C1->CR1 |= I2C_CR1_START;

    /* wait until start flag is set */
    while (!(I2C1->CR1 & I2C_CR1_START));

    /* transmit slave address + write */
    I2C1->DR = slaveAddress << 1;

    /* wait until address flag is set */
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    /* clear address flag */
    temp = I2C1->SR2;

    /* wait until transmitter is empty */
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    /* send memory address */
    I2C1->DR = memAddress;

    for(int i = 0; i < nrBytes; ++i)
    {
        /* wait until transmitter is empty */
        while (!(I2C1->SR1 & I2C_SR1_TXE));

        /* transmit the data */
        I2C1->DR  = *data++;
    }

    /* wait until transfer is finished */
    while(!(I2C1->SR1 & I2C_SR1_BTF));

    /* generate stop after data is transmitted */
    I2C1->CR1 |= I2C_CR1_STOP;

}
