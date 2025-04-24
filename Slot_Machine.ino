///////////////////////////////////////SLOT MACHINE//////////////////////////////////////////
/*
* Name: Slot Machine
* Author: Melker Willforss
* Date: 2025-03-06
* Description:
* This project waits for a token to trigger the sensor at A5, increasing credits. When the user has aquired credits,
* they can then pull a lever wich activates pin 3. This rolls three symbols and checks if the layout is valid for
* any payouts. If so, a corresponding amount of tokens is dispensed using pin 2. Every "spin" also costs 1 credit.
* In addition, the project plays sound through a speaker on pin 6 every time the lever is pulled, in order to help
* the user tell when it's been pulled far enough.
*/

// Include Libraries
#include <XilkaGFX.h>
#include <XilkaHX8357D.h>
#include <SPI.h>

// Init constants
const int sensitivity = 50;
const int knapp = 3;
const int dispenser = 2;
const int symbols[11] = {0x03,0x03,0x04,0x04,0x05,0x05,0x06,0x06,0x0E,0x0E,0x0F};

// Init global variables
int credits = 0;
int currentReading[2] = {0,0};
int lastReading = 0;
int ambientLight = 0;

//Setup TFT
typedef Xilka::HX8357D DisplayType;
using namespace Xilka;
const int8_t PIN_RESET(-1);
const int8_t PIN_CS(10);
const int8_t PIN_DC(9);
DisplayType tft(PIN_RESET, PIN_DC, PIN_CS);

void setup() {
  // init Communication
  Serial.begin(9600);
  spiBegin();

  // Init Hardware
  pinMode(dispenser, OUTPUT); 
  pinMode(3, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  
  // Calibrate Coin Sensor
  int lightSetup = 0;
  for (int i = 0; i < 10; i++) {
    lightSetup += analogRead(A5);
    delay(5);
  }
  ambientLight = lightSetup/10;
  Serial.println(ambientLight + sensitivity);
  delay(600);

  // Setup Screen and Final Touches
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
  tone(6, 500, 200); //plays sound to warn the user that the lever's been pulled all the way
  while (digitalRead(knapp) != HIGH) {
    if (credits > 0) {
    credits -= 1;
    displayCredits();
    gamble();
    } else {
      tone(6, 500); //keep playing the sound if no credits are logged
    }
  }
  noTone(6); 
}