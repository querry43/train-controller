#include <SPI.h>
#include <McpDigitalPot.h>

const uint8_t en = 8;
const uint8_t dir = 9;
const uint8_t maxbuflen = 16;

McpDigitalPot digitalPot = McpDigitalPot(10, 10000);

int8_t speed, target_speed;

void setup() {
  pinMode(en, OUTPUT);
  pinMode(dir, OUTPUT);
  SPI.begin();

  disable();
  speed = 0;
  target_speed = 0;

  Serial.begin(9600);
  Serial.println("OK");
}

void loop() {
  char command[maxbuflen];
  if (read_command(command)) {
    run_command(command);
  }

  if (speed > target_speed) {
    set_speed(--speed);
    Serial.println(speed);
  } else if (speed < target_speed) {
    set_speed(++speed);
    Serial.println(speed);
  }
}

bool read_command(char* command) {
  static char buf[maxbuflen];
  static uint8_t buflen = 0;

  if (Serial.available()) {
    char byte = Serial.read();

    // newline
    if (byte == '\n' || byte == '\r') {
      if (buflen > 0) {
        buf[buflen] = 0;
        strncpy(command, buf, buflen+1);
        buflen = 0;
        return true;
      } else {
        return false;
      }

    // overflow
    } else if (buflen == maxbuflen-1) {
      buflen = 0;

    // chars
    } else {
      buf[buflen++] = byte;
    }

    return false;
  }
}

void run_command(char* command) {
  char p = tolower(command[0]);
  int32_t v = strtol(command+1, NULL, 10);

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
      target_speed = 0;
      Serial.println("STOP OK");
      break;

    case 'f':
      target_speed = v;
      Serial.print("FORWARD OK: ");
      Serial.println(v);
      break;

    case 'r':
      target_speed = v * -1;
      Serial.print("REVERSE OK: ");
      Serial.println(v);
      break;

    default:
      Serial.print("NOT OK: ");
      Serial.println(p);
      break;
  }
}

void enable() { digitalWrite(en, LOW); speed = 0; target_speed = 0; }
void disable() { digitalWrite(en, HIGH); speed = 0; target_speed = 0; }
void set_speed(int8_t s) {
  if (s >= 0) digitalWrite(dir, LOW);
  else        digitalWrite(dir, HIGH);

  digitalPot.setResistance(0, map(abs(s), 0, 100, 10000, 0));
  delay(100);
}
