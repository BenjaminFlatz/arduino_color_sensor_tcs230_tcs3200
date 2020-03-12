# arduino_color_sensor_tcs230


The rgb values and the color string gets printed erery second.
If you send a string over serial to the Arduino nano you add/set the current color value, the string as name and the binary switch states as position.

Hardware:
1.  TCS3200 or TCS230 sensor.
2.  Arduino Nano
3.  Wires
4.  Breadboard or PCB
  
Schematic:
1.  S0---3
2.  S1---4
3.  S2---5
4.  S3---6
5.  sensorOut---7
6.  sw[0]---8
7.  sw[1]---9
8.  sw[2]---10
9.  sw[3]---11
  
10.  VCC---5V
11.  GND---GND
  
Functions:
1.  get_freq()
2.  add_color()
3.  set_color()
4.  get_color()
5.	get_pos()
  
