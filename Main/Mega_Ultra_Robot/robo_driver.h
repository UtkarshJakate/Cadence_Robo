#ifndef ROBO_DRIVER_H
#define ROBO_DRIVER_H

#include "Arduino.h"
#include "FablabL298Driver.h"
#include "pin_map.h"

#define bot_speed_at_75 (1/1000)  //cm per milisec


#define motor_perc1 50
#define bot_speed_at_perc1 27 //(2000/73)  //inverse of cm per milisec
#define bot_rot_speed_at_perc1 (9440/(4*360))  //inverse of degrees per milisec

#define motor_perc2 50
#define bot_speed_at_perc2 27 //(2000/73)  //inverse of cm per milisec
#define bot_rot_speed_at_perc2 (9440/(4*360))  //inverse of degrees per milisec


// Create a new instance of the Motor class
FablabL298Driver motor_L1(ENA_L1, IN1_L1, IN2_L1);
FablabL298Driver motor_L2(ENA_L2, IN1_L2, IN2_L2);
FablabL298Driver motor_R1(ENA_R1, IN1_R1, IN2_R1);
FablabL298Driver motor_R2(ENA_R2, IN1_R2, IN2_R2);

void forward(int);
void backward(int);
void rotate_right(int);
void rotate_left(int);
void rotate_right_soft(int);
void rotate_left_soft(int);

void left_wheel(int bot_speed,int error)
{
  int left_speed = bot_speed + error;

  if(left_speed<0)
  {
    motor_L1.backward();
    motor_L2.backward();
    left_speed = -left_speed;
  }
  else
  {
    motor_L1.forward();
    motor_L2.forward();
  }

uint8_t speed = (uint8_t) constrain(left_speed, 0, 100);

  motor_L1.goPercentage(speed);
  motor_L2.goPercentage(speed);

}
void right_wheel(int bot_speed,int error)
{
  int right_speed = bot_speed - error;

  if(right_speed<0)
  {
    motor_R1.backward();
    motor_R2.backward();
    right_speed = -right_speed;
  }
  else
  {
    motor_R1.forward();
    motor_R2.forward();
  }

uint8_t speed = (uint8_t) constrain(right_speed, 0, 100);

  motor_R1.goPercentage(speed);
  motor_R2.goPercentage(speed);

}

void robo_speed_update(int bot_speed, int error)
{
  left_wheel(bot_speed, error);
  right_wheel(bot_speed, error);
}

hard_rotate(int bot_speed) //+Ve value will turn right
{
  left_wheel(0,bot_speed);
  right_wheel(0,bot_speed);
}
 void robo_stop(void)
 {
  motor_L1.stop();
  motor_L2.stop();
  motor_R1.stop();
  motor_R2.stop();
 }
void robo_begin(void) 
{
  motor_L1.begin();
  motor_L1.setMin(53);
  motor_L1.setMax(255);

  motor_L2.begin();
  motor_L2.setMin(53);
  motor_L2.setMax(255);

  motor_R1.begin();
  motor_R1.setMin(50);
  motor_R1.setMax(255);

  motor_R2.begin();
  motor_R2.setMin(65);
  motor_R2.setMax(255);
}


void forward_cm(int dist,int speed)
{
  robo_speed_update( speed, 0);
  delay( (int) (( (float) dist*bot_speed_at_perc1*speed)/(float)motor_perc1) );
  robo_stop();
}
void backward_cm(int dist,int speed)
{
  robo_speed_update( -speed, 0);
  // delay(dist*bot_speed_at_perc1*speed/motor_perc1);
  delay( (int) (( (float) dist*bot_speed_at_perc1*speed)/(float)motor_perc1) );
  robo_stop();
}

void rotate_right_degree(int angle, int speed)
{
  robo_speed_update( 0, speed);//motor_perc1);
    delay(  (int) (( (float) angle*bot_rot_speed_at_perc1*speed)/((float)motor_perc1) )  );
  robo_stop();
}

void rotate_left_degree(int angle, int speed)
{
  robo_speed_update( 0, -speed);//motor_perc1);
    // delay(angle*bot_rot_speed_at_perc1*speed/motor_perc1);
    delay(  (int) (( (float) angle*bot_rot_speed_at_perc1*speed)/((float)motor_perc1) )  );
  robo_stop();
}
void rotate_right_soft_degree(int angle,int speed)
{
  rotate_right_degree(angle,speed);
}
void rotate_left_soft_degree(int angle,int speed)
{
  rotate_left_degree(angle,speed);
}

#endif