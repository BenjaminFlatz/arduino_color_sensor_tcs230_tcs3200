# arduino_color_sensor_tcs230_tcs3200


The rgb values and the color string and position gets printed every second.
If you send a string over serial to the Arduino nano you add/set the current color value, the string as name and the binary switch states as position. If you want to add without a name you can use the btnAdd instead.


Hardware:
1.  TCS3200 or TCS230 sensor.
2.  Arduino Nano
3.  Wires
4.  Breadboard or PCB


Schematic:
- TCS3200
  1.  S0---3
  2.  S1---4
  3.  S2---5
  4.  S3---6
  5.  sensorOut---7
  6.  VCC---5V
  7.  GND---GND


- Switches
  1.  sw[0]---8
  2.  sw[1]---9
  3.  sw[2]---10
  4.  sw[3]---11
  5. btnAdd---12
  

  
Functions:
1.  get_freq()
2.  add_color()
3.  set_color()
4.  get_color()
5.	get_pos()
  
