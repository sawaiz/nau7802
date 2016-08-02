//Readout for nau7802
#include "NAU7802.h"

//Instantiates a new NAU7802 class
//================================
NAU7802::NAU7802() {
}

// Setups the HW
//==============
#ifdef NAU7802_DEFAULT_WIRE
boolean NAU7802::begin(uint8_t addr) {
  _i2caddr = addr;
  wire = TwoWire();
  wire.begin();
  resetSettings();
  return true;
}
#endif //NAU7802_DEFAULT_WIRE

#ifdef NAU7802_SOFTWARE_WIRE
boolean NAU7802::begin(uint8_t sda, uint8_t scl, uint8_t addr) {
  _i2caddr = addr;
  wire = SoftwareWire(sda,scl);
  wire.begin();
  resetSettings();
  return true;
}
#endif //NAU7802_SOFTWARE_WIRE

#ifdef NAU7802_ESP8266_WIRE
boolean NAU7802::begin(uint8_t sda, uint8_t scl, uint8_t addr) {
  _i2caddr = addr;
  wire = TwoWire();
  wire.begin(sda,scl);
  resetSettings();
  return true;
}
#endif //NAU7802_ESP8266_WIRE

void NAU7802::resetSettings(){
  writeBit(NAU7802_PU_CTRL, NAU7802_RR);        //Reset Registers
  clearBit(NAU7802_PU_CTRL, NAU7802_RR);        //Clear Reset Registers
  writeBit(NAU7802_PU_CTRL, NAU7802_PUD);       //Power up digital
  readUntilTrue(NAU7802_PU_CTRL, NAU7802_PUR);  //Wait until power up
  writeBit(NAU7802_PU_CTRL, NAU7802_PUA);       //Power up analog

  writeBit(NAU7802_ADC_REG, 4);                 //Diasble chopper funcition
  writeBit(NAU7802_ADC_REG, 5);                 //Diasble chopper funcition

  writeBit(NAU7802_PGA_REG, 0);                 //Diasble chopper funcition
  writeBit(NAU7802_PGA_REG, 4);                 //Bypass PGA

  writeBit(NAU7802_CTRL2, NAU7802_CALS);        //Begin calibration
  readUntilFalse(NAU7802_CTRL2, NAU7802_CALS);  //Wait for calibration to finish

  writeBit(NAU7802_I2C_CTRL, NAU7802_SPE);      //Enable Strong Pullup

  writeBit(NAU7802_PU_CTRL,   NAU7802_CS);      //Start Conversion
}

//Reads set channel
//======================
long NAU7802::readADC(){
  readUntilTrue(NAU7802_PU_CTRL,NAU7802_CR);
  uint32_t adcVal = read24(NAU7802_ADC_B2);
  writeBit(NAU7802_PU_CTRL, NAU7802_CS);
  if(adcVal & 0x00800000){
    adcVal = ~adcVal+1;
    adcVal = -1*(adcVal & 0x00FFFFFF);
  }
  return adcVal;
}

float NAU7802::readmV(){
  return (_avcc/(float)16777216)*(float)readADC();
}

//Select channel
//=============
void NAU7802::selectCh1(){
  clearBit(NAU7802_CTRL2, 7);
}
void NAU7802::selectCh2(){
  writeBit(NAU7802_CTRL2, 7);
}
void NAU7802::selectTemp(){
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

//Set Pre-Gain Amplifier
//======================
void NAU7802::pga128x(){
}
void NAU7802::pga64x(){
}
void NAU7802::pga32x(){
}
void NAU7802::pga16x(){
}
void NAU7802::pga8x(){
}
void NAU7802::pga4x(){
}
void NAU7802::pga2x(){
}
void NAU7802::pga1x(){
}
void NAU7802::pgaDisable(){
}

//Set AVCC, Internal LDO
//======================
void NAU7802::extAvcc(float extAvcc){

}
void NAU7802::avcc2V4(){
}
void NAU7802::avcc2V7(){
}
void NAU7802::avcc3V0(){
}
void NAU7802::avcc3V3(){
}
void NAU7802::avcc3V6(){
}
void NAU7802::avcc3V9(){
}
void NAU7802::avcc4V2(){
}
void NAU7802::avcc4V5(){
}
//write(NAU7802_CTRL1,     0x38);    //Set AVCC to 2.4V

//Low level read and write procedures
//===================================

void NAU7802::write(uint8_t reg, uint8_t val) {
  wire.beginTransmission(_i2caddr);
  wire.write((uint8_t)reg);
  wire.write(val);
  wire.endTransmission();
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
  wire.beginTransmission(_i2caddr);
  wire.write((uint8_t)reg);
  wire.endTransmission();

  wire.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  return wire.read();
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

  wire.beginTransmission(_i2caddr);
  wire.write((uint8_t)reg);
  wire.endTransmission();

  wire.requestFrom((uint8_t)_i2caddr, (uint8_t)3);
  val = wire.read();    // receive high byte
  val <<= 8;            // shift byte to make room for new byte
  val |= wire.read();   // receive mid byte
  val <<= 8;            // shift both bytes
  val |= wire.read();   // receive low byte
  return val;
}

uint32_t NAU7802::read32(uint8_t reg) {
  uint32_t val;

  wire.beginTransmission(_i2caddr);
  wire.write((uint8_t)reg);
  wire.endTransmission();

  wire.requestFrom((uint8_t)_i2caddr, (uint8_t)4);
  val = wire.read();    // receive [31:24] byte
  val <<= 8;            // shift byte
  val = wire.read();    // receive [23:16] byte
  val <<= 8;            // shift bytes
  val |= wire.read();   // receive [15:08] byte
  val <<= 8;            // shift bytes
  val |= wire.read();   // receive [07:00] byte
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
