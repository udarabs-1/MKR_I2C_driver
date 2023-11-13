#include <Wire.h>
#include <SparkFunMiniMoto.h>

MiniMoto motor(0x60); 
MiniMoto motor1(0x65);
void setup() {
  Serial.begin(9600);
  Serial.println("MiniMoto Test");
  Wire.begin();
}

void loop() {
  byte fault = motor.getFault();
  if (fault) {
    Serial.print("Fault: ");
    Serial.println(fault, HEX);
  } else {
    Serial.println("Driving forward");
    motor.drive(100);
    motor1.drive(100);
    delay(1000);
    Serial.println("Driving Backward");
    motor.drive(-100);
    motor1.drive(-100);
    delay(1000);
    Serial.println("Stopping");
    motor.stop();
    motor1.stop();
    delay(1000);
  }
}
