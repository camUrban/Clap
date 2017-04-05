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
const int servoHalfMillis = 350;  //Determine experimentally
const double clapVoltage = 2.4;   //Determine experimentally
double microphoneValue = 0;
double microphoneVoltage = 0;

void setup() {
  servoTop.attach(servoTopPin);
  servoBottom.attach(servoBottomPin);
  servoTop.write(servoSpeed);
  servoBottom.write(servoSpeed);
}

void loop() {
  microphoneValue = analogRead(microphonePin);
  microphoneVoltage = microphoneValue * 5.0 / 1023.0;
  
  if(microphoneVoltage > clapVoltage) {
    if(servoSpeed == 0) {
      servoSpeed = 180;
    }
    
    else {
      servoSpeed = 0;
    }
    
    servoTop.write(servoSpeed);
    delay(servoHalfMillis);
    servoBottom.write(servoSpeed);
    delay(servoHalfMillis);
    servoTop.write(90);
    servoBottom.write(90);
    delay(500);
  }
  delay(5);
}
