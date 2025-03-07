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
const int dispenser = 2;
const int symbols[10] = {0x02,0x03,0x04,0x05,0x06,0x08,0x0B,0x0C,0x0E,0x0F};

// Init global variables

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
  Serial.begin(115200);
  spiBegin();

  // Init Hardware
  pinMode(dispenser, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  tft.begin();
  tft.fillScreen(tft.BLACK);
  tft.setTextColor(tft.WHITE,tft.BLACK);
  tft.setRotation(3);
  tft.setCursor(0, 0);
  tft.println(F("Setup Complete!"));
  Serial.println(F("Setup Complete!"));
  delay(1000);
  tft.fillScreen(tft.BLACK);
}

void loop() {
  while (digitalRead(3) == HIGH) {}
  displayRandomSymbols();
  dispense(3);

  while (digitalRead(3) == HIGH) {}
  displayRandomSymbols();
  dispense(5);
  
}