#ifndef RGB_H
#define RGB_H

  #include <Wire.h>
  #include "Adafruit_TCS34725.h"
  #include "pin_map.h"
  #include <movingAvg.h>

  #define ENABLE_DEB 0

  #define RGB_COUNT 4
  #define AVG_INTVL 5  //Moving Avg interval
  #define RGB_RED_DET_TH 130


  movingAvg rgb_L1(AVG_INTVL);                  // define the moving average object
  movingAvg rgb_L2(AVG_INTVL);                  // define the moving average object
  movingAvg rgb_R1(AVG_INTVL);                  // define the moving average object
  movingAvg rgb_R2(AVG_INTVL);                  // define the moving average object

byte multiAddress = 0x70;
byte count = 0;
int currentTime = 0;

Adafruit_TCS34725 tcs[] = {Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X)};
byte gammatable[256];

void initColorSensors(void);
void chooseBus(uint8_t);

void rgb_begin()
{
  Wire.begin();
  initColorSensors();

  rgb_L1.begin();
  rgb_L2.begin();
  rgb_R1.begin();
  rgb_R2.begin();
}

void initColorSensors(){
    for(int i = 0; i < RGB_COUNT; i++){
      #if ENABLE_DEB
        Serial.println(i);
      #endif
        chooseBus(i);
        if (tcs[i].begin()){
          #if ENABLE_DEB
            Serial.print("Found sensor "); Serial.println(i+1);
          #endif
        } else{
          #if ENABLE_DEB
            Serial.println("No Sensor Found");
          #endif
            // while (true);
        }
    }
}

void readColors(byte sensorNum){
    chooseBus(sensorNum);
    float red, green, blue;
  
    tcs[sensorNum].getRGB(&red, &green, &blue);

  #if ENABLE_DEB
    Serial.print("R:\t"); Serial.print(int(red)); 
    Serial.print("\tG:\t"); Serial.print(int(green)); 
    Serial.print("\tB:\t"); Serial.print(int(blue));
    Serial.print(" ");
    Serial.println(sensorNum);
    Serial.print("\n");
  #endif
}

int update_rgb(void)
{
  int L1,L2,R1,R2;
 
    float red, green, blue;

      chooseBus(RGB_I2C_L1);
      tcs[RGB_I2C_L1].getRGB(&red, &green, &blue);
      L1 = int(red);      
      // L1=rgb_L1.reading(int(red));
      // Serial.print("L1: ");  Serial.println(int(red)); // Serial.print("  MA L1: ");  Serial.println(L1);

      chooseBus(RGB_I2C_L2);
      tcs[RGB_I2C_L2].getRGB(&red, &green, &blue);
      L2 = int(red); 
      // L2=rgb_L2.reading(int(red));
      //  Serial.print("L2: ");  Serial.println(int(red)); // Serial.print("  MA L2: ");  Serial.println(L2);

      chooseBus(RGB_I2C_R1);
      tcs[RGB_I2C_R1].getRGB(&red, &green, &blue);
      R1 = int(red); 
      // R1=rgb_R1.reading(int(red));
      // Serial.print("R1: ");  Serial.println(int(red)); //  Serial.print("  MA R1: ");  Serial.println(R1);

      chooseBus(RGB_I2C_R2);
      tcs[RGB_I2C_R2].getRGB(&red, &green, &blue);
      R2 = int(red); 
      // R2 =rgb_R2.reading(int(red));
      //  Serial.print("R2: ");  Serial.println(int(red)); //Serial.print("  MA R2: ");  Serial.println(R2);

      return ( (L1 > RGB_RED_DET_TH)<<3 | (L2 > RGB_RED_DET_TH)<<2 | (R1 > RGB_RED_DET_TH)<<1 | (R2 > RGB_RED_DET_TH) );   
}

    
void chooseBus(uint8_t bus){
    Wire.beginTransmission(0x70);
    Wire.write(1 << (bus+2)); // will be using 2-7 instead of 0-5 because of convience (placed better on the breadboard)
    Wire.endTransmission();
}

#endif