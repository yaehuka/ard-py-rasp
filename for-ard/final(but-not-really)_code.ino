//пропись требуемых библиотек, переменных для кода
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

char incomingPacket[255];

const char* ssid = "shokoladnye_myachiki";
const char* password = "Gndtv63b";
WiFiUDP Udp;

int countt;
int brightt = 0;

Servo servo1;
Servo servo2;

CRGB leds[LED_NUM];


void setup() {
  //присваивание портов для моторов, датчиков, матрицы, wifi
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
  //подключение к wifi сети shokoladnye_myachiki

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
    http.begin("");
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode); // Код ответа
      Serial.println(response);
      if (response.length() == 2){
        //при сигнале посадки две сервы прокручиваются, открывая крышку. после чего включаетсая индикация на лед-матрице.
        servo1.write(120);
        servo2.write(120);
        for (int i = 16; i < 80; i++) {
          if((3<(i+1)*2%16) and ((i+1)*2%16<12)){
            leds[i].setHue(counter/i*16);}
        }
        for (int i = 80; i < 176; i++) {
          leds[i].setHue(counter/i*16);
        }
        for (int j = 176; j < 240; j++) {
          if((3<(j+1)*2%16) and ((j+1)*2%16<12)){
            leds[j].setHue(counter/j*16);}
        }
      }
      if (response.length() == 1){
        //при сигнале нахождения в дронпорте две сервы прокручиваются, закрывая крышку. после чего включаетсая индикация на лед-матрице.
        FastLED.clean();

        servo1.write(0);
        servo2.write(0);

        for (int i = 16; i < 80; i++) {
          if((6<(i+5)*3%16) and ((i+5)*3%16<9)){
            leds[i].setHue(counter/i*144);}
        }
        for (int i = 80; i < 176; i++) {
          leds[i].setHue(counter/i*144);
        }
        for (int j = 176; j < 240; j++) {
          if((6<(j+5)*3%16) and ((j+5)*3%16<9)){
            leds[j].setHue(counter/j*144);}
        }

        FastLED.show();
      }
      if else (response.length() == 2){
        //при сигнале нахождения в дронпорте две сервы прокручиваются, закрывая крышку. после чего включаетсая индикация на лед-матрице.
        FastLED.clean();

        servo1.write(0);
        servo2.write(0);

        for (int i = 16; i < 80; i++) {
          if((6<(i+5)*3%16) and ((i+5)*3%16<9)){
            leds[i].setHue(counter/i*144);}
        }
        for (int i = 80; i < 176; i++) {
          leds[i].setHue(counter/i*144);
        }
        for (int j = 176; j < 240; j++) {
          if((6<(j+5)*3%16) and ((j+5)*3%16<19)){
            leds[j].setHue(counter/j*144);}
        }

        FastLED.show(); 
      }
      if else (response.length() == 3)
      {
        //при сигнале взлета в дронпорте две сервы прокручиваются, открывая крышку. после чего включаетсая индикация на лед-матрице.
        FastLED.clean();

        servo1.write(120);
        servo2.write(120);

        for (int i = 16; i < 80; i++) {
          if((6<(i+5)*3%16) and ((i+5)*3%16<9)){
            leds[i].setHue(counter/i*170);}
        }
        for (int i = 80; i < 176; i++) {
          leds[i].setHue(counter/i*170);
        }
        for (int j = 176; j < 240; j++) {
          if((6<(j+5)*3%16) and ((j+5)*3%16<19)){
            leds[j].setHue(counter/j*170);}
        }

        FastLED.show(); 
      }
      if else (response.length() == 4){
          //при сигнале нахождения в дронпорте две сервы прокручиваются, закрывая крышку. после чего включаетсая индикация на лед-матрице.
          FastLED.clean();

          servo1.write(0);
          servo2.write(0);

          for (int i = 16; i < 80; i++) {
            if((6<(i+5)*3%16) and ((i+5)*3%16<9)){
              leds[i].setHue(counter/i*144);}
          }
          for (int i = 80; i < 176; i++) {
            leds[i].setHue(counter/i*144);
          }
          for (int j = 176; j < 240; j++) {
            if((6<(j+5)*3%16) and ((j+5)*3%16<19)){
              leds[j].setHue(counter/j*144);}
          }

          FastLED.show(); 
      }
      // Ответ сервера
    } 
    else {
      Serial.print("Ошибка при отправке запроса: ");
      Serial.println(httpResponseCode);
    }
    // Завершить соединение
  }
  if(bright == 1){
  //ручное открытие крышки дронпорта. при затемнении датчика освещения, две сервы прокручиваются, открывая дронпорт. затем включается индикация на LED-матрице.
  FastLED.clean();
  servo1.write(120);
  servo2.write(120);

  for (int i = 16; i < 80; i++) {
    if((4<(i+3)*3%16) and ((i+3)*3%16<11)){
      leds[i].setHue(counter/i*32);
    }
  }
  for (int i = 80; i < 176; i++) {
    leds[i].setHue(counter/i*32);
  }
  for (int j = 176; j < 240; j++) {
    if((4<(j+3)*3%16) and ((j+3)*3%16<11)){
      leds[j].setHue(counter/j*32);
    }
  }

  FastLED.show(); 
  }
  if (button == 1)  //ручное закрытие крышки дронпорта. при засветлении датчика освещения, две сервы прокручиваются, закрывая дронпорт. затем включается индикация на LED-матрице.
  {
    FastLED.clean();

    servo1.write(0);
    servo2.write(0);

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
        leds[j].setHue(counter/j*32);
    }

    FastLED.show(); 
  }
  }
  counter++;
     // counter меняется от 0 до 255 (тип данных byte)
       // скорость движения радуги
}
void yield() {

}
