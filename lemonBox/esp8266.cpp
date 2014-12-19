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
int chlID =0;
void esp8266::availableData(){
	String data = "";
	if (Uart.available() > 0) {

		unsigned long start;
		start = millis();
		char c0 = Uart.read();
		if (c0 == '+')
		{
			
			while (millis()-start<1000) 
			{
				if (Uart.available()>0)
				{
					char c = Uart.read();
					data += c;
				}
				if (data.indexOf("\nOK")!=-1)
				{
					break;
				}
			}
			
			int sLen = strlen(data.c_str());
			int i,j;
			for (i = 0; i <= sLen; i++)
			{
				if (data[i] == ':')
				{
					break;
				}
				
			}
			boolean found = false;
			for (j = 4; j <= i; j++)
			{
				if (data[j] == ',')
				{
					found = true;
					break;
				}
				
			}
			int iSize;
			printer->println(data);
			
			if(found ==true)
			{
				String _id = data.substring(4, j);
				chlID = _id.toInt();
			
				printer->println(chlID);

				if (findString("IPD,",data) != -1){

					printer->println("IPD CHAR WAS FOUND:");
					//printer->println(Uart.readString().substring(0,4));
					if (findString(":GET",data) != -1){

						if (findString("ssid=", data) != -1){
							printer->println("SSID is found");
							
							}else{



							Uart.print("AT+CIPSEND=" + _id + "," + 191);
							Uart.print("\r");
							Uart.print("\n");

							Uart.print("<html><title>LemonBox</title>");
							Uart.print("<body>");
							Uart.print("<form method='GET' action='/'>");
							Uart.print("<input type='text' name='ssid'/>");
							Uart.print("<input type='text' name='password'/>");
							Uart.print("<input type='submit' value='submit'/>");
							Uart.print("</form></body></html>");
							Uart.print("\r");
							Uart.print("\n");

							delay(1000);
							Uart.print("AT+CIPCLOSE=" + _id);
							Uart.print("\r");
							Uart.print("\n");
							delay(100);
							printer->println("GET WAS FOUND:");
						}
					}
					if (findString(":POST",data) != -1){

						printer->println("POST WAS FOUND");
						Uart.print("AT+CIPSEND=" + _id + "," + 2);
						Uart.print("\r");
						Uart.print("\n");

						Uart.print("ok");
						Uart.print("\r");
						Uart.print("\n");

						delay(1000);
						Uart.print("AT+CIPCLOSE=" + _id);
						Uart.print("\r");
						Uart.print("\n");
						delay(100);
					}

				}
			
	/*        if (Uart.find("+IPD")){

	        	
	        }*/
			}
		}
	}
}

void esp8266::sendStream(String data, String size){
	String split = "hi this is a split test";
	String word3 = getValue(split, ' ', 2);
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
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
 
		