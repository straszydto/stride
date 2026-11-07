#include <Arduino.h>
#include "sbus.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

#define SERVOMIN 102
#define SERVOMAX 512
#define SERVO_FREQ 50

#define SBUS_RX 16
#define SBUS_TX -1

#define js_deadzone 100

//servo number 1, 3, 5, 7
int fl_hip, fr_hip, bl_hip, br_hip;
//servo number 2, 4, 6, 8
int fl_joint, fr_joint, bl_joint, br_joint;

bfs::SbusRx sbus(&Serial2, SBUS_RX, SBUS_TX, true);

void setup() {
  Serial.begin(19200);
  Serial.println("Starting...");

  sbus.begin();

  // ESP32 I2C pins
  Wire.begin();

  driver.begin();
  driver.setPWMFreq(SERVO_FREQ);

  fl_hip=fl_joint=90;
  fr_hip=fr_joint=90;
  bl_hip=bl_joint=90;
  br_hip=br_joint=90;
}

void moveServo(int angle, int srv_num) {
  if (angle < 0 || angle > 180) break;
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  driver.setPWM(srv_num, 0, pulse);
}

void forward(int amt) {
  
}

void loop() {
  if (sbus.Read()) {
    bfs::SbusData data = sbus.data();

    if (abs(data[0]) > 100) {
      int amt = map(data, -1000, 1000, -5, 5);
      forward(amt);
    }

  }

  if (Serial.available() > 0) {

    Serial.println("S AVAI");

    // Read user input
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() == 0) return;

    // Validate numeric input
    for (int i = 0; i < input.length(); i++) {
      if (!isDigit(input[i])) {
        Serial.println("Invalid input!");
        return;
      }
    }

    int angle = input.toInt();
  }


}
