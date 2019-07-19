#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9
Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
uint16_t tx, ty;

// Global Variables
float enginetemp;
float oilpressure;
float boostpressure;
float exhuasttemp;
int tempPin = 0; //temp sensor
int oilPin = 1; //oil sensor
int boostPin = 2; //boost sensor
int egtPin = 3; //egt sensor

int tempValue = 0;
int tempPercent = 0;
int oilValue = 0;
int oilPercent = 0;
int boostValue = 0;
int boostPercent = 0;
int egtValue = 0;
int egtPercent = 0;

//int RawValue = 0;
int LastPercent0 = 0; // temp grapgh
int LastPercent1 = 0; // oil graph
int LastPercent2 = 0; //boost graph
int LastPercent3 = 0; //egt graph




void setup() {

  Serial.begin(9600);
  Serial.println("RA8875 start");

  //Initialize the display using 'RA8875_480x80', 'RA8875_480x128', 'RA8875_480x272' or 'RA8875_800x480'
  if (!tft.begin(RA8875_800x480))
  {
    Serial.println("RA8875 Not Found!");
    while (1);
  }

  Serial.println("Found RA8875");

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.textMode();
  
  displayvalue();
}


void displayvalue()
{Serial.begin(9600);
  Serial.println("RA8875 start");

  //Initialize the display using 'RA8875_480x80', 'RA8875_480x128', 'RA8875_480x272' or 'RA8875_800x480'
  if (!tft.begin(RA8875_800x480))
  {
    Serial.println("RA8875 Not Found!");
    while (1);
  }

  Serial.println("Found RA8875");

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.textMode();
  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.textMode();
  tft.textSetCursor(10, 10);
  tft.textColor(RA8875_WHITE, RA8875_BLACK);
  tft.textEnlarge(8);
  tft.textWrite("  Temp   Oil  Boost  EGT");
  char Tempstring[30];
  char Oilstring[30];
  char Booststring[30];
  char Exhuaststring[30];
  dtostrf(enginetemp, 2, 0, Tempstring); //from temp float
  dtostrf(oilpressure, 2, 0, Oilstring); //from oil float
  dtostrf(boostpressure, 2, 0, Booststring); //from boost float
  dtostrf(exhuasttemp, 2, 0, Exhuaststring); // from egt float
  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.textMode();
  tft.textColor(RA8875_CYAN, RA8875_BLACK);
  tft.textEnlarge(2);
  tft.textSetCursor(80, 399);
  tft.textWrite(Tempstring);
  tft.textWrite(" *C");
  tft.textColor(RA8875_YELLOW, RA8875_BLACK);
  tft.textEnlarge(2);
  tft.textSetCursor(270, 399);
  tft.textWrite(Oilstring);
  tft.textWrite(" Psi");
  tft.textEnlarge(2);
  tft.textColor(RA8875_GREEN, RA8875_BLACK);
  tft.textSetCursor(460, 399);
  tft.textWrite(Booststring);
  tft.textWrite(" Psi");
  tft.textEnlarge(2);
  tft.textColor(RA8875_WHITE, RA8875_BLACK);
  tft.textSetCursor(650, 399);
  tft.textWrite(Exhuaststring);
  tft.textWrite(" *C");
}
void drawBartemp (int nPer0) {

  if (nPer0 < LastPercent0) {
    tft.fillRect(110, 50 + (350 - LastPercent0), 100, LastPercent0 - nPer0,  RA8875_BLACK);
  }
  else {
    tft.fillRect(110, 50 + (350 - nPer0), 100, nPer0 - LastPercent0,  RA8875_CYAN);
  }
  LastPercent0 = nPer0;
  


}
void drawBaroil (int nPer1) {

  if (nPer1 < LastPercent1) {
    tft.fillRect(300, 50 + (350 - LastPercent1), 100, LastPercent1 - nPer1,  RA8875_BLACK);
  }
  else {
    tft.fillRect(300, 50 + (350 - nPer1), 100, nPer1 - LastPercent1,  RA8875_YELLOW);
  }
  LastPercent1 = nPer1;
  
}
void drawBarboost (int nPer2) {

  if (nPer2 < LastPercent2) {
    tft.fillRect(490, 50 + (350 - LastPercent2), 100, LastPercent2 - nPer2,  RA8875_BLACK);
  }
  else {
    tft.fillRect(490, 50 + (350 - nPer2), 100, nPer2 - LastPercent2,  RA8875_GREEN);
  }
  LastPercent2 = nPer2;
  
}
void drawBaregt (int nPer3) {

  if (nPer3 < LastPercent3) {
    tft.fillRect(680, 50 + (350 - LastPercent3), 100, LastPercent3 - nPer3,  RA8875_BLACK);
  }
  else {
    tft.fillRect(680, 50 + (350 - nPer3), 100, nPer3 - LastPercent3,  RA8875_WHITE);
  }
  LastPercent3 = nPer3;
  
}
void loop() 

{

  tempValue = analogRead(tempPin);
  tempPercent = int((tempValue / 1024.0) * 310.0);
  if (tempPercent != LastPercent0) {
    drawBartemp(tempPercent);
  }
  {

    oilValue = analogRead(oilPin);
    oilPercent = int((oilValue / 1024.0) * 310.0);
    if (oilPercent != LastPercent1) {
      drawBaroil(oilPercent);
    }
    {

    boostValue = analogRead(boostPin);
    boostPercent = int((boostValue / 1024.0) * 310.0);
    if (boostPercent != LastPercent2) {
      drawBarboost(boostPercent);
    }
    {

    egtValue = analogRead(egtPin);
    egtPercent = int((egtValue / 1024.0) * 310.0);
    if (egtPercent != LastPercent3) {
      drawBaregt(egtPercent);
    }
    {
  enginetemp = analogRead(tempPin);
  enginetemp = (5.0 * enginetemp * 100.0) / 1024.0;
  oilpressure = analogRead(oilPin);
  oilpressure = (5.0 * oilpressure * 100.0) / 1024. / 5.8; //Display 0-70Psi
  boostpressure = analogRead(boostPin);
  boostpressure = (5.0 * boostpressure * 100.0) / 1024. / 14; //Display 0-30Psi
  exhuasttemp = analogRead(egtPin);
  exhuasttemp = (5.0 * exhuasttemp * 100.0) / 1024.*2; //Display 0-800
    }
  }
  }
  }
}
