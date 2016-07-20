#include <SPI.h>
#include <McpDigitalPot.h>

const uint8_t maxbuflen = 16;
const int8_t acceleration = 2;

class WhistleBoard {
public:
  WhistleBoard(const uint8_t ss, const uint8_t dir, const uint8_t index) : _speed(0), _target_speed(0), _dir(dir), _index(index), _digital_pot(ss, 10000) {
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
  uint8_t _dir, _index;
  McpDigitalPot _digital_pot;

  WhistleBoard();

  void _update_digipot() {
    if (_speed >= 0) digitalWrite(_dir, LOW);
    else             digitalWrite(_dir, HIGH);

    _digital_pot.setResistance(0, map(abs(_speed), 0, 100, 10000, 0));

    Serial.print("OK: ACCEL ");
    Serial.print(_index);
    Serial.print(" ");
    Serial.println(_speed);
    delay(100);
  }
};

WhistleBoard wbs[] = {
  WhistleBoard(8, 9, 0),
  WhistleBoard(6, 7, 1),
};

void setup() {
  SPI.begin();

  Serial.begin(9600);
  Serial.println("READY");
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

void run_command(char* line) {

  char command_str[maxbuflen],
    tok1_str[maxbuflen],
    tok2_str[maxbuflen];

  strncpy(command_str, strtok(line, " "), maxbuflen-1);
  strncpy(tok1_str, strtok(NULL, " "), maxbuflen-1);
  strncpy(tok2_str, strtok(NULL, " "), maxbuflen-1);

  char command_chr = tolower(command_str[0]);
  int32_t tok1_int = strtol(tok1_str, NULL, 10);
  int32_t tok2_int = strtol(tok2_str, NULL, 10);

  Serial.print("COMMAND: ");
  Serial.print(command_str);
  Serial.print(", TOK1: ");
  Serial.print(tok1_str);
  Serial.print(", TOK2: ");
  Serial.println(tok2_str);

  switch (command_chr) {
    case '?':
      Serial.println("? - This help dialog");
      Serial.println("GO index speed - Go at given speed, -100 to 100");
      Serial.println("STOP index - Slow to 0 speed");
      Serial.println("HALT index - Immediate halt");
      Serial.println();
      Serial.println("Commands are case insensitive and can be abbreviated to single characters");
      Serial.println("In all commands, index is optional and defaults to 0");
      break;

    case 'g':
      // 0 parameters
      if (strlen(tok1_str) == 0) {
        Serial.println("NOT OK: GO Missing parameters");
        break;
      // 1 parameter
      } else if (strlen(tok2_str) == 0) {
        tok2_int = tok1_int;
        tok1_int = 0;
      }

      if (tok1_int < 0 || tok1_int >= 2) {
        Serial.println("NOT OK: GO Index out of range");
      } else if (tok2_int < -100 || tok2_int > 100) {
        Serial.println("NOT OK: GO Value out of range");
      } else {
        wbs[tok1_int].set_target_speed(tok2_int);
        Serial.print("OK: GO ");
        Serial.print(tok1_int);
        Serial.print(" ");
        Serial.println(tok2_int);
      }

      break;

    case 's':
      // 0 parameters
      if (strlen(tok1_str) == 0)
        tok1_int = 0;

      if (tok1_int < 0 || tok1_int >= 2) {
        Serial.println("NOT OK: STOP Index out of range");
      } else {
        wbs[tok1_int].set_target_speed(0);
        Serial.print("OK: STOP ");
        Serial.println(tok1_int);
      }
      break;

    case 'h':
      // 0 parameters
      if (strlen(tok1_str) == 0)
        tok1_int = 0;

      if (tok1_int < 0 || tok1_int >= 2) {
        Serial.println("NOT OK: HALT Index out of range");
      } else {
        wbs[tok1_int].halt();
        Serial.print("OK: HALT ");
        Serial.println(tok1_int);
      }
      break;

    default:
      Serial.print("NOT OK: Unknown command: ");
      Serial.println(command_str);
      break;
  }
}
