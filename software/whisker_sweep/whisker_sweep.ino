#include <Servo.h>

#define SERVO_PIN 16
#define REVERSE_INTERRUPT_PIN 17
#define DEFAULT_SWEEP_DELAY 15
#define FAST_SWEEP_DELAY 2

Servo servo; // create servo object
bool reverse = false;
int sweepDelay = DEFAULT_SWEEP_DELAY; // use to control the speed of the sweep

// interrupt that will reverse the direction of the sweep when triggered so that we
// avoid damaging the whisker
void reverseSweepInterrupt()
{
  reverse = true;
}

void setup()
{
  // our MG966 (clone) servo has a pulse width responce range of approximately 500-3000ms
  servo.attach(SERVO_PIN, 500, 3000); // attaches the servo on GIO2 to the servo object

  pinMode(REVERSE_INTERRUPT_PIN, INPUT_PULLDOWN);
  attachInterrupt(REVERSE_INTERRUPT_PIN, reverseSweepInterrupt, RISING);
}

void loop()
{
  int pos;
  // reset the sweep delay to the default in case we had to reverse the sweep direction to avoid damaging the whisker as faster rate
  sweepDelay = DEFAULT_SWEEP_DELAY;

  // Direction A
  for (pos = 0; pos <= 180; pos += 1)
  {
    // check if interrupt has been triggered, and reverse direction if it has
    if (reverse)
    {
      reverse = false;
      sweepDelay = FAST_SWEEP_DELAY;
      break;
    }
    servo.write(pos);
    delay(sweepDelay);
  }

  // Direction B
  for (pos = 180; pos >= 0; pos -= 1)
  {
    // check if interrupt has been triggered, and reverse direction if it has
    if (reverse)
    {
      reverse = false;
      sweepDelay = FAST_SWEEP_DELAY;
      break;
    }
    servo.write(pos);
    delay(sweepDelay);
  }
}