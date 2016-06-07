#include <SPI.h>
#include <McpDigitalPot.h>

const uint8_t ss = 8;
const uint8_t dir = 9;
const uint8_t maxbuflen = 16;
const int8_t acceleration = 2;

McpDigitalPot digitalPot = McpDigitalPot(ss, 10000);

int8_t speed, target_speed;

void setup() {
  pinMode(dir, OUTPUT);
  SPI.begin();

  speed = 0;
  target_speed = 0;

  set_speed(0);

  Serial.begin(9600);
  Serial.println("OK");
}

void loop() {
  char command[maxbuflen];
  if (read_command(command)) {
    run_command(command);
  }

  if (speed > target_speed) {
    speed = max(speed - acceleration, target_speed);
    set_speed(speed);
  } else if (speed < target_speed) {
    speed = min(speed + acceleration, target_speed);
    set_speed(speed);
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
      Serial.println("G<speed> - Go, -100 to 100");
      Serial.println("S - Stop");
      Serial.println("H - Immediate halt");
      break;

    case 's':
      target_speed = 0;
      Serial.println("STOP OK");
      break;

    case 'g':
      target_speed = v;
      Serial.print("GO OK: ");
      Serial.println(v);
      break;

    case 'h':
      target_speed = 0;
      speed = 0;
      Serial.println("HALT OK");
      set_speed(0);
      break;

    default:
      Serial.print("NOT OK: ");
      Serial.println(p);
      break;
  }
}

void set_speed(int8_t s) {
  if (s >= 0) digitalWrite(dir, LOW);
  else        digitalWrite(dir, HIGH);

  digitalPot.setResistance(0, map(abs(s), 0, 100, 10000, 0));

  Serial.print("SPEED: ");
  Serial.println(speed);
  delay(100);
}
