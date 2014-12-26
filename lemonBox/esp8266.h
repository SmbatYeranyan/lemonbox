
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
    void joinAccessPoint(String ssid, String pass);
    void uartSend(String data);
    void closeMux(String id);
    void reply(String id, String msg);
    void onboarding(String id);
    void sendStream(String data);
    void sendData(String data, String client);
    boolean send(String id, String str);
    void multipleConnections();
    void tcpServer();
    void listAccessPoints();
    void getNetowrkIP();
    String myIP;
    String getValue(String data, char seperator, int index);

  private:
    char inChar;
    int inByte;
    bool Contains(String s, String search);
    int findString(String s, String search);
  	Print* printer;
};

#endif