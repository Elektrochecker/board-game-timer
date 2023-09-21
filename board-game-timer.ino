//A0 - A5 work as digital pins
const int pin[12] =  {2,3,13,4,6,5,7,8,9,10,11,12};

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 12; i++) {
    pinMode(pin[i], OUTPUT);
  }

  startupAnimation();
}

void loop() {
  wait(60);
  delay(1000);
}

void wait(float secs) {
  float t = secs * 1000;

  for (int i = 0; i < 12; i++) {
    show(12 - i);
    delay(t / 12);
  }
}

void startupAnimation() {
  for (int i = 0; i <= 12; i++) {
    show(i);
    delay(50);
  }

  for (int i = 12; i >= 0; i--) {
    show(i);
    delay(50);
  }
}
//RBG1200_YBG1200#KIN
//verbundene LED segmente:
//2-3, 5-6, 7-8, 10-11
void show(int p) {
  if (p > 12) p = 12;
  if (p < 0)  p = 0;

  int state[12] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

  for (int i = 0; i < p; i++) {
    state[i] = HIGH;
  }

  if (p > 2)  state [1] = LOW;
  if (p > 5)  state [4] = LOW;
  if (p > 7)  state [6] = LOW;
  if (p > 10) state [9] = LOW;

  for (int i = 0; i < 12; i++) {
    digitalWrite(pin[i], state[i]);
  }
}