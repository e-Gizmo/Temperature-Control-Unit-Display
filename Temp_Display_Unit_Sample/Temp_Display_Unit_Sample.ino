/*
  e-Gizmo Temperature Display Unit

  The e-Gizmo temperature control unit display is 
  made for easy and fast measurement circuit 
  temperature sensor, whose output voltage is 
  linearly proportional to the Fahrenheit on its
  LM34 IC sensor then converted / calibrated 
  directly in degrees celcius.

  ===================
  Wiring Connections:
  ===================
  Serial LCD II rev2 ~ GizDuino MCU

      TXD  ------------>   RXD
      RXD  ------------>   TXD
      GND  ------------>   GND

  by e-Gizmo Mechatronix Central
  November 12, 2015
  hhtp://www.e-gizmo.com

*/

void setup(){
  // Initialize serial:
  Serial.begin(9600);
  
  Serial.write(2);
  Serial.print("C272"); //Calibrate command ex. 27.2 deg C "C272"
  Serial.write(3);

  delay(2000);

  Serial.write(2);
  Serial.print("H300"); //Set HIGH trigger for comparator ex. 30.0 deg C "H300"
  Serial.write(3);

  delay(2000);

  Serial.write(2);
  Serial.print("L2500"); //Set LOW trigger for comparator ex. 25.0 deg C "L250"
  Serial.write(3);

  delay(2000);

  Serial.write(2);
  Serial.print("S*"); // Save current settings (to NVRAM) or remember your calibration
  Serial.write(3);

  delay(1000);

}
void loop(){

// Put your codes here

}
