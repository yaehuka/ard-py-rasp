#define PARSE_AMOUNT 2
#include "Servo.h"
int pos;
Servo myservo;    
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
void setup() {
  Serial.begin(9600);
  myservo.attach(11);
}
void loop() {
  parsing();       
  if (recievedFlag) {                           
    recievedFlag = false;
    while (pos < intData[0]) {
    pos = pos + 1; 
    myservo.write(pos);
    delay(20); 
  }
    /*for (byte i = 0; i < PARSE_AMOUNT; i++) { 
      Serial.print(intData[i]); Serial.print(" ");
    } Serial.println();*/
  }
}
