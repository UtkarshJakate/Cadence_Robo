// Setting up 6 TCS34725 sensors together and reading their output values
// TCA9548A
#include <Wire.h>

#include "Adafruit_TCS34725.h"

#define intPin 10     //--> Mega IntPin D18
#define data0 7       //--> Mega D15
#define data1 8       //--> Mega D16
#define data2 9       //--> Mega D17

int dataLine[2][4]={  0, 1, 2, 3,
                      4, 5, 6, 7  };

bool StatusChanged=0;
bool previous_sensor = 0;
int LastData=8;
bool s0, s1, s2, s3;

#define COUNT 4
byte multiAddress = 0x70;
byte count = 0;
int currentTime = 0;

char data[4][3] = {{'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'}};

Adafruit_TCS34725 tcs[] = {Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X)};
byte gammatable[256];

void setup(){
    // Serial.begin(9600);
    Wire.begin();
    Wire.setClock(400*1000);
    pinMode(intPin, OUTPUT);
    pinMode(data0, OUTPUT);
    pinMode(data1, OUTPUT);
    pinMode(data2, OUTPUT);

    for(int i =0; i < 256; i++){
        float x = i;
        x /= 255;
        x = pow(x, 2.5);
        x *= 255;
        gammatable[i] = x;
    }
    initColorSensors();
}


void loop(){
    for(int i = 0; i < sizeof(data); i++){ // get all colors... not necessary right now 
        readColors(i);
    }    
    // int start_tick = millis();
    for(int i = 0; i < COUNT; i++){
        readColors(i);
        // delay(10);
    }
    // int stop_tick = millis();
    // Serial.println( stop_tick - start_tick );
}
void initColorSensors(){
    for(int i = 0; i < COUNT; i++){
        Serial.println(i);
        chooseBus(i);
        if (tcs[i].begin()){
            Serial.print(" Found sensor "); Serial.println(i+1);
        } else{
            Serial.println(" No Sensor Found");
            // while (true);
        }
    }
}
void readColors(byte sensorNum){
    chooseBus(sensorNum);
    float red, green, blue;
  
    tcs[sensorNum].setInterrupt(false);  // turn on LED
    // delay(60);  // takes 50ms to read
    tcs[sensorNum].getRGB(&red, &green, &blue);
    tcs[sensorNum].setInterrupt(true);  // turn off LED

    // Serial.print("R:\t");    Serial.print(int(red)); 
    // Serial.print("\tG:\t");  Serial.print(int(green)); 
    // Serial.print("\tB:\t");  Serial.print(int(blue));
    // Serial.print(" ");
    // Serial.println(sensorNum);
    
    // Serial.print("\n");

    /*if(int(red)>130){
        switch(sensorNum){
        case 0: s0=1; 
                break;
        case 1: s1=1; 
                break;
        case 2: s2=1; 
                break;
        case 3: s3=1; 
                break;
        default: s0=s1=s2=s3=0;  
        } 
      else{
        switch(sensorNum){
        case 0: s0=0; 
                break;
        case 1: s1=0; 
                break;
        case 2: s2=0; 
                break;
        case 3: s3=0; 
                break;
        default: s0=s1=s2=s3=0;
        }
    }*/

    updateMega(int(red), sensorNum);
}

void updateMega(int red_val, int sensorNum_val){
    if(int(red_val)>130)
    {
      digitalWrite(data0, (sensorNum_val&1));
      digitalWrite(data1, ((sensorNum_val>>1)&1));
      digitalWrite(data2, dataLine[previous_sensor][sensorNum_val]>>2);
      digitalWrite(intPin, 1);
      delay(10);
      digitalWrite(intPin, 0);

      // if(LastData!=dataLine[previous_sensor][sensorNum_val]){
      //   StatusChanged=1;
      //   LastData=dataLine[previous_sensor][sensorNum_val];
      // }

      // Serial.print(sensorNum_val&1);
      // Serial.print((sensorNum_val>>1)&1);
      // Serial.print(int(dataLine[previous_sensor][sensorNum_val]>>2));
      // Serial.println(int(dataLine[previous_sensor][sensorNum_val]));

      previous_sensor=1;
    }
    else
      previous_sensor=0;

    // if(StatusChanged){      
    //   digitalWrite(intPin, 1);
    //   delay(10);
    //   digitalWrite(intPin, 0);
    //   StatusChanged=0;
    // }
}


void chooseBus(uint8_t bus){
    Wire.beginTransmission(0x70);
    Wire.write(1 << (bus+2)); // will be using 2-7 instead of 0-5 because of convience (placed better on the breadboard)
    Wire.endTransmission();
}