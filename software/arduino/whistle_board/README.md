Whistle Board Arduino Software
==============================
Control a Whistle Board from an Arduino or Arduino compatible by sending and receiving commands serially.

Serial commands
---------------
    ? - This help dialog
    GO index speed - Go at given speed, -100 to 100
    STOP index - Slow to speed 0
    HALT index - Immediate halt

These commands are case insensitive and can be abbreviated down to a single character.  For example: "g 0 100".  Commands are separated by newlines and/or carriage returns.  Each command takes an optional index.  This is the train line number when controlling multiple trains, starting at 0.  If an index is not given, 0 is assumed.

Serial Responses
----------------

When the Arduino is ready, it will send the message "READY".  After that, it will respond to all commands either with "OK: <message>" or "NOT OK: <message>" where the message will usually include the command it is responding to.  In addition to responses, the arduino may respond with additional status information:

    OK: ACCEL index value - The current speed values when accelerating to a requested speed

