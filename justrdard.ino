int message;
const char* package[] = {"code:", "9056", "Brazil", "RiodeJaneiro"};
void setup() {
Serial.begin(9600);}

void loop() {
message = Serial.read();
delay(2000);
int x = sizeof(package)/2;
if (message == 97)
{for(int o = 0; o < x; ++o){
  Serial.println(package[o]);}
  }
else{Serial.println(message);}
}
