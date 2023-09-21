//A0 - A5 work as digital pins
int pins[12] =  {2,3,13,4,6,5,7,8,9,10,11,12};

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 12; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i <= 12; i++) {
    show(i);
    delay(100);
  }

  for (int i = 12; i >= 0; i--) {
    show(i);
    delay(100);
  }
}

//verbundene LED segmente:
//2-3, 5-6, 7-8, 10-11
void show(int p) {
  if (p > 12) p = 12;
  if (p < 0)  p = 0;

  int led[12] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

  for (int i = 0; i < p; i++) {
    led[i] = HIGH;
  }

  if (p > 2)  led [1] = LOW;
  if (p > 5)  led [4] = LOW;
  if (p > 7)  led [6] = LOW;
  if (p > 10) led [9] = LOW;

  for (int i = 0; i < 12; i++) {
    digitalWrite(pins[i], led[i]);
  }
}