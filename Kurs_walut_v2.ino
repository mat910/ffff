/// e-mail lwj12239@cdfaq.com
/// ZAQ!2wsx + tel
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
//#include <WiFiClient.h>
ESP8266WiFiMulti WiFiMulti;

#include <U8g2lib.h>
#include <SPI.h>
 U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, 14, 13, 15, U8X8_PIN_NONE);  
String Euro;
String USD;
String CHF;
String data;
String zloto;
float suma2;
int suma;
String srebro;
String uncjasrebro;
String uncjazloto;

void setup() {

  u8g2.begin();
  u8g2.setFont(u8g2_font_5x7_tf);
 
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(3);

  Serial.begin(115200);
  
/*
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }*/
  u8g2.clearBuffer();
  u8g2.drawFrame(0,0,128,64);
  u8g2.drawStr( 20,57, "Connecting");
  u8g2.drawStr( 30,57, "Wait");  
  u8g2.sendBuffer();
  delay(800);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("UPC242160429", "****8");
  u8g2.clearBuffer();
  u8g2.drawStr( 20,57, "Wifi Connected ");
  u8g2.drawStr( 30,57, "Success!"); 
  u8g2.sendBuffer();
  delay(100);
}

void loop() {
   WiFiClient client;
///////////////////////EURO/////////////////////
  if ((WiFiMulti.run() == WL_CONNECTED)) {

   
    HTTPClient http;

    if (http.begin(client, "http://api.thingspeak.com/apps/thinghttp/send_request?api_key=Y14QDTQCNUR617JJ"));
      int httpCode = http.GET();
      if (httpCode > 0) 
        {
        
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
        Euro = http.getString(); 
          } 

      http.end();
    }
//////////////////////USD/////////////////////
if ((WiFiMulti.run() == WL_CONNECTED)) {

  
    HTTPClient http;

    if (http.begin(client, "http://api.thingspeak.com/apps/thinghttp/send_request?api_key=ENI3XPSCGO0S4237"));
      int httpCode = http.GET();
      if (httpCode > 0) 
        {
        
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
        USD = http.getString(); 
          } 

      http.end();
    }

  //////////////////////CHF/////////////////////
if ((WiFiMulti.run() == WL_CONNECTED)) {

  
    HTTPClient http;

    if (http.begin(client, "http://api.thingspeak.com/apps/thinghttp/send_request?api_key=103T8XPU8W1LJWY8"));
      int httpCode = http.GET();
      if (httpCode > 0) 
        {
        
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
        CHF = http.getString(); 
          } 

      http.end();
    }

    //////////////////////zloto/////////////////////
if ((WiFiMulti.run() == WL_CONNECTED)) {

  
    HTTPClient http;

    if (http.begin(client, "http://api.thingspeak.com/apps/thinghttp/send_request?api_key=L6EAHPKZJ783N23Z"));
      int httpCode = http.GET();
      if (httpCode > 0) 
        {
        
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
        zloto = http.getString(); 
        zloto.remove(5,18);
        zloto.remove(1,1);
        USD[1] = '.';
        suma = ((zloto.toFloat()) * (USD.toFloat()));
        Serial.println(zloto.toFloat());
        Serial.println(USD.toFloat());
          } 

      http.end();
    }
     //////////////////////srebro/////////////////////
if ((WiFiMulti.run() == WL_CONNECTED)) {

  
    HTTPClient http;

    if (http.begin(client, "http://api.thingspeak.com/apps/thinghttp/send_request?api_key=3HZ9ZWDN5PYM7Y98"));
      int httpCode = http.GET();
      if (httpCode > 0) 
        {
        
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
        srebro = http.getString(); 
        srebro.remove(4,16);
        suma2 = ((srebro.toFloat()) * (USD.toFloat()));
        Serial.println(srebro.toFloat());
        Serial.println(USD.toFloat());
          } 

      http.end();
    }
    //////////////////////DATA/////////////////////
if ((WiFiMulti.run() == WL_CONNECTED)) {

  
    HTTPClient http;

    if (http.begin(client, "http://api.thingspeak.com/apps/thinghttp/send_request?api_key=TC42HK2X3OO1GKNQ"));
      int httpCode = http.GET();
      if (httpCode > 0) 
        {
        
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
        data = http.getString(); 
        data.remove(0,32);
          } 

      http.end();
    }


//////////////////////1uncja srebra/////////////////////
if ((WiFiMulti.run() == WL_CONNECTED)) {

  
    HTTPClient http;

    if (http.begin(client, "http://api.thingspeak.com/apps/thinghttp/send_request?api_key=WT842YQVG7UCZ5GI"));
      int httpCode = http.GET();
      if (httpCode > 0) 
        {
        
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
        uncjasrebro = http.getString(); 
        uncjasrebro.remove(13);
        uncjasrebro.remove(0,6);
          } 

      http.end();
    }
//////////////////////1/2 uncja zlota/////////////////////
if ((WiFiMulti.run() == WL_CONNECTED)) {

  
    HTTPClient http;

    if (http.begin(client, "http://api.thingspeak.com/apps/thinghttp/send_request?api_key=AIPZWUNNIPKC8ESK"));
      int httpCode = http.GET();
      if (httpCode > 0) 
        {
        
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
        uncjazloto = http.getString(); 
        uncjazloto.remove(15);
        uncjazloto.remove(0,6);
          } 

      http.end();
    }
///////////////////////////////////////  
  u8g2.clearBuffer();
  u8g2.drawFrame(0,0,128,64);
///////////////////////////////////
  u8g2.drawStr( 5,57, "EUR");
  u8g2.setCursor(5, 30);
  u8g2.print(Euro);
////////////////////////////////////////
  u8g2.drawStr( 15,57, "USD");
  u8g2.setCursor(15, 30);
  u8g2.print(USD);
/////////////////////////////////////
  u8g2.drawStr( 25,57, "CHF");
  u8g2.setCursor(25, 30);
  u8g2.print(CHF);
  
///////////////////////////////////
  u8g2.drawLine(37, 10, 37, 55);
////////////////////////////////////
  u8g2.drawStr( 41,60, "Gold");
  u8g2.setCursor(41, 25);
  u8g2.print(suma);
 ////////////////////////////////
  u8g2.drawStr( 51,60, "Silver");
   u8g2.setCursor(51, 25);
  u8g2.print(suma2);
/////////////////////////////////
  u8g2.drawLine(63, 10, 63, 55);
 // u8g2.drawStr( 92,57, "Stop%");
 // u8g2.drawStr( 102,57, "Inf.");
  /////////////////////////////////////
 u8g2.drawStr( 67,58, " Brit.1/2oz");
  u8g2.setCursor(77, 57);
  u8g2.print(uncjazloto);
  u8g2.drawStr( 77,16, "zl");


  
  u8g2.drawStr( 90,61, "Bull&Bear1oz");
  u8g2.setCursor(101, 52);
  u8g2.print(uncjasrebro);
  u8g2.drawStr( 101,20, "zl");
  
 u8g2.setCursor(114, 55);
  u8g2.print(data);
 u8g2.sendBuffer();
///////////////////////////////////
  delay(60000);
}
