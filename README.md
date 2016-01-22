Whistle Board
================
The Whistle Board is a an inexpensive and easily assembled kit for controlling your model trains with a microcontroller.

Specifications
--------------
 * Supports HO, N, and Z scales
 * Control up to 3 trains at once
 * Works with your existing transformer
 * Does not require any modifications to trains or track
 * Auxilary outputs for additional accessories
 * 1A per channel
 * Supports both 5V and 3.3V logic

Whistle Board Parts List
------------------------
https://docs.google.com/spreadsheets/d/1KjXTjjhD9g_6WGJ1dTABSkwde-gAP-HaPDzFgPxGlLw/edit#gid=0

Total Cost: $12.30

Whistle Supply Parts List
-------------------------
https://docs.google.com/spreadsheets/d/1KjXTjjhD9g_6WGJ1dTABSkwde-gAP-HaPDzFgPxGlLw/edit#gid=384509371

Total Cost: $13.88
 
Output voltage
--------------
This board can be assembled for different model scales by adjusting the value of R3.  Be sure to select the correct value for your scale or you risk damaging your engines.

*Output Voltage Table*

| Scale | Max Output Voltage | R3       |
|-------|--------------------|----------|
| Z     |  8V                | 1.6k ohm |
| N     | 12V                | 820  ohm |
| HO    | 16V                | 470  ohm |

Using multiple controllers
--------------------------
Up to three Whistle Boards can be connected to one microcontroller.  Connect each Whistle Board back to the same Whistle Supply.  Connect the SDI, SCL from each board in parallel but use distinct microcontroller pins for SS, ENABLE, and DIR.