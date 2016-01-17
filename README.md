Train Controller
================
This is a variable speed power supply for model trains of various scales.  It is designed to be inexpensive, easily assembled, and controlled by a microcontroller.  Multiple controllers can be used simultaneously for multi-train layouts.

Controller Parts List
---------------------
 * PCB
 * microcontroller
 * supply board (can be shared between mutliple controllers)
 
 * 3x 1k ohm 1/4 watt resistors
 * 1/4 watt resistor (see output voltage table for value)
 * 1n4148 diode

 * 2x BCD638

 * L272
 * EC2-5NU
 * MCP4131

 * 2x JST Jumper 2 Wire Assembly (https://www.sparkfun.com/products/9914)
 * 2x JST Jumper 3 Wire Assembly (https://www.sparkfun.com/products/9915)
 
Optional Parts
--------------
 * 300 ohm 1/4 watt resistor
 * 3mm yellow led
 * 3x additional JST Jumper 2 Wire Assembly (https://www.sparkfun.com/products/9914)

Supply Parts List
-----------------
 * PCB
 * 5V power supply
 * model train transformer
 
 * 3KBP06 bridge rectifier
 
 * 5mm pitch screw terminal (https://www.sparkfun.com/products/8432)
 * barrel jack (https://www.sparkfun.com/products/119)
 * JST Jumper 2 Wire Assembly (https://www.sparkfun.com/products/9914)

Optional Parts
--------------
 * 10mm red led
 * 10mm green led
 * 4x 270 ohm 1/4 watt resistors
 * 330 owm 1/4 watt resistor
 
Output voltage
--------------
This board can be assembled for different model scales by adjusting the value of R3.  Be sure to select the correct value for your scale or you risk damaging your engines.

*Output Voltage Table*

| Scale | Max Output Voltage | R3       |
|-------|--------------------|----------|
| Z     |  8V                | 1.6k ohm |
| N     | 12V                | 820  ohm |
| HO    | 16V                | 470  ohm |


M(V) and M(I)
-------------
The optional M(V) and M(I) headers are test points for measuring track voltage and current respectively.  When not in use, bridge the solder jumper on M(I).

AUX
---
The optional AUX header outputs V+ and ground for indicators and other devices.  Unlike the V+ in, it is controlled bu the same EN used for enabling track voltage.

Using multiple controllers
--------------------------
It is possible to use multiple controllers from one MC by chaining the boards together.  To do this, connect each controller back to the same supply board.  Connect together the SER pins of each board in parallel but use distinct CTL pins from the microctonroller.