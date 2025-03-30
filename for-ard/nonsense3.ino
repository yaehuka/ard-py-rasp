int message; 
void setup() {
Serial.begin(9600);

}

void loop() {
message = Serial.read();
if (message == 97){Serial.println("Hello");}
else{Serial.println("Bye Bye");}

}
