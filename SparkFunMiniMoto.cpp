#include "SparkFunMiniMoto.h"

MiniMoto::MiniMoto(byte addr) {
    _addr = addr;
}

byte MiniMoto::getFault() {
    byte buffer = 0;
    byte clearFault = 0x80;
    I2CReadBytes(0x01, &buffer, 1);
    I2CWriteBytes(0x01, &clearFault, 1);
    return buffer;
}

void MiniMoto::drive(int speed) {
    byte regValue = 0x80; // Clear the fault status
    I2CWriteBytes(0x01, &regValue, 1);
    regValue = (byte)abs(speed);
    if (regValue > 63) {
        regValue = 63; // Cap the value at 63
    }
    regValue = regValue << 2; // Left shift to make room for bits 1:0
    if (speed < 0) {
        regValue |= 0x01; // Set bits 1:0 based on sign of input
    } else {
        regValue |= 0x02;
    }
    I2CWriteBytes(0x00, &regValue, 1);
}

void MiniMoto::stop() {
    byte regValue = 0; // HI-Z
    I2CWriteBytes(0x00, &regValue, 1);
}

void MiniMoto::brake() {
    byte regValue = 0x03; // Brake
    I2CWriteBytes(0x00, &regValue, 1);
}

void MiniMoto::I2CWriteBytes(byte addr, byte* buffer, byte len) {
    Wire.beginTransmission(_addr);
    Wire.write(addr);
    for (byte i = 0; i < len; i++) {
        Wire.write(buffer[i]);
    }
    Wire.endTransmission();
}

void MiniMoto::I2CReadBytes(byte addr, byte* buffer, byte len) {
    Wire.beginTransmission(_addr);
    Wire.write(addr);
    Wire.endTransmission(false); // Send repeated start
    Wire.requestFrom(_addr, len);
    for (byte i = 0; i < len; i++) {
        buffer[i] = Wire.read();
    }
}
