/****************************************************************************************************************************
  PWM_StepperControl.ino
  For ESP32, ESP32_S2, ESP32_S3, ESP32_C3 boards with ESP32 core v2.0.0+
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ESP32_FastPWM
  Licensed under MIT license

  This is pure hardware-based PWM

  Credits of Paul van Dinther (https://github.com/dinther). Check https://github.com/khoih-prog/RP2040_PWM/issues/16
*****************************************************************************************************************************/
/******************************************************************************************************************************
  // All GPIO pins (but GPIO34-39) can be used to generate PWM
  // For ESP32, number of channels is 16, max 20-bit resolution
  // For ESP32_S2, ESP32_S3, number of channels is 8
  // For ESP32_C3, number of channels is 6
******************************************************************************************************************************/

// Use with Stepper-Motor driver, such as TMC2209

#define _PWM_LOGLEVEL_       4

#include "ESP32_FastPWM.h"

#if ARDUINO_ESP32C3_DEV
  #define STEP_PIN       9
#else
  #define STEP_PIN       16
#endif

#define DIR_PIN          4

// Max resolution is 20-bit
// Resolution 65536 (16-bit) for lower frequencies, OK @ 1K
// Resolution  4096 (12-bit) for lower frequencies, OK @ 10K
// Resolution  1024 (10-bit) for higher frequencies, OK @ 50K
// Resolution  256  ( 8-bit)for higher frequencies, OK @ 100K, 200K
// Resolution  128  ( 7-bit) for higher frequencies, OK @ 500K
int PWM_resolution = 10;

//creates pwm instance
ESP32_FAST_PWM* stepper;

void setSpeed(int speed)
{
  if (speed == 0)
  {
    // Use DC = 0 to stop stepper
    stepper->setPWM(STEP_PIN, 500, 0);
  }
  else
  {
    //  Set the frequency of the PWM output and a duty cycle of 50%
    digitalWrite(DIR_PIN, (speed < 0));
    stepper->setPWM(STEP_PIN, abs(speed), 50);
  }
}

void setup() 
{
  pinMode(DIR_PIN, OUTPUT);
  
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(100);

  Serial.print(F("\nStarting PWM_StepperControl on "));
  Serial.println(ARDUINO_BOARD);
  Serial.println(ESP32_FAST_PWM_VERSION);
  
  // Create PWM object and passed just a random frequency of 500
  // The duty cycle is how you turn the motor on and off
  stepper = new ESP32_FAST_PWM(STEP_PIN, 500, 0);
}

void loop() 
{
  setSpeed(1000);
  delay(3000);

  // Stop before reversing
  setSpeed(0);
  delay(3000);

  // Reversing
  setSpeed(-500);
  delay(3000);

  // Stop before reversing
  setSpeed(0);
  delay(3000);
}
