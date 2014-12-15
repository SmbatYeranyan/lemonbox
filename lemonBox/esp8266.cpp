#include <SoftwareSerial.h>
#include "Arduino.h"
#include "esp8266.h"


esp8266::esp8266(SoftwareSerial U, Print &print)
{
	Uart = U;
	printer = &print;
 	init();
}

void esp8266::init(){
	//Uart.begin(9600);	
}

void esp8266::check(){
    uartSend("AT");
}


void esp8266::accessPoint(String name){
    uartSend("AT+CWMODE=3");
    delay(1000);
    //uartSend('AT+CWSAP="' + name + '","",1,0');
}

void esp8266::multipleConnections(){
	uartSend("AT+CIPMUX=1");
}

void esp8266::tcpServer(){
	uartSend("AT+CIPSERVER=1,8888");
}
void esp8266::availableData(){
	if (Uart.available() > 0) {
		inByte = Uart.read();
		inChar = (char)inByte;
		

        if (Uart.find("+IPD")){

	        if (Uart.find(":POST")){
	        	printer->println("POST WAS FOUND:");
	        }
        	if(Uart.find(":GET")){
	        	printer->println("GET WAS FOUND:");
	        	String connection = (Uart.readString().substring(1,2));
	        	printer->println(connection);
	        	String form = "<html xmlns='http://www.w3.org/1999/xhtml'><title>TheLemonBox</title><body><form method='POST' action='/'><input type='text' name='key'/><input type='submit' value='submit'/></form></body></html>\r\n\r\n";

	        	// String complete = stack + form;
	        	sendData(form, connection);
        	}
        }
	}

}


void esp8266::sendData(String data, String client){
	uartSend("AT+CIPSEND="+ client +","+ data.length());
    uartSend(data);
	delay(100);
	uartSend("AT+CIPCLOSE="+ client);

}

void esp8266::uartSend(String data){
	Uart.print(data);
	Uart.print("\r");
    Uart.print("\n");
}

bool esp8266::Contains( String s, String search)
{
	int max = s.length() - search.length(); // the searchstring has to fit in the other one  
	for (int i=0; i<= max; i++) 
	{
		if (s.substring(i) == search) return true;  // or i
	}
	return false;  //or -1
}

