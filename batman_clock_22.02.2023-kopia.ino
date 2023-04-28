/////////////biblioteki AutoConnect///////////
#include <ESP8266WiFi.h>          
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>  /////////////////////////dodano
#include <WiFiManager.h>  

/////////////bibliotek1 czasu/////////////////
#include <NTPtimeESP.h>
#define DEBUG_ON
NTPtime NTPch("tempus1.gum.gov.pl");  
strDateTime dateTime;
///////////////////////////////dodano ThingSeeak temperatura legnica/////////////////////
const char* host = "api.thingspeak.com";                             
const int httpPortRead = 80;   
const char* url1 = "/apps/thinghttp/send_request?api_key=X1VR5QS41CL561XG";     
int To_remove;      
String Temp, Data_Raw,Data_Raw_1;  
WiFiClient client;                                                  
HTTPClient http; 
////////////////////////////////////////////////////////////////////////////////////////
/////////////pozostale/////////////////////////////////////////////////////////////////
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
char google[] = "google.com";
//////////////zmienne//////////////////////
int x,y,z,x2,y2,z2,r,g,b;
int zmienna = 11;
String dzien_tygodnia, miesiac;
int val;
int p = 0;
float suma = 0;
bool zmienna1 = true;

/////////////////////////////////////////
Adafruit_NeoPixel strip = Adafruit_NeoPixel(32, D3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(21, D5, NEO_GRB + NEO_KHZ800);
WiFiServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
   Serial.begin(115200);
////////////////EEPROM///////////////  
EEPROM.begin(10); 

   x2 = EEPROM.read(1);
   y2 = EEPROM.read(2);
   z2 = EEPROM.read(3);
   r = EEPROM.read(4);
   g = EEPROM.read(5);
   b = EEPROM.read(6);
   x = EEPROM.read(7);
   y = EEPROM.read(8);
   z = EEPROM.read(9);
   

/////////////////////////////////////
   
  lcd.begin();
  lcd.backlight();
 
  strip.begin();
  strip2.begin();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Wait for");
   lcd.setCursor(1, 0);
  lcd.print("connection ...");    
 // lcd.println(ssid);
  //delay(4000);

   
   WiFiManager wifiManager;
  //reset settings - for testing
 // wifiManager.resetSettings();
//   delay(3000);
  //  ESP.reset();
  wifiManager.setTimeout(30);
  if(!wifiManager.autoConnect("Clock_setting")) {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.println("Failed - timeout :(");
       delay(3000);
    ESP.reset();
    delay(5000);
    } 
    server.begin();
  Serial.println("connecting ok");
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
   lcd.clear();
   lcd.setCursor(1, 0);
   lcd.println("WiFi connected");
   lcd.setCursor(1, 1);
   lcd.println(WiFi.localIP()); 
   
     delay(5000); 
      lcd.clear();
       dateTime = NTPch.getNTPtime(1.0, 1);
    
}


void loop() {
 
if (client.connect(google, 80))
{
///////////////////////////////////////////

   WiFiClient client = server.available();
   client.setTimeout(500); // default is 1000
   String req = client.readStringUntil('\r');
   Serial.println(req);  
/////////////////reconnect/////////////////////////////

if (WiFi.status() != WL_CONNECTED)  {
  WiFi.disconnect();
  delay(3000);
  WiFi.reconnect();
}


if (zmienna1 == true)
  {
     lcd.setCursor(14, 0);
              lcd.print(" ."); 
             zmienna1 = !zmienna1;
    }  
    else
    {
      lcd.setCursor(14, 0);
              lcd.print("  "); 
              zmienna1 = !zmienna1;
      }
   
/*////////////////////RESET//////////////////////

if(req.indexOf(F("RESET/")) != -1)
{ 
   lcd.clear();
   strip.clear();
   lcd.setCursor(5, 0);
   lcd.println("RESET !");
   lcd.setCursor(1, 1);
   lcd.println("Please wait ..."); 
   WiFiManager wifiManager;
   wifiManager.resetSettings();
   delay(300);
    ESP.reset();
 }*/

////////////////////////////////////////////////

 if(req.indexOf(F("godzina/red/")) != -1)
{ 
  int val= req.indexOf(" H");
 String val2 = req.substring(17,val);
 x2 = val2.toInt();
 EEPROM.write(1, x2);
 EEPROM.commit();

 }

   
   if(req.indexOf(F("godzina/green/")) != -1)
{
int val= req.indexOf(" H");
 String val2 = req.substring(19,val);
 y2 = val2.toInt();
 EEPROM.write(2, y2);
 EEPROM.commit();
 }
 
 if(req.indexOf(F("godzina/blue/")) != -1)
{ 
int val= req.indexOf(" H");
 String val2 = req.substring(18,val);
 z2 = val2.toInt();
 EEPROM.write(3, z2);
 EEPROM.commit();
 } 

//////////////////////////////////////////////////
   if(req.indexOf(F("pod/red/")) != -1)
{ 
  int val= req.indexOf(" H");
 String val2 = req.substring(13,val);
 r = val2.toInt();
 EEPROM.write(4, r);
 EEPROM.commit();

 }

   
   if(req.indexOf(F("pod/green/")) != -1)
{
int val= req.indexOf(" H");
 String val2 = req.substring(15,val);
 g = val2.toInt();
 EEPROM.write(5, g);
 EEPROM.commit();
 }
 
 if(req.indexOf(F("pod/blue/")) != -1)
{ 
int val= req.indexOf(" H");
 String val2 = req.substring(14,val);
 b = val2.toInt();
 EEPROM.write(6, b);
 EEPROM.commit();
 } 

//////////////////////////////////////////////////       
 if(req.indexOf(F("minuty/red/")) != -1)
{ 
  int val= req.indexOf(" H");
 String val2 = req.substring(16,val);
 x = val2.toInt();
 EEPROM.write(7, x);
 EEPROM.commit();

 }

   
   if(req.indexOf(F("minuty/green/")) != -1)
{
int val= req.indexOf(" H");
 String val2 = req.substring(18,val);
 y = val2.toInt();
 EEPROM.write(8, y);
 EEPROM.commit();
 }
 
 if(req.indexOf(F("minuty/blue/")) != -1)
{ 
int val= req.indexOf(" H");
 String val2 = req.substring(17,val);
 z = val2.toInt();
 EEPROM.write(9, z);
 EEPROM.commit();
 } 

/////////////////////////////////////////////////////////////////////////////////////////
dateTime = NTPch.getNTPtime(1.0, 1);
  /// warunek odebrania danych
  // NTPch.printDateTime(dateTime);

    byte actualHour = dateTime.hour;
    byte actualMinute = dateTime.minute;
    byte actualsecond = dateTime.second;
    int actualyear = dateTime.year;
    byte actualMonth = dateTime.month;
    byte actualday =dateTime.day;
    byte actualdayofWeek = dateTime.dayofWeek;

   int pierwszy = actualHour / 10;
   int drugi = actualHour % 10;
   int trzeci = actualMinute / 10;
   int czwarty = actualMinute % 10;
    
//////////////////////////////////////////////    
     ///dni tygodnia///
    if (actualdayofWeek == 2)
      dzien_tygodnia = "Poniedzial.";
    if (actualdayofWeek == 3)
      dzien_tygodnia = "Wtorek     ";
    if (actualdayofWeek == 4)
      dzien_tygodnia = "Sroda      ";
    if (actualdayofWeek == 5)
      dzien_tygodnia = "Czwartek   ";
    if (actualdayofWeek == 6)
      dzien_tygodnia = "Piatek     ";
    if (actualdayofWeek == 7)
      dzien_tygodnia = "Sobota     ";
    if (actualdayofWeek == 1)
      dzien_tygodnia = "Niedziela  ";
     if (actualdayofWeek < 1)
      dzien_tygodnia = "Error      ";
      if (actualdayofWeek > 12)
      dzien_tygodnia = "Error      ";  
         ////miesiac////
    if (actualMonth == 1)
      miesiac = " Stycznia    ";
    if (actualMonth == 2)
      miesiac = " Lutego      ";
    if (actualMonth == 3)
      miesiac = " Marca       ";
    if (actualMonth == 4)
      miesiac = " Kwietnia    ";
    if (actualMonth == 5)
      miesiac = " Maja        ";
    if (actualMonth == 6)
      miesiac = " Czerwca     ";
    if (actualMonth == 7)
      miesiac = " Lipca       ";
    if (actualMonth == 8)
      miesiac = " Sierpnia    ";
    if (actualMonth == 9)
      miesiac = " Wrzesnia    ";
    if (actualMonth == 10)
      miesiac = " Pazdziernika";
    if (actualMonth == 11)
      miesiac = " Listopada   ";
    if (actualMonth == 12)
      miesiac = " Grudnia     ";
       if (actualMonth < 1)
      miesiac = "Error        ";
      if (actualMonth > 12)
      miesiac = "Error        ";

 
     
/////////////////////////////////////////////
if (zmienna == 11)
{
zmienna = czwarty;
}
 Serial.println(zmienna);
 
 if (czwarty == zmienna) 
 {
 zmienna = czwarty + 1;
lcd.clear();
 }

if ((actualday/10) == 0)
    {
    lcd.setCursor(1, 0);
    lcd.print(miesiac);
    lcd.setCursor(0, 1);
    lcd.print(dzien_tygodnia);
    lcd.setCursor(0, 0);
    lcd.print(actualday);
    } else
    {
    lcd.setCursor(2, 0);
    lcd.print(miesiac);
    lcd.setCursor(0, 1);
    lcd.print(dzien_tygodnia);
    lcd.setCursor(0, 0);
    lcd.print(actualday);
    }
    ///////////////////AnalogRead//////////////     
/*
while (p<11)
 {
   val = analogRead(A0);
   suma=suma+val;
   p++;
   delay(80);
  }
val=suma/10;
p=0;
suma=0;
*/  
     
     val = analogRead(A0);
     val = map(val, 1, 1050, 1, 99);
     if (val<5)
    {  
   delay(500);
    if (val<5)
    lcd.noBacklight();
    }
    else
    lcd.backlight();
    
    
    
  
   

     //////////////////////AnalogRead part 2/////////////////////////////////////////
     if (val>5)  { 
      strip.setBrightness(val);
      strip2.setBrightness(val+5);  }

      
     else  {

 if (actualHour == 21 | actualHour == 22 | actualHour == 23)
      {
        
      strip.setPixelColor(0, 0,0,0);
      strip.setPixelColor(1, 0,0,0);
      strip.setPixelColor(2, 0,0,0);
      strip.setPixelColor(3, 0,0,0);
      strip.setPixelColor(4, 0,0,0);
      strip.setPixelColor(5, 0,0,0);
      strip.setPixelColor(6, 0,0,0);

      strip.setPixelColor(7, 0,0,0);
      strip.setPixelColor(8, 0,0,0);
      strip.setPixelColor(9, 0,0,0);
      strip.setPixelColor(10, 0,0,0);
      strip.setPixelColor(11, 0,0,0);
      strip.setPixelColor(12, 0,0,0);
      strip.setPixelColor(13, 0,0,0);
      
     strip2.setBrightness(0);  } 
      
     else {
      strip.setPixelColor(0, x,y,z);
      strip.setPixelColor(1, x,y,z);
      strip.setPixelColor(2, x,y,z);
      strip.setPixelColor(3, x,y,z);
      strip.setPixelColor(4, x,y,z);
      strip.setPixelColor(5, x,y,z2);
      strip.setPixelColor(6, x,y,z);

      strip.setPixelColor(7, x,y,z);
      strip.setPixelColor(8, x,y,z);
      strip.setPixelColor(9, x,y,z);
      strip.setPixelColor(10, x,y,z);
      strip.setPixelColor(11, x,y,z);
      strip.setPixelColor(12, x,y,z2);
      strip.setPixelColor(13, x,y,z);
      
      strip2.setBrightness(5);   }       
      
      if (actualHour == 23 | actualHour == 0 | actualHour == 1 | actualHour == 2 ) {
      strip.setBrightness(0);
      strip2.setBrightness(0); } 

     
      else   {
       strip.setBrightness(val);
        strip2.setBrightness(5);  }

          }
    

//////////////////////////////////////////////////////////////////////////////////////////
if( http.begin (client,host,httpPortRead,url1))        //Connect to the host and the url                                      
      {
        int httpCode = http.GET();                //Check feedback if there's a response                                                  
        if (httpCode > 0)                                                              
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {                
              
              Data_Raw = http.getString();   
              Data_Raw_1 = Data_Raw;                                    
              To_remove = Data_Raw_1.indexOf(">");                                                     
              Data_Raw_1.remove(0,To_remove+1);                       
              To_remove = Data_Raw_1.indexOf("°");                                                 
              Data_Raw_1.remove(To_remove,Data_Raw_1.length());                                                               
              Temp=Data_Raw_1;
              int Temp1 = Temp.toInt();
              Serial.print("Temp Legnica: ");
              Serial.println(Temp1);
       ////////////////////////////////
              if (Temp1 >= 0 && Temp1 <=9)  //jedna dodatnia
              {
                 lcd.setCursor(11, 1);
              lcd.print("  ");
                lcd.setCursor(13, 1);
              lcd.print(Temp);   
              }
      ///////////////////////////////////////       
                if (Temp1 >= 10)  //dwie dodatnie
              {
                 lcd.setCursor(11, 1);
              lcd.print(" ");
                lcd.setCursor(12, 1);
              lcd.print(Temp);   
              }
        /////////////////////////////////      
               if (Temp1 <= -1 && Temp1 >= -9)  //jedna ujemna
              {
                 lcd.setCursor(11, 1);
              lcd.print(" ");
                lcd.setCursor(12, 1);
              lcd.print(Temp);   
              }
          ////////////////////////////////    
             if (Temp1 <= -9)  //dwie ujemne
              {
                lcd.setCursor(11, 1);
              lcd.print(Temp);   
              } 
            lcd.setCursor(15, 1);
              lcd.print("C"); 
              lcd.setCursor(14, 1);
              lcd.print(char(39));                
            }
        } 
        http.end();                                                                 
      }    
 //////////////////////////////
 strip.clear();
     strip2.clear();
 if (pierwszy == 1)
    {
      strip.setPixelColor(24, x2,y2,z2);
      strip.setPixelColor(25, x2,y2,z2);
    }
    if (pierwszy == 2)
    {
      strip.setPixelColor(23, x2,y2,z2);
      strip.setPixelColor(24, x2,y2,z2);
      strip.setPixelColor(21, x2,y2,z2);
      strip.setPixelColor(27, x2,y2,z2);
      strip.setPixelColor(26, x2,y2,z2);
    }
   
    if (drugi == 1)
    {
      strip.setPixelColor(17, x2,y2,z2);
      strip.setPixelColor(18, x2,y2,z2);
    }
    if (drugi == 2)
    {
      strip.setPixelColor(16, x2,y2,z2);
      strip.setPixelColor(17, x2,y2,z2);
      strip.setPixelColor(14, x2,y2,z2);
      strip.setPixelColor(20, x2,y2,z2);
      strip.setPixelColor(19, x2,y2,z2);
    }
    if (drugi == 3)
    {
      strip.setPixelColor(16, x2,y2,z2);
      strip.setPixelColor(17, x2,y2,z2);
      strip.setPixelColor(14, x2,y2,z2);
      strip.setPixelColor(18, x2,y2,z2);
      strip.setPixelColor(19, x2,y2,z2);

    }
    if (drugi == 4)
    {
      strip.setPixelColor(15, x2,y2,z2);
      strip.setPixelColor(14, x2,y2,z2);
      strip.setPixelColor(17, x2,y2,z2);
      strip.setPixelColor(18, x2,y2,z2);
    }
    if (drugi == 5)
    {
      strip.setPixelColor(16, x2,y2,z2);
      strip.setPixelColor(15, x2,y2,z2);
      strip.setPixelColor(14, x2,y2,z2);
      strip.setPixelColor(18, x2,y2,z2);
      strip.setPixelColor(19, x2,y2,z2);
    }
    if (drugi == 6)
    {
      strip.setPixelColor(16, x2,y2,z2);
      strip.setPixelColor(15, x2,y2,z2);
      strip.setPixelColor(20, x2,y2,z2);
      strip.setPixelColor(19, x2,y2,z2);
      strip.setPixelColor(18, x2,y2,z2);
      strip.setPixelColor(14, x2,y2,z2);
    }
    if (drugi == 7)
    {
      strip.setPixelColor(16, x2,y2,z2);
      strip.setPixelColor(17, x2,y2,z2);
      strip.setPixelColor(18, x2,y2,z2);
    }
    if (drugi == 8)
    {
      strip.setPixelColor(14, x2,y2,z2);
      strip.setPixelColor(15, x2,y2,z2);
      strip.setPixelColor(16, x2,y2,z2);
      strip.setPixelColor(17, x2,y2,z2);
      strip.setPixelColor(18, x2,y2,z2);
      strip.setPixelColor(19, x2,y2,z2);
      strip.setPixelColor(20, x2,y2,z2);
    }
    if (drugi == 9)
    {
      strip.setPixelColor(14, x2,y2,z2);
      strip.setPixelColor(15, x2,y2,z2);
      strip.setPixelColor(16, x2,y2,z2);
      strip.setPixelColor(17, x2,y2,z2);
      strip.setPixelColor(18, x2,y2,z2);
      strip.setPixelColor(19, x2,y2,z2);
    }
    if (drugi == 0)
    {
      strip.setPixelColor(15, x2,y2,z2);
      strip.setPixelColor(16, x2,y2,z2);
      strip.setPixelColor(17, x2,y2,z2);
      strip.setPixelColor(18, x2,y2,z2);
      strip.setPixelColor(19, x2,y2,z2);
      strip.setPixelColor(20, x2,y2,z2);
    }
 

    if (trzeci == 0)
    {
      strip.setPixelColor(8, x,y,z);
      strip.setPixelColor(9, x,y,z);
      strip.setPixelColor(10, x,y,z);
      strip.setPixelColor(11, x,y,z);
      strip.setPixelColor(12, x,y,z);
      strip.setPixelColor(13, x,y,z);
    }

    if (trzeci == 1)
    {
      strip.setPixelColor(10, x,y,z);
      strip.setPixelColor(11, x,y,z);
    }
    if (trzeci == 2)
    {
      strip.setPixelColor(9, x,y,z);
      strip.setPixelColor(10, x,y,z);
      strip.setPixelColor(7, x,y,z);
      strip.setPixelColor(13, x,y,z);
      strip.setPixelColor(12, x,y,z);
    }
    if (trzeci == 3)
    {
      strip.setPixelColor(9, x,y,z);
      strip.setPixelColor(10, x,y,z);
      strip.setPixelColor(7, x,y,z);
      strip.setPixelColor(11, x,y,z);
      strip.setPixelColor(12, x,y,z);
    }
    if (trzeci == 4)
    {
      strip.setPixelColor(8, x,y,z);
      strip.setPixelColor(7, x,y,z);
      strip.setPixelColor(10, x,y,z);
      strip.setPixelColor(11, x,y,z);
    }
    if (trzeci == 5)
    {
      strip.setPixelColor(9, x,y,z);
      strip.setPixelColor(8, x,y,z);
      strip.setPixelColor(7, x,y,z);
      strip.setPixelColor(11, x,y,z);
      strip.setPixelColor(12, x,y,z);
    }

    
    if (czwarty == 1)
    {
      strip.setPixelColor(3, x,y,z);
      strip.setPixelColor(4, x,y,z);
    }
    if (czwarty == 2)
    {
      strip.setPixelColor(2, x,y,z);
      strip.setPixelColor(3, x,y,z);
      strip.setPixelColor(0, x,y,z);
      strip.setPixelColor(6, x,y,z);
      strip.setPixelColor(5, x,y,z);
    }
    if (czwarty == 3)
    {
     
      strip.setPixelColor(2, x,y,z);
      strip.setPixelColor(3, x,y,z);
      strip.setPixelColor(0, x,y,z);
      strip.setPixelColor(4, x,y,z);
      strip.setPixelColor(5, x,y,z);
     
    }
    if (czwarty == 4)
    {
      strip.setPixelColor(1, x,y,z);
      strip.setPixelColor(0, x,y,z);
      strip.setPixelColor(3, x,y,z);
      strip.setPixelColor(4, x,y,z);
    }
    if (czwarty == 5)
    {
      strip.setPixelColor(2, x,y,z);
      strip.setPixelColor(1, x,y,z);
      strip.setPixelColor(0, x,y,z);
      strip.setPixelColor(4, x,y,z);
      strip.setPixelColor(5, x,y,z);
    }
    if (czwarty == 6)
    {
    
      strip.setPixelColor(2, x,y,z);
      strip.setPixelColor(1, x,y,z);
      strip.setPixelColor(6, x,y,z);
      strip.setPixelColor(5, x,y,z);
      strip.setPixelColor(4, x,y,z);
      strip.setPixelColor(0, x,y,z);
       
    }
    if (czwarty == 7)
    {
      strip.setPixelColor(2, x,y,z);
      strip.setPixelColor(3, x,y,z);
      strip.setPixelColor(4, x,y,z);

    }
    if (czwarty == 8)
    {
      strip.setPixelColor(0, x,y,z);
      strip.setPixelColor(1, x,y,z);
      strip.setPixelColor(2, x,y,z);
      strip.setPixelColor(3, x,y,z);
      strip.setPixelColor(4, x,y,z);
      strip.setPixelColor(5, x,y,z);
      strip.setPixelColor(6, x,y,z);
    }
    if (czwarty == 9)
    {
      strip.setPixelColor(0, x,y,z);
      strip.setPixelColor(1, x,y,z);
      strip.setPixelColor(2, x,y,z);
      strip.setPixelColor(3, x,y,z);
      strip.setPixelColor(4, x,y,z);
      strip.setPixelColor(5, x,y,z);
    }
    if (czwarty == 0)
    {
     
      strip.setPixelColor(1, x,y,z);
      strip.setPixelColor(2, x,y,z);
      strip.setPixelColor(3, x,y,z);
      strip.setPixelColor(4, x,y,z);
      strip.setPixelColor(5, x,y,z);
      strip.setPixelColor(6, x,y,z);
   
    }
    
    
      strip2.setPixelColor(0, r, g, b);
     strip2.setPixelColor(1, r, g, b);
     strip2.setPixelColor(2, r, g, b);
     strip2.setPixelColor(3, r, g, b);
     strip2.setPixelColor(4, r, g, b);
     strip2.setPixelColor(5, r, g, b);
     strip2.setPixelColor(6, r, g, b);
     strip2.setPixelColor(7, r, g, b);
     strip2.setPixelColor(8, r, g, b);
     strip2.setPixelColor(9, r, g, b);
     strip2.setPixelColor(10, r, g, b);
     strip2.setPixelColor(11, r, g, b);
     strip2.setPixelColor(12, r, g, b);
     strip2.setPixelColor(13, r, g, b);
     strip2.setPixelColor(14, r, g, b);
     strip2.setPixelColor(15, r, g, b);
     strip2.setPixelColor(16, r, g, b);
     strip2.setPixelColor(17, r, g, b);
     strip2.setPixelColor(18, r, g, b);
     strip2.setPixelColor(19, r, g, b);
     strip2.setPixelColor(20, r, g, b);
     strip2.setPixelColor(21, r, g, b);
     
/////////////////////////////////////////

strip.show();
    strip2.show();
  

 delay(500);
    
 }
 else
 {
  strip.clear();
  lcd.clear();
   lcd.setCursor(1, 0);
   lcd.println("Brak");
    lcd.setCursor(1, 1);
   lcd.println("internetu");
   
     val = analogRead(A0);
     val = map(val, 1, 1050, 1, 99);
     if (val<5)
    {  
   delay(500);
    if (val<5)
    lcd.noBacklight();
    }
    
    else
    lcd.backlight();
     if (val>5)
     {

     strip.setBrightness(val);
     strip2.setBrightness(val+5);
     }


  
  if (zmienna1 == true)
  {
     strip.setPixelColor(5, 255,0,0);
     strip.setPixelColor(12, 255,0,0);
     strip.setPixelColor(19, 255,0,0);
     strip.setPixelColor(26, 255,0,0);
             zmienna1 = !zmienna1;
    }  
    else
    {
      
strip.clear();
              zmienna1 = !zmienna1;
      }
      strip.show();
      strip2.show();
  }}
 
