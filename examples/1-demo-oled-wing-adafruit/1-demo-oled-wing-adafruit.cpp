#include "oled-wing-adafruit.h"

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

void graphicsTest();
void bitmapTest();

void setup() {
	display.setup();

	display.clearDisplay();
	display.display();
}

void loop() {
	display.loop();

	if (display.pressedA()) {
		display.clearDisplay();

		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0,0);
		display.println("Hello, world!");
		display.display();
	}
	if (display.pressedB()) {
		graphicsTest();
	}

	if (display.pressedC()) {
		bitmapTest();
	}
}

void graphicsTest() {
	display.clearDisplay();

	{
		uint8_t color = 1;
		for (int16_t i=0; i<display.height()/2; i+=3) {
			// alternate colors
			display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
			display.display();
			delay(1);
			color++;
		}
		delay(500);
		display.clearDisplay();
	}
	{
		for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
			display.drawTriangle(display.width()/2, display.height()/2-i,
					display.width()/2-i, display.height()/2+i,
					display.width()/2+i, display.height()/2+i, WHITE);
			display.display();
			delay(1);
		}
		delay(500);
		display.clearDisplay();
	}
	{
		uint8_t color = WHITE;
		for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
			display.fillTriangle(display.width()/2, display.height()/2-i,
					display.width()/2-i, display.height()/2+i,
					display.width()/2+i, display.height()/2+i, WHITE);
			if (color == WHITE) color = BLACK;
			else color = WHITE;
			display.display();
			delay(1);
		}
		delay(500);
		display.clearDisplay();
	}
	{
		for (int16_t i=0; i<display.height()/2-2; i+=2) {
			display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
			display.display();
			delay(1);
		}
		delay(500);
		display.clearDisplay();
		display.display();
	}
}

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char logo16_glcd_bmp[] =
{   B00000000, B11000000,
		B00000001, B11000000,
		B00000001, B11000000,
		B00000011, B11100000,
		B11110011, B11100000,
		B11111110, B11111000,
		B01111110, B11111111,
		B00110011, B10011111,
		B00011111, B11111100,
		B00001101, B01110000,
		B00011011, B10100000,
		B00111111, B11100000,
		B00111111, B11110000,
		B01111100, B11110000,
		B01110000, B01110000,
		B00000000, B00110000 };


void bitmapTest() {
	display.clearDisplay();
	display.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
	display.display();
}
