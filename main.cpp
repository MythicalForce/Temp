#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "config.h"
#include "utils.h"

Layer layer(*matrix);

void setup()
{
  Serial.begin(115200);

  MatrixConfig::begin();
}

void loop()
{
  int x = random(virtualDisp->width());
  int y = random(virtualDisp->height());
  
  // Working code when used normaly
  //virtualDisp->drawPixelRGB888(x, y, random(255), random(255), random(255));

  // Trying to use the layer
  layer.drawPixel(x, y, random(255), random(255), random(255));
  layer.display();
}
