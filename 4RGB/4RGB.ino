// Setting up 6 TCS34725 sensors together and reading their output values
// TCA9548A

#include <Wire.h>

#include "Adafruit_TCS34725.h"

#define  inPin  7
#define  rPin   8
#define  gPin   9
#define  bPin   10

#define COUNT 4
byte multiAddress = 0x70;
byte count = 0;
int currentTime = 0;

char data[6][3] = {{'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'}};
Adafruit_TCS34725 tcs[] = {Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X)};
byte gammatable[256];

void setup(){
    Serial.begin(9600);
    Wire.begin();
    pinMode(inPin, INPUT_PULLUP);
    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);
    // gammatable for more color accuracy when outputting on LED
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
    //for(int i = 0; i < sizeof(data); i++){ // get all colors... not necessary right now 
    //    readColors(i);
    //}
    for(int i = 0; i < COUNT; i++){
        readColors(i);
        delay(1000);
    }
    
}
void initColorSensors(){
    for(int i = 0; i < COUNT; i++){
        Serial.println(i);
        chooseBus(i);
        if (tcs[i].begin()){
            Serial.print("Found sensor "); Serial.println(i+1);
        } else{
            Serial.println("No Sensor Found");
            // while (true);
        }
    }
}
void readColors(byte sensorNum){
    chooseBus(sensorNum);
    float red, green, blue;
  
    tcs[sensorNum].setInterrupt(false);  // turn on LED
    delay(60);  // takes 50ms to read
    tcs[sensorNum].getRGB(&red, &green, &blue);
    tcs[sensorNum].setInterrupt(true);  // turn off LED

    Serial.print("R:\t"); Serial.print(int(red)); 
    Serial.print("\tG:\t"); Serial.print(int(green)); 
    Serial.print("\tB:\t"); Serial.print(int(blue));
    Serial.print(" ");
    Serial.println(sensorNum);
    Serial.print("\n");

}
    
void chooseBus(uint8_t bus){
    Wire.beginTransmission(0x70);
    Wire.write(1 << (bus+2)); // will be using 2-7 instead of 0-5 because of convience (placed better on the breadboard)
    Wire.endTransmission();
}
void displayLED(uint16_t r, uint16_t g, uint16_t b){
    if (r > 255 || g > 255 || b > 255){
        analogWrite(rPin, 0);
        analogWrite(gPin, 0);
        analogWrite(bPin, 0);
    } else{
        analogWrite(rPin, gammatable[(int)r]);
        analogWrite(gPin, gammatable[(int)g]);
        analogWrite(bPin, gammatable[(int)b]); 
    }
    
}
