#include "HCSR04.h"
#include "FablabL298Driver.h"
// #include <TimerOne.h>
#include <Servo.h>

// Motor pins
const uint8_t ENA_L1 = A12;
const uint8_t IN1_L1 = 46;
const uint8_t IN2_L1 = 47;

const uint8_t ENA_L2 = A13;
const uint8_t IN1_L2 = 48;
const uint8_t IN2_L2 = 49;

const uint8_t ENA_R1 = A14;
const uint8_t IN1_R1 = 50;
const uint8_t IN2_R1 = 51;

const uint8_t ENA_R2 = A15;
const uint8_t IN1_R2 = 52;
const uint8_t IN2_R2S = 53;

//Ultra Sonic pins
byte triggerPin = 22;
byte echoCount = 4;
byte* echoPins = new byte[echoCount] { 24,26,28,30 };

#define TIMER_INTERVAL_MS  50L

void setup () {
  Serial.begin(115200);
  HCSR04.begin(triggerPin, echoPins, echoCount);
  
  // Initialize the motor
}


void loop () {
  double* distance1 = HCSR04.measureDistanceCm();
  
}