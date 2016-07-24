//Arduino library for interfacing with the nau7802 24bit ADC

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

//REG0x00:PU_CTRL         Powerup Control
#define NAU7802_AVDDS  7  //AVDD source select          1:Internal LDO        0:AVDD Pin Input         (0-Default)
#define NAU7802_OSCS   6  //System clock source select  1:External Crystal    0:Internal RC OScillator (0-Default)
#define NAU7802_CR     5  //Cycle ready (Read Only)     1:ADC Data Ready      0:No ADC Data            (0-Default)
#define NAU7802_CS     4  //Cycle start ADC             1:Start ADC           0:Stop ADC               (0-Default)
#define NAU7802_PUR    3  //Power up ready (Read Only)  1:Power up, Ready     0:Power down, not ready  (0-Default)
#define NAU7802_PUA    2  //Power up analog circuit     1:Power up anlaog     0:Power down analog      (0-Default)
#define NAU7802_PUD    1  //Power up digital circuit    1:Power up digital    0:Power down digital     (0-Default)
#define NAU7802_RR     0  //Register Reset              1:Reset all save RR   0:Normal Operation       (0-Default)


class NAU7802 {
 public:
  NAU7802();
	boolean begin(uint8_t sda, uint8_t scl, uint8_t addr = NAU7802_I2CADDR);

  long readADC();

  void selectCh1();
  void selectCh2();

  void rate010sps();
  void rate020sps();
  void rate040sps();
  void rate080sps();
  void rate320sps();

	void write(uint8_t reg, uint8_t val);
  void writeBit(uint8_t reg, uint8_t bit);
  void clearBit(uint8_t reg, uint8_t bit);


	uint8_t  read(uint8_t reg);
	uint32_t read24(uint8_t reg);
	uint32_t read32(uint8_t reg);
	boolean  readBit(uint8_t reg, uint8_t bit);

	void  readUntilTrue(uint8_t reg, uint8_t bit);
	void  readUntilFalse(uint8_t reg, uint8_t bit);

 private:
  uint8_t _i2caddr;
};
