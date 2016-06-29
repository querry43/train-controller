const uint8_t led_pin = 13;
const uint8_t enable_pin = 9;
const uint8_t signal_pin = A0;

const uint16_t threshold = 60;
const uint16_t transition_time = 10;

void setup() {
  _setup_sensor();
}

void loop() {
  _read_sensor();
}

void _setup_sensor() {

  pinMode(enable_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(signal_pin, INPUT_PULLUP);

  digitalWrite(enable_pin, HIGH);
  digitalWrite(led_pin, LOW);
  digitalWrite(signal_pin, HIGH);

  Serial.begin(9600);
}

void _read_sensor() {
  const int16_t r1 = analogRead(signal_pin);

  digitalWrite(enable_pin, LOW);
  delay(transition_time);

  const int16_t r2 = analogRead(signal_pin);

  digitalWrite(enable_pin, HIGH);
  delay(transition_time);

  const int16_t r3 = analogRead(signal_pin);

  digitalWrite(led_pin, max(abs(r1 - r2), abs(r3 - r2)) > threshold);

  //Serial.print(r1); Serial.print("\t"); Serial.print(r2); Serial.print("\t"); Serial.println(r3);
  //delay(1000);
}

