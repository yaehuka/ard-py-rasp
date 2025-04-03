#define LED_PIN 4
#define BRIGHT_PIN 5
#define SERVO1_PIN 18
#define SERVO2_PIN 19
#define BUTTON_PIN 17
#define LED_NUM 256

#include "FastLED.h"
#include "ESP32Servo.h"
#include "HTTPClient.h"
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;
char incomingPacket[255];
const char* ssid = "shokoladnye_myachiki";
const char* password = "Gndtv63b";
int countt;
int brightt = 0;
Servo servo1;
Servo servo2;
CRGB leds[LED_NUM];

void setup() {
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(255);
  pinMode(BRIGHT_PIN, INPUT);
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  Serial.println("\nConnecting to WiFi Network ..");
 
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
    }
  Serial.println("\nConnected to the WiFi network");
   // Отправка HTTP GET запроса
  
}
byte counter;
void loop() {
  int bright = digitalRead(BRIGHT_PIN);
  int button = digitalRead(BUTTON_PIN);

  FastLED.clear();

  if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Укажите URL вашего сервера
      http.begin(""); // Замените на ваш URL
      int httpResponseCode = http.GET();

        // Проверка кода ответа
      if (httpResponseCode > 0) {
          String response = http.getString();
          Serial.println(httpResponseCode); // Код ответа
          Serial.println(response);
          servo1.write(90);
          servo2.write(90);
           // Ответ сервера
        } else {
          Serial.print("Ошибка при отправке запроса: ");
          Serial.println(httpResponseCode);
        }
        
      http.end(); // Завершить соединение
  }
    if(bright == 1)
  {
    servo1.write(180);

    for (int i = 16; i < 80; i++) {
    if((4<(i+3)*3%16) and ((i+3)*3%16<11)){
    leds[i].setHue(counter/i*32);}
  }
  for (int i = 80; i < 176; i++) {
    leds[i].setHue(counter/i*32);
  }
  for (int j = 176; j < 240; j++) {
    if((4<(j+3)*3%16) and ((j+3)*3%16<11)){
    leds[j].setHue(counter/j*32);}
  }
  }
  if (button == 1)
  {
        servo1.write(0);
  for (int i = 16; i < 80; i++) {
    if((4>i%16) and (i%16>11)){
    leds[i].setHue(counter/i*12);}
  }
  for (int i = 80; i < 176; i++) {
    if((4<i%16) and (i%16<11)){
    leds[i].setHue(counter/i*32);}
  }
  for (int j = 176; j < 240; j++) {
    if((4>j%16) and (j%16>11)){
    leds[j].setHue(counter/j*32);}
  }
  }
  counter++;
  FastLED.show();      // counter меняется от 0 до 255 (тип данных byte)
       // скорость движения радуги
}
