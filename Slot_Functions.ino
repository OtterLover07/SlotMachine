/*
* This function dispenses an amount of coins from the coin mechanism.
* Parameters: x - The amount of coins that sould be dispensed (int)
* Returns: Void
*/
void payout(int x) {
  for (int i = 0; i < x; i++) {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
  }
}

/*
* This function rolls three random symbols from [symbols] and displays them on the screen. This is done an amount of times.
* Parameters: x - The amount of times the function should be executed (int)
* Returns: Void
*/
void displayRandomSymbols(int x) {
  tft.setTextSize(15);
  for (int i = 0; i < x; i++) {
    tft.setCursor(112, 100);
    for (int j = 0; j < 3; j++) {
      tft.write(symbols[random(0,11)]);
    }
  }
}

/*
* This function writes how many credits the user has to the TFT display.
* Parameters: Void
* Returns: Void
*/
void displayCredits() {
  tft.setTextSize(3);
  tft.setCursor(150, 250);
  tft.print("Credits: ");
  tft.print(credits);
  tft.print("        ");
}

/*
* This function is responsible for the gambling process. First it randomly shows a few symbols to tease the user.
* It then rolls three random symbols and stores their values along with displaying them to the user. It then checks
* the rolled symbols. If the rolled set of symbols is eligible for a payout, the corresponding payout is then given.
* Parameters: Void
* Returns: Void
*/
void gamble() {
  displayRandomSymbols(30);
  int rolled[3] = {};
  tft.setCursor(112, 100);
  for (int i = 0; i < 3; i++) {
    rolled[i] = symbols[random(0,11)];
    tft.write(rolled[i]);
  }

  // Check if the rolled symbols should give a payout, and do if so.
  if (rolled[0] == rolled[1] && rolled[0] == rolled[2] && rolled[0] == 0x0F) {
    payout(10);
    Serial.println("Jackpot! (15)");
  } else if (rolled[0] == rolled[1] && rolled[0] == rolled[2] && rolled[0] == 0x0E) {
    payout(5);
    Serial.println("Note Triples (5)");
  } else if (rolled[0] == rolled[1] && rolled[0] == rolled[2]) {
    payout(3);
    Serial.println("Triples (3)");
  } else if ((rolled[0] == rolled[1] && rolled[0] == 0x0F) || (rolled[0] == rolled[2] && rolled[0] == 0x0F) || (rolled[1] == rolled[2] && rolled[1] == 0x0F)) {
    Serial.println("Eye Doubles (No Payout)");
  } else if ((rolled[0] == rolled[1] && rolled[0] == 0x0E) || (rolled[0] == rolled[2] && rolled[0] == 0x0E) || (rolled[1] == rolled[2] && rolled[1] == 0x0E)) {
    Serial.println("Note Doubles (No Payout)");
  } else if ((rolled[0] == rolled[1]) || (rolled[0] == rolled[2]) || (rolled[1] == rolled[2])) {
    payout(2);
    Serial.println("Suit Doubles (2)");
  } else {
    Serial.println("No Payout");
  }
}

/*
* This function checks the coin sensor. If a coin has been inserted it then increments the credits variable by 1.
* Parameters: Void
* Returns: Void
*/
void checkCredits() {
  currentReading[0] = analogRead(A5);
  delay(5);
  currentReading[1] = analogRead(A5);
  int reading = (currentReading[0] + currentReading[1])/2;
  if (reading < (lastReading - 5) || reading > (lastReading + 5)) {
    Serial.println(reading);
  }
  if (reading > (ambientLight + sensitivity)) {
    delay(200);
    credits += 1;
    Serial.println("Credit inserted!");
    displayCredits();
  }
  lastReading = reading;
  }