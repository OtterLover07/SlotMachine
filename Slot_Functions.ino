void dispense(int amount) {
  for (int i = 0; i < amount; i++) {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
  }
}

void displayRandomSymbols() {
  for (int i = 0; i < 30; i++) {
    tft.setCursor(112, 100);
    tft.setTextSize(15);
    for (int j = 0; j < 3; j++) {
      tft.write(symbols[random(0,9)]);
    }
  }
}