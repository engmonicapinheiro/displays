#include "st7735.h"
#include "timebase.h"


/*STM32F4			ST7735
 * PA5(SCK)	  :     SCK
 * PA7(MOSI)  :     SDA
 * PB5		  :     RS(RES)
 * PB4		  :     DC
 * PB3		  :     CS 		*/



#define GPIOBEN			(1U<<1)

SPI_HandleTypeDef hspi1;


static void st7735_write_cmd(uint8_t cmd);
static void st7735_write_data(uint8_t data);

int32_t g_ymax,g_ymin, g_yrange;
uint16_t g_plot_bg_color;
uint32_t g_time_index;


void st7735_init(void)
{
	/*Init GPIOs*/
	st7735_gpio_init();

	/*Init SPI*/
	st7735_spi_init();

	/*Run init commands*/
	standard_init_cmds();

	/*Fill screen*/
	st7735_fill_screen(ST7735_COLOR_BLACK);
}

void st7735_fill_screen(uint16_t color)
{
	st7735_fill_rect(0,0,ST7735_WIDTH,ST7735_HEIGHT,color);
}
void standard_init_cmds(void)
{
	/*Set CS low*/
	ST7735_CS0;

	/*Set RES low*/
	ST7735_RES0;

	/*delay a bit*/
	delay(10);

	/*Set RES high*/
	ST7735_RES1;
	delay(10);

	/*Set Sleep Out and Booster*/
	st7735_write_cmd(0x11);

	/*delay a bit*/
	delay(120);

	/*Select color mode*/
	st7735_write_cmd(0x3A);

    /*Set color mode 16 bits*/
	st7735_write_data(5);

	/*Select memory ccess mode*/
	st7735_write_cmd(0x36);

	/*Set  horizontal refresh right to left and row address order*/
	st7735_write_data(0x14);

	/*Display on*/
	st7735_write_cmd(0x29);
}
void st7735_gpio_init(void)
{
	/*Enable clock access to GPIO*/
	RCC->AHB1ENR |=GPIOBEN;

	/*Set PB3,PB4 and PB5 as output pins*/

	GPIOB->MODER |=(1U<<6);
	GPIOB->MODER &=~(1U<<7);

	GPIOB->MODER |=(1U<<8);
	GPIOB->MODER &=~(1U<<9);

	GPIOB->MODER |=(1U<<10);
	GPIOB->MODER &=~(1U<<11);
}

void st7735_spi_init(void)
{


	/*Set spi configuration parameters*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction =  SPI_DIRECTION_1LINE;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity =  SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase =  SPI_PHASE_1EDGE;
	hspi1.Init.NSS =  SPI_NSS_SOFT;
	hspi1.Init.BuadRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;


	/*Initialize spi*/
	spi_init(&hspi1);


}

static void st7735_send_data(unsigned char data)
{
	spi_transmit(&hspi1, &data,1,1);
}

static void st7735_write_cmd(uint8_t cmd)
{
	/*Set DC low*/
	ST7735_DC0;

	/*Send command*/
	st7735_send_data(cmd);
}

static void st7735_write_data(uint8_t data)
{
	/*Set DC high*/
	ST7735_DC1;

	/*Send data*/
	st7735_send_data(data);
}

static void st7735_push_color(uint16_t color)
{
	/*High and Low bytes of color separately*/
	st7735_write_data((uint8_t)(color >> 8));
	st7735_write_data((uint8_t)color);
}



static void st7735_set_addr_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	/*Select Column Addr Set*/
	st7735_write_cmd(ST7735_CASET);
	st7735_write_data(0x00);
	/*x start*/
	st7735_write_data(x0);
	st7735_write_data(0x00);

	/*x end*/
	st7735_write_data(x1);
	st7735_write_data(0x00);


	/*Select Row Addr Set*/
	st7735_write_cmd(ST7735_RASET);
	st7735_write_data(0x00);

	/*x start*/
	st7735_write_data(y0);
	st7735_write_data(0x00);

	/*x end*/
	st7735_write_data(y1);

	/*Select Write to RAM*/
	st7735_write_cmd(ST7735_RAMWR);

}

void st7735_drw_px(int16_t x, int16_t y, uint16_t color)
{
    // Check if x,y coordinates are within the bounds of the display
    if((x < 0) || (x >= ST7735_WIDTH) || (y < 0) || (y >= ST7735_HEIGHT)) {
        return;
    }

    // Set the address window to the specific x,y location
    st7735_set_addr_window(x, y, x, y);

    //Set the color
    st7735_push_color(color);
}


void st7735_drw_vline(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    // Check for out-of-bounds coordinates
    if(x < 0 || x >= ST7735_WIDTH || y < 0 || y >= ST7735_HEIGHT) {
        return;
    }

    // Cap the height to the maximum possible value
    if(y + h > ST7735_HEIGHT) {
        h = ST7735_HEIGHT - y;
    }

    //Set the address window
    st7735_set_addr_window(x, y, x, y + h - 1);
    //Draw the line
    while(h--)
    {
        //Set the color
        st7735_push_color(color);
    }

}

void st7735_drw_hline(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    // Check for out-of-bounds coordinates
    if(x < 0 || x >= ST7735_WIDTH || y < 0 || y >= ST7735_HEIGHT) {
        return;
    }

    //Clip line if it exceeds the screen width
    if (x + w - 1 >= ST7735_WIDTH) {
    	w = ST7735_WIDTH - x;
    }

    //Set the address window
    st7735_set_addr_window(x, y, x + w - 1, y );

    for( int i = 0; i < w; i ++)
    {
        //Set the color
        st7735_push_color(color);
    }

}


void st7735_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{

	  // Check if the given coordinates are within the screen bounds
	  if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)){
		  return;
	  }

	  // Check if the width exceeds the screen bounds and adjust if necessary
	  if((x + w - 1) >= ST7735_WIDTH) {
		  w = ST7735_WIDTH  - x;
	  }

	  // Check if the height exceeds the screen bounds and adjust if necessary
	  if((y + h - 1) >= ST7735_HEIGHT){
		  h = ST7735_HEIGHT - y;
	  }

	  // Set the address window for the rectangle
	  st7735_set_addr_window(x, y, x+w-1, y+h-1);

	  for( y = h; y > 0; y--)
	  {
		  for( x = w; x > 0; x--)
		  {
		        //Set the color
		        st7735_push_color(color);
		  }
	  }
}
void st7735_draw_char(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size)
{
    // Check if the character is out of bounds
    if(((x + 5*size - 1) >= ST7735_WIDTH)  || // check right
       ((y + 8*size - 1) >= ST7735_HEIGHT) || // check bottom
       ((x + 5*size - 1) < 0)        || // check left
       ((y + 8*size - 1) < 0)){         // check top
        return;
    }
    // Set the address window for the character
     st7735_set_addr_window(x, y, x+6*size-1, y+8*size-1);

     uint8_t character_row = 0x01;
     // Iterate through the rows of the character

     for(int row = 0; row < 8; row++){
			 // Iterate through the columns of the character
			 for(int col = 0; col < 5; col++){

             // Check if the current pixel of the character should be drawn
             if(Font[(c*5)+col] & character_row){
                 // Draw a rectangle of text color pixels
                 st7735_fill_rect(x+(col*size), y+(row*size), size, size, textColor);
             } else {
                 // Draw a rectangle of background color pixels
                 st7735_fill_rect(x+(col*size), y+(row*size), size, size, bgColor);
             }
           }
		 // Draw blank column(s) to the right of character
			 st7735_fill_rect(x+(5*size), y+(row*size), size, size, bgColor);
			 character_row = character_row << 1;
     }
}

uint32_t st7735_drw_str(uint16_t x, uint16_t y, char *string, int16_t textColor)
{
    uint32_t characters_drawn = 0;
    // iterate through the string
    while(*string)
    {
    	st7735_draw_char(x*6, y*10, *string, textColor, ST7735_COLOR_BLACK, 1);
        string++;
        x++;

        characters_drawn++;
    }

    return characters_drawn;
}

void st7735_drw_axs(uint16_t axisColor,
					uint16_t bgColor,
					char *xLabel,
					char *yLabel1,
					uint16_t label1Color,
					char *yLabel2,
					uint16_t label2Color,
					int32_t ymax,
					int32_t ymin)
{

	  int i;

	  //assign ymax and ymin to global variables
	  g_ymax = ymax;
	  g_ymin = ymin;

	  //calculate the range of y-axis
	  g_yrange = g_ymax - g_ymin;

	  //initialize the time index for plotting
	  g_time_index = 0;

	  //set the background color for the plot
	  g_plot_bg_color = bgColor;

	  //fill the entire screen with the background color
	  st7735_fill_rect(0, 0, 128, 160, bgColor);

	  //draw horizontal axis line
	  st7735_drw_hline(10, 140, 101, axisColor);

	  //draw vertical axis line
	  st7735_drw_vline(10, 17, 124, axisColor);

	  //draw tick marks on horizontal axis
	  for(  i = 20; i<=110; i=i+10){
	    st7735_drw_px(i, 141, axisColor);
	  }

	  //draw tick marks on vertical axis
	  for(i = 17; i<120; i=i+10){
	    st7735_drw_px(9, i, axisColor);
	  }

	  //draw x-axis label
	  i =  50;
	  while((*xLabel) && (i < 100)){
	    st7735_draw_char(i, 145, *xLabel, axisColor, bgColor, 1);
	    i = i + 6;
	    xLabel++;
	  }

	  //check if there are two y-axis labels
	  if(*yLabel2)
	  {
		  i = 26;
		    while((*yLabel2) && (i < 50)){
		      st7735_draw_char(0, i, *yLabel2, label2Color, bgColor, 1);
		      i = i + 8;
		      yLabel2++;
		    }
		    i = 82;
	  }
	  /*Prep i for one label only*/
	  else
	  {
		  i = 42;
	  }
	  while((*yLabel1) && (i < 120)){
	   st7735_draw_char(0, i, *yLabel1, label1Color, bgColor, 1);
	    i = i + 8;
	    yLabel1++;
	  }

}

void st7735_plt_pt(int32_t data1, uint16_t color1)
{
	  // Scale the data value to the range of the display
	  data1 = ((data1 - g_ymin)*100)/g_yrange;

	  // Check for out of bounds data values
	  if(data1 > 98){
	    data1 = 98;
	    color1 = ST7735_COLOR_RED;
	  }
	  if(data1 < 0){
	    data1 = 0;
	    color1 = ST7735_COLOR_RED;
	  }

	  // Plot the point on the display
	  st7735_drw_px(g_time_index + 11, 116 - data1, color1);
	  st7735_drw_px(g_time_index + 11, 115 - data1, color1);
}


void st7735_plt_incr(void)
{
	  //increment the time index
	  g_time_index = (g_time_index + 1) % 100;

	  //clear the previous plotted point to maintain the scrolling effect
	  st7735_drw_vline(g_time_index + 11, 17, 100, g_plot_bg_color);
}
