/* 
e-Gizmo Temperature Display Unit kit Arduino Demo 

Connections:
TDU to gizDuino board
TX  =  D0/RX
RX  =  D1/TX
GND =  GND

VIN =  7-9VDC /VIN

Codes by
e-Gizmo Mechatronix Central
http://www.e-gizmo.com
August 10, 2017

Modified by Amoree
08/10/17


*/

// defines used by the serial event
// do not modify
#define  STX 2
#define  ETX 3
#define  SERIALSTX 0
#define  SERIALETX 1
#define  SERIALRDY 2

// Temperature read results
 String  temp_value;      // data streaming
 
byte  serial_state;
String serialinput;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  Serial.println("e-Gizmo Temperature Reader Demo");
  delay(1000);
  Serial.println("\002v0\003");
  delay(500);
  serial_state=SERIALSTX;
  serialinput="";
  check_temperature();
  
}

void loop() {

 if(check_temperature()==true){
    
    /* Replace the following demo codes with your own
    */
    // Print the read data
    Serial.print("Temperature:");
    Serial.println(temp_value);
  }

}


/* Do not modify anything in the following codes unless
  you absolutely know what you are doing :-) */
  
boolean check_temperature(void){

  int  strindex;
  int  strindexe;
  
      // Read if temperature data is available
     if(serial_state==SERIALRDY){
       
      //extract data stream portion
      strindex=strindexe+1;
      strindexe=serialinput.indexOf(",",strindex);
      temp_value=serialinput.substring(strindex,strindexe);
      
      // clear received string and ready SERIAL for new stream
     serialinput="";
     serial_state=SERIALSTX;
     return(true);
   }
   return(false);  // return false if temperature data is not available
}


/* This is a interrupt driven serial Rx routine */

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    
    // Wait for the STX character
    if(serial_state==SERIALSTX){
      if(inChar==STX){
        serial_state=SERIALETX;    // STX character detected, enable next phase
        return;
        }
    }
    
    // Store rx character to serial input until ETX is detected
    if(serial_state==SERIALETX){
      if(inChar!=ETX){
        serialinput += inChar;
        return;
        }
    }
    
      // Indicate serial data is ready after ETX is detected
      serial_state=SERIALRDY;
    }
  }


