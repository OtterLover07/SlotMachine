void payout(int x) {
  for (int i = 0; i < x; i++) {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
  }
}

void displayRandomSymbols(int x) {
  tft.setTextSize(15);
  for (int i = 0; i < x; i++) {
    tft.setCursor(112, 100);
    for (int j = 0; j < 3; j++) {
      tft.write(symbols[random(0,11)]);
    }
  }
}

void displayCredits() {
  tft.setTextSize(3);
  tft.setCursor(150, 250);
  tft.print("Credits: ");
  tft.print(credits);
  tft.print("        ");
}

void gamble() {
  displayRandomSymbols(30);
  int rolled[3] = {};
  tft.setCursor(112, 100);
  for (int i = 0; i < 3; i++) {
    rolled[i] = symbols[random(0,11)];
    tft.write(rolled[i]);
  }

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

void checkCredits() {
  currentReading[0] = analogRead(A5);
  delay(5);
  currentReading[1] = analogRead(A5);
  int reading = (currentReading[0] + currentReading[1])/2;
  //Serial.println(reading);
  if (reading < (lastReading - sensitivity)) {
    delay(200);
    credits += 1;
    Serial.println("Credit inserted!");
    displayCredits();
  }
  lastReading = reading;
}