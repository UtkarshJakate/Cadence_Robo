#include "HCSR04.h"
#include "FablabL298Driver.h"
// #include <TimerOne.h>
#include <Servo.h>
#include "bot_strategy.h"
#include "pin_map.h"
#include "robo_driver.h"
#include "rgb_sense.h"

// int bot_speed;

void setup () {
  Serial.begin(115200);
  HCSR04.begin(triggerPin, echoPins, echoCount);
  // Initialize the motor
  robo_begin();
 //Time: 1 Sec : 1,000,000
  //  Timer1.initialize(150000);// blinkLED to run every 0.15 Sec.
  // Timer1.attachInterrupt(Servo_Update);

//   pinMode(LED_PIN, OUTPUT);
//  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
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

  int rgb_det = update_rgb();
  if(rgb_det) //Detected edge of arena
  {
    // Serial.println("Edge detected");
    // Serial.println(rgb_det);

    edge_detected_move(rgb_det);
  }
  robo_speed_update(15, 0);
  

  double* distances = HCSR04.measureDistanceCm();
  // Serial.println(distances[0]);
  if(distances[0]<50)
  {
   //Bot detected
    robo_stop();
    robo_speed_update(10, 0); 
  }
  // black trigger
  else
  {
    robo_speed_update(0, 20);
  }

}