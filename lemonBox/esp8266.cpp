#include <SoftwareSerial.h>
#include "esp8266.h"
#include "string.h"
#include <Arduino.h>


esp8266::esp8266(SoftwareSerial U, Print &print)
{
	Uart = U;
	Serial.begin(9600);
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

String incoming;
boolean	network;
void esp8266::getNetowrkIP(){
	Uart.print("AT+CIFSR");
	Uart.print("\r");
	Uart.print("\n");
}


void esp8266::joinAccessPoint(String ssid, String pass){
    //uartSend("AT+CWJAP='"+ ssid +"','"+pass+"'");
    Uart.print("AT+CWQAP");
    Uart.print("\r");
    Uart.print("\n");
    delay(2000);
    Uart.print("AT+CWJAP=");
    Uart.print("\"");   //"ssid"
    Uart.print(ssid);
    Uart.print("\"");

    Uart.print(",");

    Uart.print("\"");    //"pwd"
    Uart.print(pass);
    Uart.println("\"");


}

void esp8266::multipleConnections(){
	uartSend("AT+CIPMUX=1");
}

void esp8266::tcpServer(){
	uartSend("AT+CIPSERVER=1,80");

}

void esp8266::listAccessPoints(){
	uartSend("AT+CWLAP");
}
char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character
int chlID =0;
void esp8266::availableData(){
	String data = "";

	if (Uart.available() > 0 ) {

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
			if (findString("CIFSR", data) != -1){
				printer->println("FOUND AN IP");
				printer->println(getValue(data,'\n',2));
			}
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
							String ssid =(getValue(getValue(getValue(data,'?',1),'&',0),'=',1));
							String pass =(getValue(getValue(data,'?',1),'=',2));
							printer->println(ssid+" " + pass);
							printer->println(data);
							joinAccessPoint(ssid,pass);
							delay(2000);
							reply(_id, "ok");
							


							while (millis()-start<3000) 
							{
								Uart.print("AT+CIPCLOSE=" + _id);
			
								Uart.print("\r");
								Uart.print("\n");
							}
							delay(100);
						}else{

							onboarding(_id);//onboarding
						}
					}
					if (findString(":POST",data) != -1){
						if (findString("/on", data) != -1){
							digitalWrite(20, HIGH); 
						}						
						if (findString("/off", data) != -1){
							digitalWrite(20, LOW); 
						}
						printer->println("POST WAS FOUND");
						reply(_id, "ok");
					}

				}
			
	/*        if (Uart.find("+IPD")){

	        	
	        }*/
			}
		}
	}
}

void esp8266::reply(String id, String msg){
	Uart.print("AT+CIPSEND=" + id + "," + 2);
	Uart.print("\r");
	Uart.print("\n");

	Uart.print(msg);
	Uart.print("\r");
	Uart.print("\n");

	delay(1000);
	Uart.print("AT+CIPCLOSE=" + id);
	Uart.print("\r");
	Uart.print("\n");
	delay(100);
}

void esp8266::onboarding(String id){

	String html;
	html ="<html><head><title>LemonBox</title>";
	html+="<style>body{text-align:center;}";
	html+="form{display:inline-block}";
	html+="form input{display:block}";
	html+="</style></head><body>";
	html+="<form method='GET' action='/'>";
	html+="<input type='text' placeholder='SSID' name='ssid'/>";
	html+="<input type='password'";
	html+="placeholder='PASSWORD' name='password'/>";
	html+="<input type='submit' value='submit'/>";
	html+="</form></body></html>";
/*	printer->println("MYID: "+id);
	Uart.print("AT+CIPSEND=" + id + "," + html.length());
	Uart.print("\r");
	Uart.print("\n");*/
/*
	Uart.print("AT+CIPSEND=" + id + "," + 354);
	delay(2000);*/

/*	unsigned long startMili;
	startMili = millis();
	bool foundWrite;
	while (millis()-startMili<3000) {    
        if(Uart.find(">")==true )
        {
			foundWrite = true;
           break;
        }
     }
	 if(foundWrite){*/
/*		Uart.print("<html><head><title>LemonBox</title>");
		Uart.print("<style>body{text-align:center;}");
		Uart.print("form{display:inline-block}");
		Uart.print("form input{display:block}");
		Uart.print("</style></head><body>");
		Uart.print("<form method='GET' action='/'>");
		Uart.print("<input type='text' placeholder='SSID' name='ssid'/>");
		Uart.print("<input type='text' placeholder='PASSWORD' name='password'/>");
		Uart.print("<input type='submit' value='submit'/>");
		Uart.print("</form></body></html>");
		Uart.print("\r");
		Uart.print("\n");

		delay(2000);
		closeMux(id);*/
	/*}*/

	send(id, html);

}

boolean esp8266::send(String id, String str)
{
	
    Uart.print("AT+CIPSEND=");

    Uart.print((id));
    Uart.print(",");
    Uart.print((str.length()));
        
    unsigned long start;
	start = millis();
	bool found;
	while (millis()-start<5000) {                          
        if(Uart.find(">")==true )
        {
			found = true;
           break;
        }
     }
	 if(found)
		Uart.print(str);
	else
	{
		closeMux(id);
		return false;
	}


    String data;
    start = millis();
	while (millis()-start<5000) {
     if(Uart.available()>0)
     {
     char a =Uart.read();
     data=data+a;
     }
     if (data.indexOf("SEND OK")!=-1)
     {
         return true;
     }
  }
  return false;
}

void esp8266::closeMux(String id){
	Uart.print("AT+CIPCLOSE=" + id);
	Uart.print("\r");
	Uart.print("\n");
}
void esp8266::sendStream(String data){
	

	for (int i = 0; i < data.length(); i++) { 
		String line = getValue(data, '\r', i);
		printer->println("line: "+line);
 
	}

}

String esp8266::getValue(String data, char separator, int index)
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
 
		