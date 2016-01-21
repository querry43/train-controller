Train Controller
================
This is a variable speed controller for model trains of various scales.  It is designed to be inexpensive, easily assembled, and controlled by a microcontroller.

Specifications
--------------
 * Supports HO, N, and Z scales
 * Control up to 3 trains at once
 * Works with your existing transformer
 * Auxilary outputs for additional accessories
 * 1A per channel
 * Supports both 5V and 3.3V logic

Controller Parts List
---------------------
https://docs.google.com/spreadsheets/d/1KjXTjjhD9g_6WGJ1dTABSkwde-gAP-HaPDzFgPxGlLw/edit#gid=0

Total: $15.10

Supply Parts List
-----------------
https://docs.google.com/spreadsheets/d/1BliDvUq5zB4kFqZqiHKTbAABE47wwhIGIc2BcT_Ae6E/edit#gid=0

Total: $14.94
 
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
It is possible to use multiple controllers from one MC by chaining the boards together.  To do this, connect each controller back to the same supply board.  Connect together the SER pins of each board in parallel but use distinct CTL pins from the microctonroller.