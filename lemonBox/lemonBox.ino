

// set this to the hardware serial port you wish to use
// reference code: www.pjrc.com/teensy/td_uart.html
// 6/7/2014  not working yet
#include <SoftwareSerial.h>
#include "esp8266.h"
SoftwareSerial Uart(10, 11);
char inChar;
int inByte;

esp8266 Esp(Uart, Serial);

void setup() {
  Serial.begin(9600);
  Uart.begin(9600);
 


/*
  HWSERIAL.print("m"); // setup strings to initialize sensor
  HWSERIAL.print("g 1\n");  
  HWSERIAL.print("q");  */
}
int looper=0;
void loop() {
	/*Esp.availableData();*/


  if (Serial.available() > 0) {
    inByte = Serial.read();    // read in character
    inChar = (char)inByte;     // convert it to ASCII viewable
/*    Serial.print(inByte);      // echo back values to both ports
    Serial.print(" ");
    Serial.print(inChar);
    Serial.print(" \n");*/
    if (inByte == 49){
/*	    Uart.write('A');
	    Uart.write('T');
	    Uart.write('+');
	    Uart.write('C');
	    Uart.write('W');
	    Uart.write('M');
	    Uart.write('O');
	    Uart.write('D');
	    Uart.write('E');
	    Uart.write('=');
	    Uart.write('1');
	    Uart.write('\n\r');
    	*/
    }

    if (inByte == 50){
/*	    Uart.print("AT+CWMODE?");
	    Uart.print("\n");
    	*/
    }

    if (inByte == 51){
	    Uart.print("AT");
	    Uart.print("\r");
	    Uart.print("\n");
    	
    }  

    if (inByte == 52){
    	//Serial.println("yolo");
    	Esp.accessPoint("lemonBoxTrial");
    	delay(1000);
    	Esp.multipleConnections();
    	delay(1000);
    	Esp.tcpServer();

    }  
  }
  Esp.availableData();
}
