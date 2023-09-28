#include "Arduino.h"
#include "FablabL298Driver.h"
#include "pin_map.h"

// Create a new instance of the Motor class
FablabL298Driver motor_L1(ENA_L1, IN1_L1, IN2_L1);
FablabL298Driver motor_L2(ENA_L2, IN1_L2, IN2_L2);
FablabL298Driver motor_R1(ENA_R1, IN1_R1, IN2_R1);
FablabL298Driver motor_R2(ENA_R2, IN1_R2, IN2_R2);


void left_wheel(int bot_speed,int error)
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
    motor_L2.forward();
  }

uint8_t speed = constrain(left_speed, 0, 255);

  motor_L1.goSpeed(speed);
  motor_L2.goSpeed(speed);

}
void right_wheel(int bot_speed,int error)
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
    motor_R2.forward();
  }

uint8_t speed = constrain(left_speed, 0, 255);

  motor_R1.goSpeed(speed);
  motor_R2.goSpeed(speed);

}
