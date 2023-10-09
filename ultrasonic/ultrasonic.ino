#include "HCSR04.h"
#include "FablabL298Driver.h"
// #include <TimerOne.h>
#include <Servo.h>
#include "bot_strategy.h"
#include "pin_map.h"
#include "robo_driver.h"
#include "rgb_sense.h"
#include "rgb_from_nano.h"

// #define DET_RADIUS 50 //Radious in which detected object will be consider as bot and will be attacked



void setup () {
  // Serial.begin(600);
  HCSR04.begin(triggerPin, echoPins, echoCount);
  //Inititialize RGB from Nano
  rgb_from_nano_begin();
  // Initialize the motor
  robo_begin();
}


void loop () {

unsigned long fn_time;

  // fn_time = millis();
  // int rgb_det = update_rgb();
  // if(rgb_det) //Detected edge of arena
  // {
  //   // Serial.println("Edge detected");
  //   // Serial.println(rgb_det);

  //   edge_detected_move(rgb_det);
  // }
  // fn_time= millis() - fn_time;
  // Serial.print("RGB:");
  // Serial.print(fn_time);


if(read_rgb_intr())
{
  edge_detected_move(read_rgb_state());

  clear_rgb_intr();
}

  // fn_time = millis();

  double* distances = HCSR04.measureDistanceCm();

  // fn_time= millis() - fn_time;
  // Serial.print("ultra:");
  // Serial.print(fn_time);

  // Serial.print("Ultra1:");
  // Serial.print(distances[0]);
  // Serial.print(",Ultra2:");
  // Serial.print(distances[1]);
  // Serial.print(",Ultra3:");
  // Serial.print(distances[2]);
  // Serial.print(",Ultra4:");
  // Serial.println(distances[3]);
  // delay(1000);

  // if(distances[ultra_idx_b]<DEF_RADIUS)
  if(distances[ultra_idx_b]<DEF_DET_RADIUS)
  {
    update_const_rot_dir(TURN_RIGHT);
    hard_rotate(99 * read_const_rot_dir());
    delay(100);//
  }
  else
  if(distances[ultra_idx_f]<DET_RADIUS)
  {
   //Bot detected
    robo_stop();
   //attack 
    robo_speed_update(CONST_FWD_SPEED, 0); 
  }
  else
  {   // Track other robot
    hard_rotate(CONST_ROT_SPEED * read_const_rot_dir());
  } 

}