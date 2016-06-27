#include <SPI.h>
#include <McpDigitalPot.h>

const uint8_t maxbuflen = 16;
const int8_t acceleration = 2;

class WhistleBoard {
public:
  WhistleBoard(const uint8_t ss, const uint8_t dir) : _speed(0), _target_speed(0), _dir(dir), _digital_pot(ss, 10000) {
    pinMode(_dir, OUTPUT);
  }

  void set_target_speed(int8_t target_speed) { _target_speed = target_speed; }

  void halt() {
    _speed = 0;
    _target_speed = 0;
    _update_digipot();
  }

  void update() {
    if (_speed > _target_speed) {
      _speed = max(_speed - acceleration, _target_speed);
      _update_digipot();
    } else if (_speed < _target_speed) {
      _speed = min(_speed + acceleration, _target_speed);
      _update_digipot();
    }
  }
 
private:
  int8_t _speed, _target_speed;
  uint8_t _dir;
  McpDigitalPot _digital_pot;

  WhistleBoard();

  void _update_digipot() {
    if (_speed >= 0) digitalWrite(_dir, LOW);
    else             digitalWrite(_dir, HIGH);

    _digital_pot.setResistance(0, map(abs(_speed), 0, 100, 10000, 0));

    Serial.print("SPEED: ");
    Serial.println(_speed);
    delay(100);
  }
};

WhistleBoard wbs[] = {
  WhistleBoard(8, 9),
  WhistleBoard(6, 7),
};

void setup() {
  SPI.begin();

  Serial.begin(9600);
  Serial.println("OK");
}

void loop() {
  char command[maxbuflen];
  if (read_command(command)) {
    run_command(command);
  }

  wbs[0].update();
  wbs[1].update();
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
  uint8_t i = command[1] - '0';
  int32_t v = strtol(command+2, NULL, 10);



  switch (p) {
    case '?':
      Serial.println("G<i><speed> - Go, -100 to 100");
      Serial.println("S<i> - Stop");
      Serial.println("H - Immediate halt");
      break;

    case 's':
      if (i >= 2) {
        Serial.println("NOT OK: Attempt to index > 2");
      } else {
        wbs[i].set_target_speed(0);
        Serial.print("STOP OK: ");
        Serial.println(i);
      }
      break;

    case 'g':
      if (i >= 2) {
        Serial.println("NOT OK: Attempt to index > 2");
      } else {
        wbs[i].set_target_speed(v);
        Serial.print("GO OK: ");
        Serial.print(i);
        Serial.print(" => ");
        Serial.println(v);
      }
      break;

    case 'h':
      wbs[0].halt();
      wbs[1].halt();
      Serial.println("HALT OK");
      break;

    default:
      Serial.print("NOT OK: ");
      Serial.println(p);
      break;
  }
}
