#include <Wire.h>
#define TRIG_PIN 5
#define ECHO_PIN 18
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Wire.begin();
  mpu.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

int getDistance() {
  // Measure distance using HC-SR04
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  // Move the EEEbot forward by setting L and R motor speeds
  // Send the values 255, 255, and 0 to the Arduino 
  Wire.beginTransmission(0x04); // Send to arduino
  Wire.write(255);
  Wire.write(255);
  Wire.write(0);
  Wire.endTransmission();

  delay(1000); // Wait for 1 second

  // Stop the EEEbot forward by setting L and R motor speeds
  // Send the values 0, 0, and 0 to the Arduino 
  Wire.beginTransmission(0x04); // Send to arduino
  Wire.write(0);
  Wire.write(0);
  Wire.write(0);
  Wire.endTransmission();

  Wire.beginTransmission(0x04);
  // Send initial values to the Arduino
  Wire.write(255);
  Wire.write(255);
  Wire.write(180);
  Wire.endTransmission();

  mpu.update();
  // Read the Z-axis rotation
  int zRotation = mpu.getRotationZ();
  // Check if the MPU has been rotated 180 degrees on the Z-axis
  if (zRotation >= 180) {
    // Send the values to the Arduino
    Wire.beginTransmission(0x04);
    Wire.write(0);
    Wire.write(0);
    Wire.write(0);
    Wire.endTransmission();
  }

  // Send values -255, -255, 0 to the Arduino Nano
  Wire.beginTransmission(0x04);
  Wire.write(-255);
  Wire.write(-255);
  Wire.write(0);
  Wire.endTransmission();

  int distance = getDistance();

  // Check if distance is less than or equal to 10cm
  if (distance <= 10) {
    // Send values 0, 0, 0 to the Arduino Nano
    Wire.beginTransmission(0x04);
    Wire.write(0);
    Wire.write(0);
    Wire.write(0);
    Wire.endTransmission();
  }

    Wire.beginTransmission(0x04);
  // Send initial values to the Arduino
  Wire.write(-255);
  Wire.write(-255);
  Wire.write(180);
  Wire.endTransmission();

  mpu.update();
  // Read the Z-axis rotation
  int zRotation = mpu.getRotationZ();
  // Check if the MPU has been rotated 90 degrees on the Z-axis
  if (zRotation >= 90) {
    // Send the values to the Arduino
    Wire.beginTransmission(0x04);
    Wire.write(0);
    Wire.write(0);
    Wire.write(0);
    Wire.endTransmission();
  }

  // Send values -255, -255, 0 to the Arduino Nano
  Wire.beginTransmission(0x04);
  Wire.write(-255);
  Wire.write(-255);
  Wire.write(0);
  Wire.endTransmission();

  int distance = getDistance();

  // Check if distance is less than or equal to 10cm
  if (distance <= 10) {
    // Send values 0, 0, 0 to the Arduino Nano
    Wire.beginTransmission(0x04);
    Wire.write(0);
    Wire.write(0);
    Wire.write(0);
    Wire.endTransmission();
  }

}
