#include "HCSR04.h"
#include "FablabL298Driver.h"
// #include <TimerOne.h>
#include <Servo.h>
#include "bot_strategy.h"
#include "pin_map.h"
#include "robo_driver.h"
#include "rgb_sense.h"

#define DET_RADIUS 50 //Radious in which detected object will be consider as bot and will be attacked

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

  int rgb_det = update_rgb();
  if(rgb_det) //Detected edge of arena
  {
    // Serial.println("Edge detected");
    // Serial.println(rgb_det);

    edge_detected_move(rgb_det);
  }
 

  double* distances = HCSR04.measureDistanceCm();
  // Serial.println(distances[0]);
  if(distances[0]<DET_RADIUS)
  {
   //Bot detected
    robo_stop();
    robo_speed_update(40, 0); 
  }
  else
  {   // black trigger
    hard_rotate(30);
  } 
}