

// set this to the hardware serial port you wish to use
// reference code: www.pjrc.com/teensy/td_uart.html
// 6/7/2014  not working yet
#include <SoftwareSerial.h>
#include "esp8266.h"
SoftwareSerial Uart(7, 8);
char inChar1;
int inByte1;

esp8266 Esp(Uart, Serial);

void setup() {
    
	Uart.begin(9600);
    
	pinMode(13, OUTPUT);           // set pin to input
	pinMode(20, OUTPUT);           // set pin to input
	pinMode(18, INPUT);           // set pin to input
	digitalWrite(20, HIGH);
		Serial.write("Starting....");
/*
  HWSERIAL.print("m"); // setup strings to initialize sensor
  HWSERIAL.print("g 1\n");  
  HWSERIAL.print("q");  */
}
int looper=0;
boolean on = false;
void loop() {
	/*Esp.availableData();*/
	if (digitalRead(18)){
		
	}


  if (Serial.available() > 0) {
    inByte1 = Serial.read();    // read in character
    inChar1 = (char)inByte1;     // convert it to ASCII viewable
/*    Serial.print(inByte);      // echo back values to both ports
    Serial.print(" ");
    Serial.print(inChar);
    Serial.print(" \n");*/
    if (inByte1 == 49){
    	if (on == true){
			digitalWrite(13, LOW); 
			digitalWrite(20, LOW); 
			on= false;
    	}else{

			digitalWrite(13, HIGH); 
			digitalWrite(20, HIGH); 
			on= true;
    		
    	}
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

    	Esp.getNetowrkIP();
    }

    if (inByte1 == 50){
    	//Esp.getNetowrkIP();
    	Esp.joinAccessPoint("","");

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
