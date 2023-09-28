#ifndef BOT_STRATGY_H
#define BOT_STRATGY_H

#include "rgb_sense.h"
#include "robo_driver.h"

void edge_detected_move(int);

void edge_detected_move(int rgb_state)
{
      // Serial.println("Inside switch");
      // Serial.println(rgb_state);
        switch (rgb_state){
          case 1: //R2 
            forward(30); //Forward by 3 cm
            rotate_left(135); //Rotate left by 135 degrees            
          break;
          case 2: //R1 
            backward(30); //Forward by 3 cm
            rotate_right(135); //Rotate left by 45 degrees
          break;
          case 3: //R1 & R2
            rotate_left_soft(90); //Rotate left by 45 degrees
            forward(3); //Forward by 3 cm
          break;
          case 4: //L2
            forward(30); //Forward by 3 cm
            rotate_right(135); //Rotate left by 45 degrees
          break;
         case 5: //L2 & R2
            forward(30); //Forward by 3 cm
            rotate_right(180); //Rotate left by 180 degrees
          break;
          case 8: //L1
            backward(30); //Forward by 3 cm
            rotate_right(135); //Rotate left by 45 degrees
          break;
          case 10: //L1 & R1
            backward(30); //Forward by 3 cm
            rotate_right(180); //Rotate left by 45 degrees
          break;
          case 12: //L1 & L2
            rotate_right_soft(90);
            forward(30); //Forward by 3 cm
          break;         

          default:
          break;
        }
}

#endif