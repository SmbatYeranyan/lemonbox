

// set this to the hardware serial port you wish to use
// reference code: www.pjrc.com/teensy/td_uart.html
// 6/7/2014  not working yet
#include <SoftwareSerial.h>
#include "esp8266.h"
SoftwareSerial Uart(10, 11);
char inChar1;
int inByte1;

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
    inByte1 = Serial.read();    // read in character
    inChar1 = (char)inByte1;     // convert it to ASCII viewable
/*    Serial.print(inByte);      // echo back values to both ports
    Serial.print(" ");
    Serial.print(inChar);
    Serial.print(" \n");*/
    if (inByte1 == 49){
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

    if (inByte1 == 50){
    	Esp.getNetowrkIP();

    }

    if (inByte1 == 51){
    	Esp.uartSend("AT+CIPCLOSE=0");
    	delay(100);
    	Esp.uartSend("AT+CIPCLOSE=1");
    	delay(100);
    	Esp.uartSend("AT+CIPCLOSE=2");
    	delay(100);
    	Esp.uartSend("AT+CIPCLOSE=3");
    	delay(100);
    	Esp.uartSend("AT+CIPCLOSE=4");
    	
    	delay(100);
    }  

    if (inByte1 == 52){
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
