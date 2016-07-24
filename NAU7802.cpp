//Readout for nau7802
#include <Arduino.h>
#include <Wire.h>
#include "NAU7802.h"

//Instantiates a new NAU7802 class
//================================
NAU7802::NAU7802() {
}

// Setups the HW
//==============
boolean NAU7802::begin(uint8_t sda, uint8_t scl, uint8_t addr) {
  _i2caddr = addr;
  Wire.begin(sda,scl);

  write(NAU7802_PU_CTRL,   0x01);    //reset Registers
  write(NAU7802_PU_CTRL,   0x02);    //Power up digital
  readUntilTrue(NAU7802_PU_CTRL, 3); //Wait until power up
  write(NAU7802_PU_CTRL,   0x06);    //Power up analog
  write(NAU7802_CTRL1,     0x38);    //Set AVCC to 2.4V
  write(NAU7802_PGA_REG,   0x01);    //Turn off chopper function
  write(NAU7802_CTRL2,     0x04);    //Begin calibration
  readUntilFalse(NAU7802_CTRL2, 2);  //Wait for calibration to finish
  write(NAU7802_CTRL2,     0x00);    //Conversion Rate = 10SPS
  write(NAU7802_I2C_CTRL,  0x10);    //Enable Strong Pullup
  write(NAU7802_PU_CTRL,   0x16);    //Start Conversion

  return true;
}

//Reads set channel
//======================
long NAU7802::readADC()
{
  readUntilTrue(NAU7802_PU_CTRL,NAU7802_CR);
  uint32_t adcVal = read24(NAU7802_ADC_B2);
  if(adcVal & 0x00800000){
    adcVal = ~adcVal+1;
    adcVal = -1*(adcVal & 0x00FFFFFF);
  }
  return adcVal;
}

//Select channel
//=============
void NAU7802::selectCh1(){
  clearBit(NAU7802_CTRL2, 7);
}
void NAU7802::selectCh2(){
  writeBit(NAU7802_CTRL2, 7);
}

//Set Sampling rate
//================
void NAU7802::rate010sps(){
  clearBit(NAU7802_CTRL2, 4);
  clearBit(NAU7802_CTRL2, 5);
  clearBit(NAU7802_CTRL2, 6);
}
void NAU7802::rate020sps(){
  clearBit(NAU7802_CTRL2, 4);
  clearBit(NAU7802_CTRL2, 5);
  writeBit(NAU7802_CTRL2, 6);
}
void NAU7802::rate040sps(){
  clearBit(NAU7802_CTRL2, 4);
  writeBit(NAU7802_CTRL2, 5);
  clearBit(NAU7802_CTRL2, 6);
}
void NAU7802::rate080sps(){
  clearBit(NAU7802_CTRL2, 4);
  writeBit(NAU7802_CTRL2, 5);
  writeBit(NAU7802_CTRL2, 6);
}
void NAU7802::rate320sps(){
  writeBit(NAU7802_CTRL2, 4);
  writeBit(NAU7802_CTRL2, 5);
  writeBit(NAU7802_CTRL2, 6);
}

//Low level read and write procedures

void NAU7802::write(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.write(val);
  Wire.endTransmission();
}

void NAU7802::writeBit(uint8_t reg, uint8_t bit) {
  uint8_t val = read(reg) | (1<<bit);
  write(reg, val);
}

void NAU7802::clearBit(uint8_t reg, uint8_t bit) {
  uint8_t val = read(reg) & ~(1<<bit);
  write(reg, val);
}

uint8_t NAU7802::read(uint8_t reg) {
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  return Wire.read();
}

boolean NAU7802::readBit(uint8_t reg, uint8_t bit){
  //create bitmask
  uint8_t bitmask = 1<<bit;
  if(read(reg) & bitmask){
    return true;
  }
  return false;
}

uint32_t NAU7802::read24(uint8_t reg) {
  uint32_t val;

  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)3);
  val = Wire.read();    // receive high byte
  val <<= 8;            // shift byte to make room for new byte
  val |= Wire.read();   // receive mid byte
  val <<= 8;            // shift both bytes
  val |= Wire.read();   // receive low byte
  return val;
}

uint32_t NAU7802::read32(uint8_t reg) {
  uint32_t val;

  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)4);
  val = Wire.read();    // receive [31:24] byte
  val <<= 8;            // shift byte
  val = Wire.read();    // receive [23:16] byte
  val <<= 8;            // shift bytes
  val |= Wire.read();   // receive [15:08] byte
  val <<= 8;            // shift bytes
  val |= Wire.read();   // receive [07:00] byte
  return val;
}

void NAU7802::readUntilTrue(uint8_t reg, uint8_t bit) {
  //create bitmask
  uint8_t bitmask = 1<<bit;
  bool readUntil = false;
  //Just keep reading until bit requested is true
  while(readUntil == false){
    if(read(reg) & bitmask){
      readUntil=true;
    }
  }
}

void NAU7802::readUntilFalse(uint8_t reg, uint8_t bit) {
  //create bitmask
  uint8_t bitmask = 1<<bit;
  bool readUntil = false;
  //Just keep reading until bit requested is false
  while(readUntil == false){
    if(~read(reg) & bitmask){
      readUntil=true;
    }
  }
}
