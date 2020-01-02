#include <Wire.h>
#include <Arduino.h>

#ifndef TINY_ADXL345_h
#define TINY_ADXL345_h

class Adxl345{
 static const uint8_t I2C_ADDRESS = 0x53;
 static const uint8_t DEVID = 0xE5; 
 /*************************** REGISTER MAP ***************************/
 static const uint8_t  R_DEVID			=0x00; // Device ID
 static const uint8_t  R_RESERVED1   	=0x01; // Reserved
 static const uint8_t  R_THRESH_TAP		=0x1D; // Tap Threshold
 static const uint8_t  R_OFSX			=0x1E; // X-Axis Offset
 static const uint8_t  R_OFSY			=0x1F; // Y-Axis Offset
 static const uint8_t  R_OFSZ			=0x20; // Z- Axis Offset
 static const uint8_t  R_DUR			=0x21; // Tap Duration
 static const uint8_t  R_LATENT			=0x22; // Tap Latency
 static const uint8_t  R_WINDOW			=0x23; // Tap Window
 static const uint8_t  R_THRESH_ACT		=0x24; // Activity Threshold
 static const uint8_t  R_THRESH_INACT	=0x25; // Inactivity Threshold
 static const uint8_t  R_TIME_INACT		=0x26; // Inactivity Time
 static const uint8_t  R_ACT_INACT_CTL	=0x27; // Axis Enable Control for Activity and Inactivity Detection
 static const uint8_t  R_THRESH_FF	    =0x28; // Free-Fall Threshold
 static const uint8_t  R_TIME_FF		=0x29; // Free-Fall Time
 static const uint8_t  R_TAP_AXES	    =0x2A; // Axis Control for Tap/Double Tap
 static const uint8_t  R_ACT_TAP_STATUS	=0x2B; // Source of Tap/Double Tap
 static const uint8_t  R_BW_RATE		=0x2C; // Data Rate and Power mode Control
 static const uint8_t  R_POWER_CTL	    =0x2D; // Power-Saving Features Control
 static const uint8_t  R_INT_ENABLE		=0x2E; // Interrupt Enable Control
 static const uint8_t  R_INT_MAP		=0x2F; // Interrupt Mapping Control
 static const uint8_t  R_INT_SOURCE		=0x30; // Source of Interrupts
 static const uint8_t  R_DATA_FORMAT	=0x31; // Data Format Control
 static const uint8_t  R_DATAX0			=0x32; // X-Axis Data 0
 static const uint8_t  R_DATAX1			=0x33; // X-Axis Data 1
 static const uint8_t  R_DATAY0			=0x34; // Y-Axis Data 0
 static const uint8_t  R_DATAY1			=0x35; // Y-Axis Data 1
 static const uint8_t  R_DATAZ0			=0x36; // Z-Axis Data 0
 static const uint8_t  R_DATAZ1			=0x37; // Z-Axis Data 1
 static const uint8_t  R_FIFO_CTL	    =0x38; // FIFO Control
 static const uint8_t  R_FIFO_STATUS	=0x39; // FIFO Status 	
  
 static void write(uint8_t rAddress, uint8_t value){
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(rAddress);
  Wire.write(value);
  Wire.endTransmission();
 }
 
 static uint8_t read(uint8_t rAddress){
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(rAddress);
  Wire.endTransmission();
  Wire.beginTransmission(I2C_ADDRESS);
  uint8_t outcome{0};  	 
  if (Wire.requestFrom(I2C_ADDRESS,uint8_t(1))==1){
	outcome = Wire.read();  
  }else{
	readError = true;
  }
  Wire.endTransmission();
  return(outcome); 
 }
 
public:
 inline static bool readError{false};
 static void init(){
	 Wire.begin();
	 write(R_POWER_CTL,0);	// Wakeup     
	 write(R_POWER_CTL,16);	// Auto_Sleep
	 write(R_POWER_CTL,8);	// Measure
 }
 static void setRangeSettings(uint8_t v){
   v &= 0b00000011; 
   write(R_DATA_FORMAT,(read(R_DATA_FORMAT)&0b11111100)|v);
 }
 
 static void setTapDetectionOnXYZ(bool x, bool y, bool z){
  uint8_t mask = x<<2|y<<1|z;
  write(R_TAP_AXES, (read(R_TAP_AXES)&0b11111000)|mask );
 }
 
 static void setTapThreshold(uint8_t v){write(R_THRESH_TAP,v);};
 static void setTapDuration(uint8_t v){write(R_DUR,v);};

//  static	void InactivityINT(bool v){setInterrupt(ADXL345_INT_INACTIVITY_BIT,v);};
//  static	void ActivityINT(bool v){setInterrupt(ADXL345_INT_ACTIVITY_BIT,v);};
//  static	void FreeFallINT(bool v){setInterrupt(ADXL345_INT_FREE_FALL_BIT,v);};
//  static	void doubleTapINT(bool v){setInterrupt(ADXL345_INT_DOUBLE_TAP_BIT,v);};
//  static	void singleTapINT(bool v){setInterrupt(ADXL345_INT_SINGLE_TAP_BIT,v);};
//  void setInterrupt(uint8_t interruptBit,bool v){setRegisterBit(ADXL345_INT_ENABLE, interruptBit, v);};
// 	
// 	 
 static uint8_t getINT_SOURCE(){return read(R_INT_SOURCE);}  
    
};

#endif