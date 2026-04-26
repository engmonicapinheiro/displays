#include "adxl345.h"
#include "i2c.h"

/* PB8 ... SCL -> yellow wire
 * PB9 ... SDA -> blue wire
 */


uint8_t dataValues[6];
const double FOUR_G_SCALE_FACTOR = 0.0078;

void AdxlReadAddress(uint8_t reg)
{
    I2cByteRead(DEVICE_ADDR, reg, &data);
}

void AdxlWrite(uint8_t reg, char value)
{
    char data[1];
    data[0] = value;
    I2cBurstWrite(DEVICE_ADDR, reg, data,1);
}

void AdxlReadValues(uint8_t reg)
{
    I2cBurstRead(DEVICE_ADDR, reg,  (char*)dataValues, 6);
}

void AdxlInit(void)
{
    /* enable the I2C module */
    I2CInit();

    /* read the device ID. this should return 0xE5 */
    AdxlReadAddress(DEVICE_REG);

    /* set the data format range to +-4G */
    AdxlWrite(DATA_FORMAT_REG, FOUR_G);

    /* reset all bits */
    AdxlWrite(POWER_CTL_REG, RESET);

    /* set the power control measure bit */
    AdxlWrite(POWER_CTL_REG, SET_MEASURE_B);
}