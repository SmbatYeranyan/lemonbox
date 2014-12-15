#include "Arduino.h"
#include "esp8266.h"

esp8266::esp8266()
{
  init();
}

void esp8266::init()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}


