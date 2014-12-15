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
    Uart.print("AT");
    Uart.print("\r");
    Uart.print("\n");
    printer->println("Sent At");
}


void esp8266::accessPoint(){
    Uart.print("AT+CWMODE=3");
    Uart.print("\r");
    Uart.print("\n");
    printer->println("Sent At");
}

void esp8266::multipleConnections(){
	Uart.print("AT+CIPMUX=1");
    Uart.print("\r");
    Uart.print("\n");
}

void esp8266::tcpServer(){
	Uart.print("AT+CIPSERVER=1,8888");
    Uart.print("\r");
    Uart.print("\n");
}
void esp8266::availableData(){
	if (Uart.available() > 0) {
		inByte = Uart.read();
		inChar = (char)inByte;
		

        if (Uart.find("+IPD")){
        	String connection = (Uart.readString().substring(1,2));
        	printer->println(connection);
        	//String stack ="GET / HTTP/1.1 \nHost: 192.168.4.1:8888 \nAccept: */* \nAuthorization: Basic XXX \nAccept-Encoding: gzip, deflate\n\rHTTP/1.1 200 OK\nVary: Authorization,Accept\nTransfer-Encoding: chunked\nEtag: 'fa2ba873343ba638123b7671c8c09998'\nContent-Type: application/html; charset=utf-8\nDate: Wed, 01 Jun 2011 14:59:30 GMT\nServer: thin 1.2.11 codename Bat-Shit Crazy\nAllow: GET,OPTIONS,HEAD\nCache-Control: public,max-age=120\nConnection: close \n\r";
        	String form = "<html xmlns='http://www.w3.org/1999/xhtml'><title>TheLemonBox</title><body><form method='POST' action='/'><input type='text' name='key'/><input type='submit' value='submit'/></form></body></html>\r\n\r\n";

        	// String complete = stack + form;
        	sendData(form, connection);
        	printer->println(Uart.readString());
        }
	}

}


void esp8266::sendData(String data, String client){
	Uart.print("AT+CIPSEND="+ client +","+ data.length());
    Uart.print("\r");
    Uart.print("\n");
    Uart.print(data);
    Uart.print("\r");
    Uart.print("\n");
	delay(100);
	Uart.print("AT+CIPCLOSE="+ client);
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

