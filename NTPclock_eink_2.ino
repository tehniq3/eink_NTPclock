/* NTP clock on 2.9" e-ink display 
 * original design by niq_ro: https://github.com/tehniq3/ 
 * v.1 - base NTP clock
 * v.2 - rotate info at 90 degree (portrait mode))
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>  // https://github.com/ZinggJM/GxEPD2
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>

// ESP8266 SS=15->D8,SCL(SCK)=14->D5,SDA(MOSI)=13->D7,BUSY=16->D0,RST=5->D1,DC=4->D2
// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

// 2.13'' EPD Module
//GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display(GxEPD2_213_BN(/*CS=5*/ 15, /*DC=*/ 4, /*RST=*/ 5, /*BUSY=*/ 16)); // DEPG0213BN 122x250, SSD1680
//GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT> display(GxEPD2_213_Z98c(/*CS=5*/ 15, /*DC=*/ 4, /*RST=*/ 5, /*BUSY=*/ 16)); // GDEY0213Z98 122x250, SSD1680

// 2.9'' EPD Module
GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> display(GxEPD2_290_BS(/*CS=5*/ 15, /*DC=*/ 4, /*RST=*/ 5, /*BUSY=*/ 16)); // DEPG0290BS 128x296, SSD1680
//GxEPD2_BW<GxEPD2_290_T94_V2, GxEPD2_290_T94_V2::HEIGHT> display(GxEPD2_290_T94_V2(/*CS=5*/ 15, /*DC=*/ 4, /*RST=*/ 5, /*BUSY=*/ 16)); //GDEM029T94  128x296, SSD1680, (FPC-7519 rev.b), Waveshare 2.9" V2 variant
//GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=5*/ 15, /*DC=*/ 4, /*RST=*/ 5, /*BUSY=*/ 16)); // GDEM029C90 128x296, SSD1680

const long timezoneOffset = 2; // ? hours
const char          *ntpServer  = "pool.ntp.org"; // change it to local NTP server if needed
const unsigned long updateDelay = 900000;         // update time every 15 min
const unsigned long retryDelay  = 5000;           // retry 5 sec later if time query failed

unsigned long tpafisare;
unsigned long tpinfo = 60000;  // 15000 for test in video

unsigned long lastUpdatedTime = updateDelay * -1;
unsigned int  second_prev = 0;
bool          colon_switch = false;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer);

byte DST = 1;
byte DST0;
bool updated;
byte a = 0;

int ora = 20;
int minut = 24;
int minut0 = 65;
int secundar = 0;
int zi, zi2, luna, an;
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

byte cnt = 0;

void setup()
{
  display.init(115200,true,50,false);
  
   //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();
    
    //set custom ip for portal
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration

    wifiManager.autoConnect("AutoConnectAP");
      
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");

    delay(500);

timeClient.setTimeOffset((timezoneOffset + DST)*3600);
 timeClient.begin();

   intro();
   delay(3000);

  display.setRotation(2);
}


void loop() {
   if (WiFi.status() == WL_CONNECTED && millis() - lastUpdatedTime >= updateDelay) {
    updated = timeClient.update();
    if (updated) {
      Serial.println("NTP time updated.");
      getYear();
      getMonth();
      getDay();
      zi2 = timeClient.getDay();
      lastUpdatedTime = millis();
    } else {
      Serial.println("Failed to update time. Waiting for retry...");
      lastUpdatedTime = millis() - updateDelay + retryDelay;
    }
  } else {
    if (WiFi.status() != WL_CONNECTED) Serial.println("WiFi disconnected!");
  }
 
unsigned long t = millis();

ora = timeClient.getHours();
minut = timeClient.getMinutes();
secundar = timeClient.getSeconds();

if (minut != minut0)
{   
 ceas();
 minut0 = minut;
}

delay(10000);
// display.hibernate();
}  // end main loop


void ceas()
{
  display.setPartialWindow(0, 0, display.width(), 296); //this sets a window for the partial update, so the values can update without refreshing the entire screen.
  display.firstPage();
   display.setFont(&FreeSans24pt7b);
  //display.setFont(&FreeMonoBold18pt7b);
  display.setTextColor(GxEPD_BLACK);
//  display.setFullWindow();
display.fillScreen(GxEPD_WHITE);
  do
  {
    display.setCursor(5, 50);
    display.print(ora/10);
    display.print(ora%10);
    display.print(":");
    display.print(minut/10);
    display.println(minut%10);
    display.setFont(&FreeMonoBold9pt7b);
    display.print(" ");
    display.print("GMT+3");
    /*
    display.print(":");
    display.print(secundar/10);
    display.print(secundar%10);
    */
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(5, 200);
    display.print(weekDays[zi2]);

  //  display.setFont(&FreeMonoBold18pt7b);
    display.setCursor(5, 220);
    display.print(zi/10);
    display.print(zi%10);
    display.print(".");
    display.print(luna/10);
    display.print(luna%10);
    display.print(".");
    display.print(an); 

    display.setCursor(5, 200);
    display.print(cnt);     
  }
  while (display.nextPage());
}

void intro()
{
  display.setRotation(2);
  display.setFont(&FreeMonoBold9pt7b);
  //display.setFont(&FreeMonoBold18pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 20);
    display.println(" NTP clock ");
    display.println("v.1.0. with");
    display.println(" ESP8266 on");
    display.println("  2.9-inch ");
    display.println("  e-paper  "); 
    display.println("  display  ");   
    display.println(" by niq_ro ");
  }
  while (display.nextPage());
}


 void getYear() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  an = ti->tm_year + 1900;
  Serial.print("year = ");
  Serial.println(an);
}

void getMonth() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  luna = ti->tm_mon + 1;
  Serial.print("month = ");
  Serial.println(luna);
}

void getDay() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  zi = ti->tm_mday;
  Serial.print("day = ");
  Serial.println(zi);
}
