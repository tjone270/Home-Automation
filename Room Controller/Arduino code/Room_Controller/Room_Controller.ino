#include <SPI.h>
#include <Ethernet.h>
#define I2C_ADDR  0x20
#include "Wire.h"


int binValue = 0;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
byte ip[] = { 192, 168, 1, 164 };
byte gateway[] = { 192, 168, 1, 1 };
byte subnet[] = { 255, 255, 255, 0 };
EthernetServer server(80);

String readString;
 
void setup(){
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Wire.begin();
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  int binValue = 0;
  digitalWrite(13, HIGH);
  sendValueToLatch(0);
}
 
void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
 
        //read char by char HTTP request
        if (readString.length() < 100) {
 
          //store characters to string
          readString += c;
          //Serial.print(c);
        }
 
        //if HTTP request has ended
        if (c == '\n') {
 
          ///////////////
          Serial.println(readString); //print to serial monitor for debuging
 
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
 
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          client.println("<link rel='stylesheet' type='text/css' href='http://homeautocss.net84.net/a.css' />");
          client.println("<TITLE>Thomas Jones - Room Controller</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1>Thomas's Room - Controller</H1>");
          client.println("<hr />");
          client.println("<br />");
         
          client.println("<a href=\"/?relay11\"\">Turn on ceiling lights</a>");
          client.println("<a href=\"/?relay10\"\">Turn off ceiling lights</a>");
          client.println("<p></p>");
          client.println("<a href=\"/?relay21\"\">Turn on the ceiling fan (High)</a>");
          client.println("<a href=\"/?relay20\"\">Turn off the ceiling fan</a>");
          client.println("<p></p>");          
          client.println("<a href=\"/?relay41\"\">Turn on the bedside lamp</a>");
          client.println("<a href=\"/?relay40\"\">Turn off the bedside lamp</a>");
          client.println("<p></p>");
          client.println("<a href=\"/?allON\"\">Turn everything on</a>");
          client.println("<a href=\"/?allOFF\"\">Turn everything off</a>");
         // client.println("<p></p>");      
         // client.println("<a href=\"/?resetSystem\"\">Soft Reset</a>");
 
          client.println("</BODY>");
          client.println("</HTML>");
 
          delay(1);
       
          client.stop();
 
         
          if(readString.indexOf("?relay11") >0)
            turnOnRelay1();
            
      
          if(readString.indexOf("?relay10") >0)
            turnOffRelay1();
            
          
          if(readString.indexOf("?relay21") >0)
            turnOnRelay2();
            
      
          if(readString.indexOf("?relay20") >0)
            turnOffRelay2();
            
            
          if(readString.indexOf("?relay41") >0)
            turnOnRelay4();
            
      
          if(readString.indexOf("?relay40") >0)
            turnOffRelay4();
        
        
          if(readString.indexOf("?resetSystem") >0)
            allOFF();
            
         
          if(readString.indexOf("?allOFF") >0)
            allOFF();
            
         
          if(readString.indexOf("?allON") >0)
            allON();
    
          
          //clearing string for next read
          readString="";
           delay(100);
        }
      }
    }
  }
}

void sendValueToLatch(int latchValue)
{
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x12);
  Wire.write(latchValue);
  Wire.endTransmission();
}

void turnOnRelay1()
{
    binValue = (binValue + 1);
    sendValueToLatch(binValue);
}
void turnOffRelay1()
{
    binValue = (binValue - 1);
    sendValueToLatch(binValue);
}
void turnOnRelay2()
{
    binValue = (binValue + 2);
    sendValueToLatch(binValue);
}
void turnOffRelay2()
{
    binValue = (binValue - 2);
    sendValueToLatch(binValue);
}
void turnOnRelay4()
{
    binValue = (binValue + 8);
    sendValueToLatch(binValue);
}
void turnOffRelay4()
{
    binValue = (binValue - 8);
    sendValueToLatch(binValue);
}
void allOFF()
{
  binValue = 0;
  sendValueToLatch(0);
}
void allON()
{
  binValue = 255;
  sendValueToLatch(255);
}

