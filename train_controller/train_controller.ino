#include <SPI.h>
#include <McpDigitalPot.h>

const uint8_t en = 8;
const uint8_t dir = 9;
const uint8_t buflen = 16;

McpDigitalPot digitalPot = McpDigitalPot(10, 10000);

void setup() {
  pinMode(en, OUTPUT);
  pinMode(dir, OUTPUT);
  SPI.begin();

  Serial.begin(9600);
  Serial.println("OK");
}

void loop() {
  char buf[buflen];

  uint8_t bytes = Serial.readBytesUntil('\n', buf, buflen);

  if (bytes > 0) {
    buf[bytes] = 0;

    char p = tolower(buf[0]);
    uint32_t v = strtol(buf+1, NULL, 10);

    switch (p) {
      case '?':
        Serial.println("E - Enable");
        Serial.println("D - Disable");
        Serial.println("S - Stop");
        Serial.println("F<speed> - Forward");
        Serial.println("R<speed> - Reverse");
        break;

      case 'e':
        enable();
        Serial.println("ENABLE OK");
        break;

      case 'd':
        disable();
        Serial.println("DISABLE OK");
        break;

      case 's':
        speed(0);
        Serial.println("STOP OK");
        break;

      case 'f':
        enable();
        forward();
        speed(v);
        Serial.print("FORWARD OK: ");
        Serial.println(v);
        break;

      case 'r':
        enable();
        reverse();
        speed(v);
        Serial.print("REVERSE OK: ");
        Serial.println(v);
        break;

      default:
        Serial.print("NOT OK: ");
        Serial.println(p);
        break;
    }
  }
}

void enable() { digitalWrite(en, LOW); }
void disable() { digitalWrite(en, HIGH); }
void speed(uint8_t s) { digitalPot.setResistance(0, map(s, 0, 100, 0, 10000)); }
void forward() { digitalWrite(dir, LOW); }
void reverse() { digitalWrite(dir, HIGH); }
