
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

#define SERVOMIN 102
#define SERVOMAX 512
#define SERVO_FREQ 50

void setup() {
  Serial.begin(19200);
  Serial.println("Starting...");

  // ESP32 I2C pins
  Wire.begin();

  driver.begin();
  driver.setPWMFreq(SERVO_FREQ);

  delay(100);

  Serial.println("Enter an angle between 0 and 180:");
}

void moveServo(int angle, int srv_num) {
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  driver.setPWM(srv_num, 0, pulse);
}

void loop() {
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

    // Validate angle
    if (angle < 0 || angle > 180) {
      Serial.println("Angle must be between 0 and 180!");
      return;
    }

    // Convert angle to PWM
    

    // Move all servos
    // for (uint8_t servonum = 0; servonum < NUMSERVOS; servonum++) {
    //   driver.setPWM(servonum, 0, pulse);
    // }

    // Output results
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" degrees | PWM: ");
    Serial.print(pulse);
    Serial.print(" | Servos: ");
  }
}
