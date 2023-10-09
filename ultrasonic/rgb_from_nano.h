#ifndef RGB_FROM_NANO_H
#define RGB_FROM_NANO_H
#include "pin_map.h"
#include "bot_strategy.h"

int rgb_from_nano_local_intr_flag = 0;
int rgb_from_nano_local_state = 0;

int read_rgb_intr()
{
  return rgb_from_nano_local_intr_flag;
}
void set_rgb_intr()
{
  // robo_stop();
  rgb_from_nano_local_intr_flag = 1;
}
void clear_rgb_intr()
{
  rgb_from_nano_local_intr_flag = 0;
}
int read_rgb_state()
{
  int rgb_state;
  rgb_state =  (digitalRead(RGB_D2) << 2) | (digitalRead(RGB_D1) << 1) | digitalRead(RGB_D0);
  return rgb_state;
}
void rgb_from_nano_begin()
{
  pinMode(RGB_INTR,INPUT_PULLUP);
  pinMode(RGB_D0,INPUT);
  pinMode(RGB_D1,INPUT);
  pinMode(RGB_D2,INPUT);
  attachInterrupt(digitalPinToInterrupt(RGB_INTR),set_rgb_intr,RISING);
}
#endif