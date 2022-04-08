const int ena = 20;
const int dir = 19;
const int pul = 18;
const int interval =9000;   // increase to reduce speed
boolean pulse_state = LOW;
int timespan = 0;
void setup()
{
  pinMode(ena, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(pul, OUTPUT);
  digitalWrite(ena, LOW);
  digitalWrite(dir, HIGH);
  digitalWrite(pul, HIGH);
}

void loop()
{
  for (timespan = 0; timespan <= 133 ; timespan++) {
    dispense();
  }

  delay(3000);  //break btwn dispensation
}

void dispense() {
  pulse_state = !pulse_state;
  digitalWrite(pul, pulse_state);
  delayMicroseconds(interval);
}
