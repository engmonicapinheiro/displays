#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f407xx.h"

/* SPI1: PA5=SCK, PA6=MISO, PA7=MOSI (AF5) */
/* CS pin can be any GPIO, pass as argument */

#define SPI_BAUD_DIV2    0
#define SPI_BAUD_DIV4    (1U << 3)
#define SPI_BAUD_DIV8    (2U << 3)
#define SPI_BAUD_DIV16   (3U << 3)
#define SPI_BAUD_DIV32   (4U << 3)
#define SPI_BAUD_DIV64   (5U << 3)
#define SPI_BAUD_DIV128  (6U << 3)
#define SPI_BAUD_DIV256  (7U << 3)

void SpiInit(uint32_t baud);
void SpiCsLow(void);
void SpiCsHigh(void);
uint8_t SpiTransfer(uint8_t data);
void SpiBurstWrite(uint8_t *data, int len);
void SpiBurstRead(uint8_t *data, int len);

#endif
