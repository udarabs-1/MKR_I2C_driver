#ifndef SparkFunMiniMoto_h
#define SparkFunMiniMoto_h

#include <Arduino.h>
#include <Wire.h>

class MiniMoto {
  public:
    MiniMoto(byte addr);
    void drive(int speed);
    void stop();
    void brake();
    byte getFault();
  private:
    void I2CWriteBytes(byte addr, byte* buffer, byte len);
    void I2CReadBytes(byte addr, byte* buffer, byte len);
    byte _addr;
};

#endif

