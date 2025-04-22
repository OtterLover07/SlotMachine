///////////////////////////////////////SLOT MACHINE//////////////////////////////////////////
/*
* Name: Slot Machine
* Author: Melker Willforss
* Date: 2025-03-06
* Description: TBA
*/

// Include Libraries
#include <XilkaGFX.h>
#include <XilkaHX8357D.h>
#include <SPI.h>

// Init constants
const int sensitivity = 80;
const int knapp = 3;
const int dispenser = 2;
const int symbols[11] = {0x03,0x03,0x04,0x04,0x05,0x05,0x06,0x06,0x0E,0x0E,0x0F};

// Init global variables
int credits = 0;
int currentReading[2] = {0,0};
int lastReading = 0;

// construct objects

//Setup TFT
typedef Xilka::HX8357D DisplayType;
using namespace Xilka;
const int8_t PIN_RESET(-1);
const int8_t PIN_CS(10);
const int8_t PIN_DC(9);
DisplayType tft(PIN_RESET, PIN_DC, PIN_CS);

void setup() {
  // init communication
  Serial.begin(9600);
  spiBegin();

  // Init Hardware
  pinMode(dispenser, OUTPUT); 
  pinMode(3, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  tft.begin();
  tft.fillScreen(tft.BLACK);
  tft.setTextColor(tft.WHITE,tft.BLACK);
  tft.setRotation(3);
  gamble();
  tft.setCursor(0, 0);
  tft.setTextSize(3);
  tft.println(F("Setup Complete!"));
  Serial.println(F("Setup Complete!"));
  delay(1000);
  tft.fillScreen(tft.BLACK);
  displayCredits();
}

void loop() {
  while (digitalRead(knapp) == HIGH) {
    checkCredits();
  }
  if (credits > 0) {
    credits -= 1;
    displayCredits();
    gamble();
  }
  
}