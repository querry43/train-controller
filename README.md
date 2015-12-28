Train Controller
================

This is a variable speed power supply for model trains of various scales.  It is designed to be inexpensive, easily assembled, and controlled by a microcontroller.  Multiple controllers can be used simultaneously for multi-train layouts.

Parts List
----------
 * 1x PCB
 * 1x DC power supply (see output voltage table for value)

 * 3x 1k ohm 1/4 watt resistors
 * 1x 300 ohm 1/4 watt resistor
 * 1x 1/4 resistor (see output voltage table for value)

 * 1x 3mm yellow led (optional)

 * 1x BCD638
 * 1x 2n2222

 * 1x L272
 * 1x EC2-5NU
 * 1x MCP4131

 * 5x JST Jumper 2 Wire Assembly (https://www.sparkfun.com/products/9914)
 * 2x JST Jumper 3 Wire Assembly (https://www.sparkfun.com/products/9915)

Input and output voltage
------------------------
This board can be run on several different voltages and can be adapted for different model scales.  The value of R3 along with the V+ value set the maximum output voltage.  Be sure to set it correctly or you risk damaging your engines.

*Output Voltage Table*

| Input Voltage | Scale | Max Output Voltage | R3       |
|---------------|-------|--------------------|----------|
| 10V or higher | Z     |  8V                | 1.6k ohm |
| 16V or higher | N     | 12V                | 820  ohm |
| 18V or higher | HO    | 16V                | 470  ohm |


M(V) and M(I)
-------------
The M(V) and M(I) are for measuring track voltage and current respectively.  When not in use, bridge the solder jumper on M(I).

AUX
---
The AUX header outputs V+ and ground for indicators.  Unlike the V+ in, it is controlled bu the same EN used for enabling track voltage.

Using multiple controllers
--------------------------
It is possible to use multiple controllers from one MC by chaining the boards together.  To do this, connect the SER and POW pins of each board in parallel but use distinct CTL pins.
