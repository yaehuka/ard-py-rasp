#define LED_PIN 4
#define BRIGHT_PIN 5
#define SERVO1_PIN 18
#define SERVO2_PIN 19
#define BUTTON_PIN 21
#define LED_NUM 256
#include "FastLED.h"
#include "ESP32Servo.h"
int countt;
int brightt = 0;
Servo servo1;
CRGB leds[LED_NUM];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(brightt);
  pinMode(BRIGHT_PIN, INPUT);
  servo1.attach(SERVO1_PIN);
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
}
byte counter;
void loop() {
  int bright = digitalRead(BRIGHT_PIN);
  int button = digitalRead(BUTTON_PIN);
  FastLED.clear();
  Serial.println(bright);
    if(bright == 1)
  {
    servo1.write(180);
  }
  else
  {
    servo1.write(0);
  }
  for (int _ = 0; _ < 255; _++) {
    FastLED.setBrightness(_);
  }
  for (int i = 0; i < 80; i++) {
    leds[i].setRGB(255, 255, 255);
  }
  for (int i = 80; i < 160; i++) {
    leds[i].setHue(160);
  }
  for (int j = 160; j < 256; j++) {
    leds[j].setHue(0);
  }


  delay(40);
  FastLED.show();
  delay(30);       // counter меняется от 0 до 255 (тип данных byte)
       // скорость движения радуги
}
