#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

unsigned long previousMillis = 0;
const long interval = 250; 
int servo_val = 37;
int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (servo_val == 37) {
      servo_val = 143;
      // Serial.println(" High ");
    } else {
      servo_val = 37;
      // Serial.println(" Low ");
    }

    myservo.write(servo_val);
  }
  // myservo.write(143);          
  // delay(200);
  // myservo.write(37);              
  // delay(200);
  
  // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(1);                       // waits 15ms for the servo to reach the position
  // }
  // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(1);                       // waits 15ms for the servo to reach the position
  // }
}