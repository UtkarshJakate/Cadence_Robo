#ifndef pin_map_h
#define pin_map_h

//LED Status PIN
const uint8_t LED_PIN = 13;
//Servo Pin 
const uint8_t SERVO_PIN = 12;
// Motor pins
const uint8_t ENA_L1 = 5;
const uint8_t IN1_L1 = 6;
const uint8_t IN2_L1 = 7;

const uint8_t ENA_L2 = 5;
const uint8_t IN1_L2 = 6;
const uint8_t IN2_L2 = 7;

const uint8_t ENA_R1 = 5;
const uint8_t IN1_R1 = 6;
const uint8_t IN2_R1 = 7;

const uint8_t ENA_R2 = 5;
const uint8_t IN1_R2 = 6;
const uint8_t IN2_R2 = 7;

//Ultra sonic pins
byte triggerPin = 8;//21;
byte echoCount = 2;
byte* echoPins = new byte[echoCount] { 9,10 };//, 13

#endif