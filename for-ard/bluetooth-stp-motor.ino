#include <Servo.h>
#include <Ultrasonic.h>
//Управляем роботом с помощью BLUETOOTH.
//В качестве управляющего устройства используем ANDROID устройство с программой Bluetooth RC Controller.

// *********************** Установка выводов моторов ************************
int MotorRightSpeed = 5; // Левый (А) мотор СКОРОСТЬ — ENA
int MotorRightForward = 2; // Левый (А) мотор ВПЕРЕД — IN1
int MotorRightBack = 4; // Левый (А) мотор НАЗАД — IN2
int MotorLeftForward = 7; // Правый (В) мотор ВПЕРЕД — IN3
int MotorLeftBack = 8; // Правый (В) мотор НАЗАД — IN4
int MotorLeftSpeed = 6; // Правый (В) мотор СКОРОСТЬ — ENB
int Speed=100;
int Trig =9;
int Echo=10;
Servo servo;
Ultrasonic ultrasonic(Trig,Echo);
//int LED = 13;

// ********************** Для управления по блютуз ****************************
char btCommand = 'S';// Задаем переменную BLUETOOTH команда — по умолчанию "S" — СТОП

// ********************************** SETUP ***********************************
void setup ()
{
Serial.begin (9600); //Включаем серйиный порт — скрость 9600

//****************** Настраиваем параметры выводов ARDUINO ******************
pinMode (MotorLeftForward, OUTPUT);
pinMode (MotorLeftBack, OUTPUT);
pinMode (MotorLeftSpeed, OUTPUT);

pinMode (MotorRightForward, OUTPUT);
pinMode (MotorRightBack, OUTPUT);
pinMode (MotorRightSpeed, OUTPUT);

//pinMode(LED, OUTPUT);
//digitalWrite(LED, HIGH);

//servo.attach(10);
}
// ****************** Задаем основные направления движения ******************
void forward (int a) // ВПЕРЕД
{
digitalWrite (MotorRightBack, LOW);
digitalWrite (MotorRightForward, HIGH);
analogWrite (MotorRightSpeed, Speed);
digitalWrite (MotorLeftBack, LOW);
digitalWrite (MotorLeftForward, HIGH);
analogWrite (MotorLeftSpeed, Speed*0.9);
}
void rightF (int b) // ПОВОРОТ ВПРАВО (одна сторона)
{
digitalWrite (MotorLeftBack, LOW);
digitalWrite (MotorLeftForward, HIGH);
analogWrite (MotorLeftSpeed, Speed);
digitalWrite (MotorRightBack, LOW);
digitalWrite (MotorRightForward, HIGH);
analogWrite (MotorRightSpeed, Speed/2);
}
void rightB (int b) // ПОВОРОТ ВПРАВО (одна сторона)
{
digitalWrite (MotorLeftBack, HIGH);
digitalWrite (MotorLeftForward, LOW);
analogWrite (MotorLeftSpeed, Speed);
digitalWrite (MotorRightBack, HIGH);
digitalWrite (MotorRightForward, LOW);
analogWrite (MotorRightSpeed, Speed/2);
}
void leftF (int c) // ПОВОРОТ ВЛЕВО (одна сторона)
{
digitalWrite (MotorRightBack, LOW);
digitalWrite (MotorRightForward, HIGH);
analogWrite (MotorRightSpeed, Speed);
digitalWrite (MotorLeftBack, LOW);
digitalWrite (MotorLeftForward, HIGH);
analogWrite (MotorLeftSpeed, Speed/2);
}
void leftB (int c) // ПОВОРОТ ВЛЕВО (одна сторона)
{
digitalWrite (MotorRightBack, HIGH);
digitalWrite (MotorRightForward, LOW);
analogWrite (MotorRightSpeed, Speed);
digitalWrite (MotorLeftBack, HIGH);
digitalWrite (MotorLeftForward, LOW);
analogWrite (MotorLeftSpeed, Speed/2);
}
void turnL (int d) // РАЗВОРОТ Влево (два стороны)
{
digitalWrite (MotorRightBack, LOW);
digitalWrite (MotorRightForward, HIGH);
analogWrite (MotorRightSpeed, Speed);
digitalWrite (MotorLeftBack, HIGH);
digitalWrite (MotorLeftForward, LOW);
analogWrite (MotorLeftSpeed, Speed);
}
void turnR (int e) // РАЗВОРОТ Вправо (два стороны)
{
digitalWrite (MotorRightBack, HIGH);
digitalWrite (MotorRightForward, LOW);
analogWrite (MotorRightSpeed, Speed);
digitalWrite (MotorLeftBack, LOW);
digitalWrite (MotorLeftForward, HIGH);
analogWrite (MotorLeftSpeed, Speed);
}
void stopp (int f) // СТОП
{
digitalWrite (MotorRightBack, LOW);
digitalWrite (MotorRightForward, LOW);
digitalWrite (MotorLeftBack, LOW);
digitalWrite (MotorLeftForward, LOW);
}
void back (int g) // НАЗАД
{
digitalWrite (MotorRightBack, HIGH);
digitalWrite (MotorRightForward, LOW);
analogWrite (MotorRightSpeed, Speed);
digitalWrite (MotorLeftBack, HIGH);
digitalWrite (MotorLeftForward, LOW);
analogWrite (MotorRightSpeed, Speed);
}
// ********************* Управление по БЛЮТУЗ ****************************
void loop()
{
if (Serial.available() > 0)// В случае если в "Серийном порту" есть информация
{
btCommand = Serial.read(); // Считываем инвормацию с "Серийного порта"
//Serial.println(btCommand); // Печатаем инвормацию с "Серийного порта" — необходио в слуае отладки программы
switch (btCommand)// Отрабатывем в соотвествии с поступившей командой
{
case '0':  
Speed=0;
break;
case '1':  
Speed=25;
break;
case '2':  
Speed=50;
break;
case '3':  
Speed=75;
break;
case '4':  
Speed=100;
break;
case '5':  
Speed=125;
break;
case '6':  
Speed=150;
break;
case '7':  
Speed=175;
break;
case '8':  
Speed=200;
break;
case '9':  
Speed=225;
break;
case 'q':  
Speed=250;
break;
case 'F':
forward (3); // едем ВПЕРЕД
break;
case 'B':
back (3); // едем НАЗАД
break;
case 'R':
turnR (3);
break;
case 'L':
turnL (3);
break;
case 'S':
stopp (3); // СТОП!
break;
case 'G':
leftF (3);//вперед-лево
break;
case 'I':
rightF (3);//вперед-право
break;
case 'H':
leftB (3);//назад-лево
break;
case 'J':
rightB (3);//назад-право
break;
case 'W':
servo.write(0);
break;
case 'U':
servo.write(180);                                                  
break;  
}
float dist_cm=ultrasonic.Ranging(CM);
//float dist_cm=ultrasonic.distanceRead(CM);
if (dist_cm<=20 ){
  stopp (3); 
  for(int i=1;i<=10;i++){  
  back (3);
  rightF (3);  
}
}
}  
}
