
// Data lines Y0–Y3 to A0–A3
const int dataPins[4] = {A0, A1, A2, A3};
const int addrPins[8] = {D2, D3, D4, D5, D6, D7, D8, D9};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) pinMode(addrPins[i], OUTPUT);

  for (int i = 0; i < 4; i++) pinMode(dataPins[i], INPUT);
}

void loop() {
  delay(1000);
  for (int addr = 0; addr < 255; addr++) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(addrPins[i], (addr >> i) & 1);
    }

    delay(10);

    byte first = 0;
    for (int i = 0; i < 4; i++) {
      if (digitalRead(dataPins[i])) {
        first |= (1 << i);
      }
    }

    addr++;

    for (int i = 0; i < 8; i++) {
      digitalWrite(addrPins[i], (addr >> i) & 1);
    }

    byte second = 0;
    for (int i = 0; i < 4; i++) {
      if (digitalRead(dataPins[i])) {
        second |= (1 << i);
      }
    }

    byte combined = (first << 4) | second;

    Serial.write(combined);
  }
  delay(60000);
}
