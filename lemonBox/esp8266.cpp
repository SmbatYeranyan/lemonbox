#include <SoftwareSerial.h>
#include "esp8266.h"
#include "string.h"
#include <Arduino.h>


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
    uartSend("AT+CWMODE=2");
    delay(1000);
    //uartSend('AT+CWSAP="' + name + '","",1,0');
}

void esp8266::multipleConnections(){
	uartSend("AT+CIPMUX=1");
}

void esp8266::tcpServer(){
	uartSend("AT+CIPSERVER=1,80");
}
char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void esp8266::availableData(){
	if (Uart.available() > 0) {
		
    String memString = "Uart.readString();";
	/*	memString.replace('\n','=');
		memString.replace('\r','=');*/
    inChar = Uart.read(); // Read a character
    inData[index] = inChar; // Store it
    index++; // Increment where to write next
    inData[index] = '\0'; // Null terminate the string
/*

*/  
    //String str(inData);
    //printer->println(str);
    //printer->println(inData);
    String find = memString.substring(0,25);
    printer->println(inData);
		//printer->println(find.length());
    if (Uart.find("+IPD")){

      printer->println("IPD CHAR WAS FOUND:");
      //printer->println(Uart.readString().substring(0,4));
      if (Uart.find(":GET")){
        
        printer->println("GET WAS FOUND");
        printer->println(inData);
      }
      
    }
    if (findString("IPD",find) != -1){
          printer->println("IPD WAS FOUND:");
			if (findString(":GET",find) != -1){
				connection = find.indexOf(',');
		         client = find.substring(connection + 1  ,connection + 2);

				if (connection > 0){
					printer->println("found int: at: "+ client);
				}
				find ="";
				memString="";
		
				//String form = "";
	        
	        	Uart.print("AT+CIPSEND=" + client + "," + 155);
			    Uart.print("\r");
			    Uart.print("\n");
			    
			    Uart.print("<html><title>LemonBox</title>");
			    Uart.print("<body>");
			    Uart.print("<form method='POST' action='/'>");
			    Uart.print("<input type='text' name='key'/><input type='submit' value='submit'/>");
			    Uart.print("</form></body></html>");
			    Uart.print("\r");
			    Uart.print("\n");

			    delay(2000);
	        	Uart.print("AT+CIPCLOSE=" + client);
			    Uart.print("\r");
			    Uart.print("\n");
			    delay(1000);
	        	printer->println("GET WAS FOUND:");


			}

		}

		
		
/*        if (Uart.find("+IPD")){

        	
        }*/
	}

}


void esp8266::sendData(String data, String client){

	Uart.print("AT+CIPCLOSE="+ client);
    Uart.print("\r");
    Uart.print("\n");

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


int esp8266::findString(String needle, String haystack) {
  int foundpos = -1;
  for (int i = 0; (i < haystack.length() - needle.length()); i++) {
    if (haystack.substring(i,needle.length()+i) == needle) {
      foundpos = i;
    }
  }
  return foundpos;
}
 
