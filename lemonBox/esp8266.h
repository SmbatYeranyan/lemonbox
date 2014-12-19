
#ifndef esp8266_h
#define esp8266_h
#include <SoftwareSerial.h>
#include <Arduino.h>
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
    void sendStream(String data, String size);
    void sendData(String data, String client);
    void multipleConnections();
    void tcpServer();
    String getValue(String data, char seperator, int index);

  private:
    char inChar;
    int inByte;
    bool Contains(String s, String search);
    int findString(String s, String search);
  	Print* printer;
};

#endif