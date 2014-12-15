
#ifndef esp8266_h
#define esp8266_h
#include <SoftwareSerial.h>
#include "Arduino.h"
extern SoftwareSerial Uart;  	

class esp8266
{
  public:
    esp8266(SoftwareSerial U, Print &print);
    void init();
    void check();
    void availableData();
    void accessPoint(String name);
    void uartSend(String data);
    void sendData(String data, String client);
    void multipleConnections();
    void tcpServer();


  private:
  	char inChar;
  	int inByte;
  	String memoryString;
  	bool stringComplete;
  	bool Contains(String s, String search);
  	Print* printer;
};

#endif