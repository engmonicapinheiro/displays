#ifndef __WS2812_H__
#define __WS2812_H__

#define NUM_OF_LEDS		30

void ws2812_init(void);
void ws2812_set_led( int led_num, int red, int green, int blue);
void ws2812_set_brightness(int brightness);
void ws2812_display(void);

#endif
