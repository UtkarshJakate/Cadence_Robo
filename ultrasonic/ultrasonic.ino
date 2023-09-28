#include "HCSR04.h"
#include "FablabL298Driver.h"
// #include <TimerOne.h>
#include <Servo.h>
#include "pin_map.h"
#include "robo_driver.h"

//LED Status PIN
//const uint8_t LED_PIN = 13;
// //Servo Pin 
// const uint8_t SERVO_PIN = 12;
// // Motor pins
// const uint8_t ENA_L1 = 5;
// const uint8_t IN1_L1 = 6;
// const uint8_t IN2_L1 = 7;

// const uint8_t ENA_L2 = 5;
// const uint8_t IN1_L2 = 6;
// const uint8_t IN2_L2 = 7;

// const uint8_t ENA_R1 = 5;
// const uint8_t IN1_R1 = 6;
// const uint8_t IN2_R1 = 7;

// const uint8_t ENA_R2 = 5;
// const uint8_t IN1_R2 = 6;
// const uint8_t IN2_R2S = 7;

// //Ultra sonic pins
// byte triggerPin = 8;//21;
// byte echoCount = 2;
// byte* echoPins = new byte[echoCount] { 9,10 };//, 13

// Create a new instance of the Motor class
/*
FablabL298Driver motor_L1(ENA_L1, IN1_L1, IN2_L1);
FablabL298Driver motor_L2(ENA_L2, IN1_L2, IN2_L2);
FablabL298Driver motor_R1(ENA_R1, IN1_R1, IN2_R1);
FablabL298Driver motor_R2(ENA_R2, IN1_R2, IN2_R2);
*/

int bot_speed;

Servo myservo;
/*
int error=0;
void left_wheel(int value)
{
  int left_speed = bot_speed - error;

  if(left_speed<0)
  {
    motor_L1.backward();
    motor_L2.backward();
    left_speed = -left_speed;
  }
  else
  {
    motor_L1.forward();
    motor_L2.forward()
  }

uint8_t speed = constrain(left_speed, 0, 255);

  goSpeed(speed);

}
void right_wheel(int value)
{
  int left_speed = bot_speed - error;

  if(left_speed<0)
  {
    motor_R1.backward();
    motor_R2.backward();
    left_speed = -left_speed;
  }
  else
  {
    motor_R1.forward();
    motor_R2.forward()
  }

uint8_t speed = constrain(left_speed, 0, 255);

  goSpeed(speed);

}
*/
#define TIMER_INTERVAL_MS        50L

void setup () {
  Serial.begin(115200);
  HCSR04.begin(triggerPin, echoPins, echoCount);
  // Initialize the motor
  motor_L1.begin();
  motor_L1.setMin(255);
  motor_L1.setMax(255);

 //Time: 1 Sec : 1,000,000
  //  Timer1.initialize(150000);// blinkLED to run every 0.15 Sec.
  // Timer1.attachInterrupt(Servo_Update);

  pinMode(LED_PIN, OUTPUT);
 myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
}

int ledState = LOW;
volatile unsigned long servo_angle = 90; // use volatile for shared variables
volatile unsigned int dir=1; // use volatile for shared variables
volatile float min_dist=500; // use volatile for shared variables
volatile int target_angle;

void Servo_Update(void)
{ if (ledState == LOW)
  {
    ledState = HIGH;
   // blinkCount = blinkCount + 1; // increase when LED turns on
  }
  else {
    ledState = LOW;
  }
  digitalWrite(LED_PIN, ledState);

  myservo.write(servo_angle);
  if(dir)
  {
    servo_angle++;
  }else
  {
    servo_angle--;
  }
  if(servo_angle>150)
  {
    dir = 0;
    min_dist=500;
    
    Serial.print(target_angle);
    Serial.print(" Degree");
    Serial.println("");
  }
  else if(servo_angle < 30)
  {
    dir = 1;
    min_dist=500;
  }

  double* distance1 = HCSR04.measureDistanceCm();
  if(distance1[0]<100)
  {
    if(distance1[0]<min_dist)
    {   
      min_dist = distance1[0];
      target_angle = servo_angle;
    }
  }

}
void loop () {
  // double* distances = HCSR04.measureDistanceCm();
  
  // for (int i = 0; i < echoCount; i++) {
  //   if (i > 0) Serial.print(" | ");
  //   Serial.print(i + 1);
  //   Serial.print(": ");
  //   Serial.print(distances[i]);
  //   Serial.print(" cm");
  // }
  
  // Serial.println("");
  // delay(100);

    // Move the motor forward at 50% speed
  motor_L1.forward();
  motor_L1.goPercentage(50);
  // delay(100);

  // Stop the motor
  motor_L1.stop();


  Servo_Update();

}