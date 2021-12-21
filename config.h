#pragma once

#include <Arduino.h>

#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>

#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 64 // Number of pixels tall of each INDIVIDUAL panel module.

#define NUM_ROWS 2 // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 2 // Number of INDIVIDUAL PANELS per ROW
#define PANEL_CHAIN NUM_ROWS*NUM_COLS    // total number of panels chained one to another

// Change this to your needs, for details on VirtualPanel pls see ChainedPanels example
#define SERPENT true // Should be false
#define TOPDOWN false // Should be true

// Virtual Panl dimensions - our combined panel would be a square 4x4 modules with a combined resolution of 128x128 pixels
#define VPANEL_W PANEL_RES_X*NUM_COLS // Kosso: All Pattern files have had the MATRIX_WIDTH and MATRIX_HEIGHT replaced by these.
#define VPANEL_H PANEL_RES_Y*NUM_ROWS //

// placeholder for the matrix object
MatrixPanel_I2S_DMA *matrix = nullptr;

// placeholder for the virtual display object
VirtualMatrixPanel  *virtualDisp = nullptr;

namespace MatrixConfig
{
    void begin()
    {
        HUB75_I2S_CFG mxconfig(PANEL_RES_X, PANEL_RES_Y, PANEL_CHAIN);

        mxconfig.gpio.e = 18; // Must be pin 18 for 64x64 else -1

        matrix = new MatrixPanel_I2S_DMA(mxconfig);

        matrix->setBrightness8(127);

        if( not matrix->begin() )
        {
            Serial.println("****** !KABOOM! I2S memory allocation failed ***********");
        }

        virtualDisp = new VirtualMatrixPanel((*matrix), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, SERPENT, TOPDOWN);
    }
};

struct layerPixels {
	CRGB data[VPANEL_H][VPANEL_W]; 
};

class Layer : public Adafruit_GFX
{
	public:

		Layer(MatrixPanel_I2S_DMA &disp) : Adafruit_GFX (VPANEL_W, VPANEL_H)
        {
			matrix = &disp;
		}

		inline void init()
		{
			// https://stackoverflow.com/questions/5914422/proper-way-to-initialize-c-structs
			pixels = new layerPixels();
			
		} // end Layer

		void drawPixel(int16_t x, int16_t y, uint16_t color);   		// overwrite adafruit implementation
		void drawPixel(int16_t x, int16_t y, int r, int g, int b);		// Layer implementation		
		void drawPixel(int16_t x, int16_t y, CRGB color);				// Layer implementation		
		void clear();
	    void display();  //	flush to display / LED matrix

		inline uint16_t color565(uint8_t r, uint8_t g, uint8_t b)
        {
					return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
		}

		// For layer composition - accessed publically
		layerPixels *pixels;

		// Release Memory
		~Layer(void); 

	private:
		MatrixPanel_I2S_DMA *matrix = nullptr;
};


// For adafruit
void Layer::drawPixel(int16_t x, int16_t y, uint16_t color)
{

	// 565 color conversion
	uint8_t r = ((((color >> 11)  & 0x1F) * 527) + 23) >> 6;
	uint8_t g = ((((color >> 5)   & 0x3F) * 259) + 33) >> 6;
	uint8_t b = (((color & 0x1F)  * 527) + 23) >> 6;

	drawPixel(x, y, CRGB(r,g,b));
}

void Layer::drawPixel(int16_t x, int16_t y, int r, int g, int b)
{
	drawPixel(x, y, CRGB(r,g,b));
}

void Layer::drawPixel(int16_t x, int16_t y, CRGB color)
{

	if( x >= VPANEL_W 	|| x < 0) return; // 0;
	if( y >= VPANEL_H 	|| y < 0) return; // 0;
	
	pixels->data[y][x] = color;
}

void Layer::clear()
{ 

	memset(pixels, 0, sizeof(layerPixels) );
}

/**
 * Send the layer to the display device.
 */
void Layer::display() { 

	CRGB _pixel = 0 ;
	for (int y = 0; y < VPANEL_H; y++) {
		for (int x = 0; x < VPANEL_W; x++)
		{
			//_pixel = pixel[XY(x, y)];
			_pixel = pixels->data[y][x];

			matrix->drawPixelRGB888( x, y, _pixel.r, _pixel.g, _pixel.b);

		} // end loop to copy fast led to the dma matrix
	}

} // display

Layer::~Layer(void)
{
  free(pixels);
}
