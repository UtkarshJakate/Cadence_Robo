#ifndef DETECT_BOT_H
#define DETECT_BOT_H

#include "HCSR04.h"
#include "pin_map.h"

void scan_360(void);
void point_to_bot(void);


Servo myservo;

int ledState = LOW;
volatile unsigned long servo_angle = 90; // use volatile for shared variables
volatile unsigned int dir=1; // use volatile for shared variables
volatile float min_dist=500; // use volatile for shared variables
volatile int target_angle;

void servo_begin()
{
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
}
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

#endif