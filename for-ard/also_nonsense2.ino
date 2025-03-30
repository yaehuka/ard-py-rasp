#define PARSE_AMOUNT 2
#include "Servo.h"
int xpos;
int ypos;
Servo servoposx; 
Servo servoposy; 
int intData[PARSE_AMOUNT];     
boolean recievedFlag;
boolean getStarted;
byte index;
String string_convert = "";
void parsing() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();        
    if (getStarted) {                        
      if (incomingByte != ' ' && incomingByte != ';') {  
        string_convert += incomingByte;       
      } else {                                
        intData[index] = string_convert.toInt();  
        string_convert = "";                  
        index++;                              
      }
    }
    if (incomingByte == '$') {                
      getStarted = true;                      
      index = 0;                              
      string_convert = "";                    
    }
    if (incomingByte == ';') {                
      getStarted = false;                     
      recievedFlag = true;                    
    }
  }
}
void servoposxd(){
  while (xpos < intData[0]) {
    xpos = xpos + 1; 
    servoposx.write(xpos);
    delay(20);}
  while(xpos > intData[0]){
    xpos = xpos - 1;
    servoposy.write(xpos);
    delay(20);
  }
}
void servoposyd(){
  while (ypos > intData[1]) {
    ypos = ypos + 1; 
    servoposy.write(ypos);
    delay(20);}
  while(ypos < intData[1]){
    ypos = ypos - 1;
    servoposy.write(ypos);
    delay(20);
  }
}
void setup() {
  Serial.begin(9600);
  servoposx.attach(11);
  servoposy.attach(10);
}
void loop() {
  parsing();       
  if (recievedFlag) {                           
    recievedFlag = false;
    servoposxd();
    servoposyd();
    for (byte i = 0; i < PARSE_AMOUNT; i++) { 
      Serial.print(intData[i]); Serial.print(" ");
    } Serial.println();
  }
}
