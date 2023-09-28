#include "HCSR04.h"
#include "FablabL298Driver.h"
// #include <TimerOne.h>
#include <Servo.h>

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
const uint8_t IN2_R2S = 7;

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
  Serial.print(distance1[0]);
}