//Arduino library for interfacing with the nau7802 24bit ADC
#ifndef __NAU7802_H__
#define __NAU7802_H__

#include <Arduino.h>
#include <Wire.h>

#define NAU7802_I2CADDR   0x2A        //Static Adress

#define NAU7802_PU_CTRL   0x00        //REG0x00:PU_CTRL     Powerup Control
#define NAU7802_CTRL1     0x01        //REG0x01:CTRL1       Control 1
#define NAU7802_CTRL2     0x02        //REG0x02:CTRL2       Control 2

#define NAU7802_OCAL1_B2  0x03        //REG0x03:OCAL1_B2    CH1 OFFSET Calibration[23:16]
#define NAU7802_OCAL1_B1  0x04        //REG0x04:OCAL1_B1    CH1 OFFSET Calibration[15:08]
#define NAU7802_OCAL1_B0  0x05        //REG0x05:OCAL1_B0    CH1 OFFSET Calibration[07:00]
#define NAU7802_GCAL1_B3  0x06        //REG0x06:GCAL1_B9    CH1 GAIN   Calibration[31:24]
#define NAU7802_GCAL1_B2  0x07        //REG0x07:GCAL1_B2    CH1 GAIN   Calibration[23:16]
#define NAU7802_GCAL1_B1  0x08        //REG0x08:GCAL1_B1    CH1 GAIN   Calibration[15:08]
#define NAU7802_GCAL1_B0  0x09        //REG0x09:GCAL1_B0    CH1 GAIN   Calibration[07:00]

#define NAU7802_OCAL2_B2  0x0A        //REG0x0A:OCAL2_B2    CH2 OFFSET Calibration[23:16]
#define NAU7802_OCAL2_B1  0x0B        //REG0x0B:OCAL2_B1    CH2 OFFSET Calibration[15:08]
#define NAU7802_OCAL2_B0  0x0C        //REG0x0C:OCAL2_B0    CH2 OFFSET Calibration[07:00]
#define NAU7802_GCAL2_B3  0x0D        //REG0x0D:GCAL2_B3    CH2 GAIN   Calibration[31:24]
#define NAU7802_GCAL2_B2  0x0E        //REG0x0E:GCAL2_B2    CH2 GAIN   Calibration[23:16]
#define NAU7802_GCAL2_B0  0x0F        //REG0x0F:GCAL2_B0    CH2 GAIN   Calibration[15:08]
#define NAU7802_GCAL2_B1  0x10        //REG0x10:GCAL2_B1    CH2 GAIN   Calibration[07:00]

#define NAU7802_I2C_CTRL  0x11        //REG0x11:I2C_CTRL    I2C Control

#define NAU7802_ADC_B2    0x12        //REG0x12:ADC_OUT_B2  ADC Conversion Result [23:16]
#define NAU7802_ADC_B1    0x13        //REG0x13:ADC_OUT_B1  ADC Conversion Result [15:08]
#define NAU7802_ADC_B0    0x14        //REG0x14:ADC_OUT_B0  ADC Conversion Result [07:00]

#define NAU7802_ADC_REG   0x15        //REG0x15:ADC_REG     ADC Registers

#define NAU7802_OTP_B1    0x16        //REG0x16:OTP_B1      OTP[15:08]
#define NAU7802_OTP_B0    0x17        //REG0x17:OTP_B0      OTP[07:00]

#define NAU7802_RES_00    0x18        //REG0x18:RES_00      RESERVED
#define NAU7802_RES_01    0x19        //REG0x19:RES_01      RESERVED
#define NAU7802_RES_02    0x1A        //REG0x1A:RES_02      RESERVED

#define NAU7802_PGA_REG   0x1B        //REG0x1B:PGA_REG     Pre-Gain Amplifier
#define NAU7802_POW_CTRL  0x1C        //REG0x1C:POW_CTRL    Power Control

#define NAU7802_RES_03    0x1D        //REG0x16:RES_03     RESERVED
#define NAU7802_RES_04    0x1E        //REG0x1E:RES_04     RESERVED

#define NAU7802_REV_ID    0x1F        //REG0x1F:READ_ONLY  MFG test and RevisionID

//REG0x00:PU_CTRL     Powerup Control
#define NAU7802_AVDDS     7  //AVDD source select          1:Internal LDO        0:AVDD Pin Input              (0-Default)
#define NAU7802_OSCS      6  //System clock source select  1:External Crystal    0:Internal RC Oscillator      (0-Default)
#define NAU7802_CR        5  //Cycle ready (Read Only)     1:ADC Data Ready      0:No ADC Data                 (0-Default)
#define NAU7802_CS        4  //Cycle start ADC             1:Start ADC           0:Stop ADC                    (0-Default)
#define NAU7802_PUR       3  //Power up ready (Read Only)  1:Power up, Ready     0:Power down, not ready       (0-Default)
#define NAU7802_PUA       2  //Power up analog circuit     1:Power up anlaog     0:Power down analog           (0-Default)
#define NAU7802_PUD       1  //Power up digital circuit    1:Power up digital    0:Power down digital          (0-Default)
#define NAU7802_RR        0  //Register Reset              1:Reset all save RR   0:Normal Operation            (0-Default)

//REG0x01:CTRL1       Control 1
#define NAU7802_CRP       7  //Conversion Ready Polarity   1:Active Low          0:Active high                 (0-Default)
#define NAU7802_DRDY_SEL  6  //DRDY pin fuction            1:Output clock        0:Output conv ready           (0-Default)

#define NAU7802_VLDO2     5  //Select LDO Voltage          1      1      1      1     0     0     0     0      (0-Default)
#define NAU7802_VLDO1     4  //Select LDO Voltage          1 2V4  1 2V7  0 3V0  0 3V3 1 3V6 1 3V9 0 4V2 0 4V5  (0-Default)
#define NAU7802_VLDO0     3  //Select LDO Voltage          1      0      1      0     1     0     1     0      (0-Default)

#define NAU7802_GAINS2    2  //Select gain                 1      1      1      1     0     0     0     0      (0-Default)
#define NAU7802_GAINS1    1  //Select gain                 1 128  1 x64  0 x32  0 x16 1 x8  1 x4  0 x2  0 x1   (0-Default)
#define NAU7802_GAINS0    0  //Select gain                 1      0      1      0     1     0     1     0      (0-Default)

//REG0x02:CTRL2       Control 2
#define NAU7802_CHS      7  //Analog input channel         1:Channel 2               0:Channel 1               (0-Default)

#define NAU7802_CRS2     6  //Converstion Rate samp/sec    1      1      1      1     0     0     0     0      (0-Default)
#define NAU7802_CRS1     5  //Converstion Rate samp/sec    1 320  1 N/A  0 N/A  0 N/A 1 80  1 40  0 20  0 10   (0-Default)
#define NAU7802_CRS0     4  //Converstion Rate samp/sec    1      0      1      0     1     0     1     0      (0-Default)

#define NAU7802_CAL_ERR  3  //Calibration Error            1:Calibration failed      0:No                      (0-Default)
#define NAU7802_CALS     2  //Start Calibration            1:Start calibration       0:Calibration finished    (0-Default)

#define NAU7802_CALMOD1  1  //Calibration Selection        1:Gain Cal  1:Offset Cal  0:RESERVED  0: Offset Cal (0-Default)
#define NAU7802_CALMOD0  0  //Calibration Selection        1:System    0:System      1:RESERVED  0: Internal   (0-Default)

//REG0x11:I2C_CTRL    I2C Control
#define NAU7802_CRSD     7  //Pull SDA low on conversion   1:Enable                  0:Diable                  (0-Default)
#define NAU7802_FRD      6  //Fast ADC DATA                1:Enable REQ REG0x15[7]:1 0:Disable                 (0-Default)
#define NAU7802_SPE      5  //Enable strong pullup         1:Enable 1K6 pullup       0:Disable 1K6 pullup      (0-Default)
#define NAU7802_WPD      4  //Disable weak pullup          1:Disable 50K pullpup     0:Enable 50K pullup       (0-Default)
#define NAU7802_SI       3  //Short Inputs                 1:Short Inputs            0:Inputs floating         (0-Default)
#define NAU7802_BOPGA    2  //PGA bunout current source    1:2.5uA Current to PGA+   0:Current disabled        (0-Default)
#define NAU7802_TS       1  //Temprature Sensor Select     1:Temprature to PGA       0:Temp disabled           (0-Default)
#define NAU7802_BGPCP    0  //Bandgap chopper              1:Disable                 0:Enable                  (0-Default)

class NAU7802 {
 public:
  NAU7802();

  #if defined NAU7802_SOFTWAREWIRE
    boolean begin(uint8_t sda, uint8_t scl, uint8_t addr = NAU7802_I2CADDR);
  #elif defined ESP8266
    boolean begin(uint8_t sda, uint8_t scl, uint8_t addr = NAU7802_I2CADDR);
  #else
    boolean begin(uint8_t addr = NAU7802_I2CADDR);
  #endif //ESP8266|NAU7802_SOFTWAREWIRE|Default

  long readADC();
  float readmV();

  void selectCh1();
  void selectCh2();
  void selectTemp();

  void rate010sps();
  void rate020sps();
  void rate040sps();
  void rate080sps();
  void rate320sps();

  void pga128x();
  void pga64x();
  void pga32x();
  void pga16x();
  void pga8x();
  void pga4x();
  void pga2x();
  void pga1x();
  void pgaDisable();

  void extAvcc(float extAvcc);
  void avcc2V4();
  void avcc2V7();
  void avcc3V0();
  void avcc3V3();
  void avcc3V6();
  void avcc3V9();
  void avcc4V2();
  void avcc4V5();

 private:

  #ifdef NAU7802_SOFTWAREWIRE
    SoftwareWire wire = SoftwareWire(2,3);
  #else
    TwoWire wire = TwoWire();
  #endif //NAU7802_SOFTWAREWIRE

  uint8_t _i2caddr;
  float _avcc = 3.3;

  void resetSettings();
  void calibrate();

  void write(uint8_t reg, uint8_t val);
  void writeBit(uint8_t reg, uint8_t bit);
  void clearBit(uint8_t reg, uint8_t bit);


  uint8_t  read(uint8_t reg);
  uint32_t read24(uint8_t reg);
  uint32_t read32(uint8_t reg);
  boolean  readBit(uint8_t reg, uint8_t bit);

  void  readUntilTrue(uint8_t reg, uint8_t bit);
  void  readUntilFalse(uint8_t reg, uint8_t bit);
};

#endif //__NAU7802_H__
