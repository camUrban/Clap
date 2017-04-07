/**
 * Clap Activated Lighting Module
 * 
 * @author: Cameron Urban
 * @date: 4/5/2017
 * 
 * Wiring:
 *    
 *    Microcontroller: Arduino Nano
 *    
 *    MAX4466 Electret Microphone Amplifier:
 *    GND:GND
 *    VCC:3.3V
 *    OUT:A0
 *    
 *    SM-S4303R High Torque Continuous Rotation Servo 1:
 *    GND:GND
 *    VCC:5V
 *    SIGNAL:D3
 *    
 *    SM-S4303R High Torque Continuous Rotation Servo 2:
 *    GND:GND
 *    VCC:5V
 *    SIGNAL:D5
 */
 
#include <Servo.h>

Servo servoTop;
Servo servoBottom;

const int servoTopPin = 3;
const int servoBottomPin = 5;
const int microphonePin = 0;
int servoSpeed = 90;
const int servoMillis = 300;  //Determine experimentally
const double clapVoltage = 1.8;   //Determine experimentally
double microphoneValue = 0;
double microphoneVoltage = 0;
boolean lightOn = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  servoTop.attach(servoTopPin);
  servoBottom.attach(servoBottomPin);
  servoTop.write(servoSpeed);
  servoBottom.write(servoSpeed);
  Serial.println("Initialized.");
}

void loop() {
  microphoneValue = analogRead(microphonePin);
  microphoneVoltage = microphoneValue * 5.0 / 1023.0;
  Serial.println(microphoneVoltage);
  
  if(microphoneVoltage > clapVoltage) {
    Serial.println("Clap Detected");
    if(servoSpeed == 0) {
      servoSpeed = 180;
    }
    
    else {
      servoSpeed = 0;
    }
    
    servoTop.write(servoSpeed);
    delay(servoMillis);
    delay(50);
    servoBottom.write(servoSpeed);
    delay(servoMillis);
    delay(50);
    servoTop.write(90);
    servoBottom.write(90);
    if(!lightOn) {
      Serial.println("Lights On");
    }
    else {
      Serial.println("Lights Off");
    }

    lightOn = !lightOn;
    delay(500);
    
  }
  delay(50);
}
