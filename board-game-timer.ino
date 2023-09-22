//A0 - A5 work as digital pins
const int pin[12] =  {2,3,A0,4,6,5,7,8,9,10,11,12};

const int button_start = A1;
const int button_mode = A2;
const int beeper = 13;

int timerDuration = 60;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 12; i++) {
    pinMode(pin[i], OUTPUT);
  }

  pinMode(button_mode, INPUT);
  pinMode(button_start, INPUT);
  pinMode(beeper, OUTPUT);

  startupAnimation();
}

void loop() {
  if (digitalRead(button_start) == HIGH) {
    beep(50);
    timer(timerDuration);
  }

  if (digitalRead(button_mode) == HIGH) {
    timerDuration += 30;
    if (timerDuration > 12*30) timerDuration = 30;

    showDurationSetting();
  }
}

void timer(float seconds) {
  for (int i = 0; i <= 12; i++) {
    show(i);
    delay(50);
  }

  float t = seconds * 1000;

  for (int i = 0; i < 12; i++) {
    show(12 - i);

    for (int j = 0; j < 100; j++) {
      delay(t / (12 * 100));

      if (digitalRead(button_mode) == HIGH) {
        //end the timer early
        i = 12;
        j = 100;
      }
    }
  }

  show(0);
  beep(400);
  delay(600);
}

void showDurationSetting() {
  for (int i = 0; i < 6; i++) {
    show(timerDuration/30 - 1);
    delay(200);
    show(timerDuration/30);
    delay(200);
    
    if (digitalRead(button_start) == HIGH || digitalRead(button_mode) == HIGH) return;
  }

  show(0);

}

void startupAnimation() {
  int dly = 40;
  for (int i = 0; i <= 12; i++) {
    show(i);
    delay(dly);
  }

  for (int i = 12; i >= 0; i--) {
    show(i);
    delay(dly);
  }
}

//KINGBRIGHT DD-12YWB
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

void beep(int t) {
  digitalWrite(beeper, HIGH);
  delay(t);
  digitalWrite(beeper, LOW);
}