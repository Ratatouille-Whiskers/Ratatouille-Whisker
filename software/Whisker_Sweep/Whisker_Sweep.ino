s#include <Servo.h>

Servo servo;  // create servo object

void setup() {
  // our MG966 (clone) servo has a pulse width responce range of approximately 500-3000ms
  servo.attach(16, 500, 3000);  // attaches the servo on GIO2 to the servo object
}

void loop() {
  int pos;

  // Direction A
  for (pos = 0; pos <= 180; pos += 1) {
    servo.write(pos);              
    delay(15);
  }

  // Direction B
  for (pos = 180; pos >= 0; pos -= 1) { 
    servo.write(pos);              
    delay(15);                     
  }
}

