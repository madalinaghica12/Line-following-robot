#define IR_SENSOR_RIGHT A0
#define IR_SENSOR_LEFT A1
#define MOTOR_SPEED 90
#define buzzer_pin 3
//Right motor
int enableRightMotor=11;
int rightMotorPin1=7;
int rightMotorPin2=8;
const int trigPin = 6;
const int echoPin = 5;
long duration;
int distance;
//Left motor
int enableLeftMotor=12;
int leftMotorPin1=9;
int leftMotorPin2=10;
#include <Adafruit_NeoPixel.h>
#define neopixel_pin 2
#define num_pixels 16
Adafruit_NeoPixel strip = Adafruit_NeoPixel(num_pixels, neopixel_pin, NEO_GRB + NEO_KHZ800);
// buzzer
int melody[] = {262, 196, 196, 220, 196, 0, 247, 262}; //frecvente de note muzicale+9
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4 };
void setup()
{
 TCCR0B = TCCR0B & B11111000 | B00000010 ;
 // put your setup code here, to run once:
 pinMode(rightMotorPin1, OUTPUT);
 pinMode(enableRightMotor, OUTPUT);
 pinMode(enableLeftMotor, OUTPUT);
 pinMode(rightMotorPin2, OUTPUT);
 pinMode(buzzer_pin, OUTPUT);
 pinMode(leftMotorPin1, OUTPUT);
 pinMode(leftMotorPin2, OUTPUT);
 pinMode(IR_SENSOR_RIGHT, INPUT);
 pinMode(IR_SENSOR_LEFT, INPUT);
 pinMode(neopixel_pin, OUTPUT);
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 strip.begin(); //initializarea benzii de LED-uri RGB
 strip.setBrightness(50); //setarea luminozitatii pentru banda de LED-uri (maxim 255)
 strip.show(); //afisarea benzii de LED-uri
 functie_pornire();
 rotateMotor(0,0);
   Serial.begin(9600);
}

void loop()
{
 int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
 int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = duration * 0.034 / 2;
 if (distance <= 12)
 {
   rotateMotor(0, 0); // Stop the motors
   delay(500);
   // Add any other actions you want to perform when an object is detected.
 }
 else
 {
 //If none of the sensors detects black line, then go straight
 if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
 {
   rotateMotor(- MOTOR_SPEED, -MOTOR_SPEED);
   tone(buzzer_pin, 1000);
   delay(50);
 }
 else if(rightIRSensorValue == LOW && leftIRSensorValue == HIGH )
 {
   rotateMotor(0, -MOTOR_SPEED);
   tone(buzzer_pin, 1000);
   delay(50);
 }
 else if(rightIRSensorValue == HIGH && leftIRSensorValue == LOW )
 {
   rotateMotor(- MOTOR_SPEED,0);
   tone(buzzer_pin, 1000);
   delay(50);
 }
 else
 {
   rotateMotor(0, 0);
    noTone(buzzer_pin);
 }
 }
 Serial.println(distance);
}
void functie_pornire() {
 functie_melodie(); // Redă melodia când pornește
 for (int i = 0; i < strip.numPixels(); i++) {
   strip.setPixelColor(i, strip.Color(255, 0, 255));
   strip.show();
   delay(50);
 }
 delay(200);
 for (int i = 0; i < strip.numPixels(); i++) {
   strip.setPixelColor(i, strip.Color(0, 0, 0));
   strip.show();
   delay(4000);
 }
 // Așteaptă ca ultimul LED să se stingă înainte de a continua
 while(strip.getPixelColor(strip.numPixels() - 1) != 0) {
   delay(10);
 }
 delay(200);
}
void functie_melodie() {
 // Modifică duratele notelor pentru a face melodia să dureze mai mult
 int noteDurations[] = {16, 16, 16, 16, 16, 16, 16, 16 };
 for (int thisNote = 0; thisNote < 8; thisNote++) {
   int noteDuration = 1000 / noteDurations[thisNote];
   tone(buzzer_pin, melody[thisNote], noteDuration);
   int pauseBetweenNotes = noteDuration * 2.00;
   delay(pauseBetweenNotes);
   noTone(buzzer_pin);
 }
}
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
 if (rightMotorSpeed < 0)
 {
   digitalWrite(rightMotorPin1,LOW);
   digitalWrite(rightMotorPin2,HIGH);    
 }
 else if (rightMotorSpeed > 0)
 {
   digitalWrite(rightMotorPin1,HIGH);
   digitalWrite(rightMotorPin2,LOW);      
 }
 else
 {
   digitalWrite(rightMotorPin1,LOW);
   digitalWrite(rightMotorPin2,LOW);      
 }
 if (leftMotorSpeed < 0)
 {
   digitalWrite(leftMotorPin1,LOW);
   digitalWrite(leftMotorPin2,HIGH);    
 }
 else if (leftMotorSpeed > 0)
 {
   digitalWrite(leftMotorPin1,HIGH);
   digitalWrite(leftMotorPin2,LOW);      
 }
 else
 {
   digitalWrite(leftMotorPin1,LOW);
   digitalWrite(leftMotorPin2,LOW);      
 }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
 analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}
