/****************************************************************************************************************************
  PWM_Multi.ino

  For ESP32, ESP32_S2, ESP32_S3, ESP32_C3 boards with ESP32 core v2.0.0+
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ESP32_FastPWM
  Licensed under MIT license

  This is pure hardware-based PWM
*****************************************************************************************************************************/
/******************************************************************************************************************************
  // All GPIO pins (but GPIO34-39) can be used to generate PWM
  // For ESP32, number of channels is 16, max 20-bit resolution
  // For ESP32_S2, ESP32_S3, number of channels is 8
  // For ESP32_C3, number of channels is 6

  LEDC Chan to Group/Channel/Timer Mapping
  ** ledc: 0  => Group: 0, Channel: 0, Timer: 0
  ** ledc: 1  => Group: 0, Channel: 1, Timer: 0
  ** ledc: 2  => Group: 0, Channel: 2, Timer: 1
  ** ledc: 3  => Group: 0, Channel: 3, Timer: 1
  ** ledc: 4  => Group: 0, Channel: 4, Timer: 2
  ** ledc: 5  => Group: 0, Channel: 5, Timer: 2
  ** ledc: 6  => Group: 0, Channel: 6, Timer: 3
  ** ledc: 7  => Group: 0, Channel: 7, Timer: 3
  ** ledc: 8  => Group: 1, Channel: 0, Timer: 0
  ** ledc: 9  => Group: 1, Channel: 1, Timer: 0
  ** ledc: 10 => Group: 1, Channel: 2, Timer: 1
  ** ledc: 11 => Group: 1, Channel: 3, Timer: 1
  ** ledc: 12 => Group: 1, Channel: 4, Timer: 2
  ** ledc: 13 => Group: 1, Channel: 5, Timer: 2
  ** ledc: 14 => Group: 1, Channel: 6, Timer: 3
  ** ledc: 15 => Group: 1, Channel: 7, Timer: 3

******************************************************************************************************************************/

#define _PWM_LOGLEVEL_       4

#include "ESP32_FastPWM.h"

#define pinToUse       16

// Max resolution is 20-bit
// Resolution 65536 (16-bit) for lower frequencies, OK @ 1K
// Resolution  4096 (12-bit) for lower frequencies, OK @ 10K
// Resolution  1024 (10-bit) for higher frequencies, OK @ 50K
// Resolution  256  ( 8-bit)for higher frequencies, OK @ 100K, 200K
// Resolution  128  ( 7-bit) for higher frequencies, OK @ 500K
int PWM_resolution    = 12;

#if ARDUINO_ESP32C3_DEV
uint32_t PWM_Pins[]   = { 8, 9, 2, 3 };
#else
uint32_t PWM_Pins[]   = { 16, 17, 19, 21 };
#endif

// Must use different group-timer for different frequency
// e.g. chan 0 (Group0-T0) and chan8(Group1-T0) OK for dif. freq, but not chan0(Group0-T0) and chan1(Group0-T0)
// timer = ((chan / 2) % 4)
// group = (chan / 8)
// For ESP32
// Group 0: channel 0-1 => timer0, channel 2-3 => timer1, channel 4-5 => timer2, channel 6-7 => timer3
// Group 1: channel 8-9 => timer0, channel 10-11 => timer1, channel 12-13 => timer2, channel 14-15 => timer3
uint32_t PWM_chan[]   = {  0,  2,  4,  6 };

// Still OK if different freq
//uint32_t PWM_chan[]   = {  0,  8,  4,  6 };
// Not OK if different freq
//uint32_t PWM_chan[]   = {  0,  1,  4,  6 };

#define NUM_OF_PINS   ( sizeof(PWM_Pins) / sizeof(uint32_t) )

float dutyCycle[] = { 10.0f, 30.0f, 50.0f, 90.0f };

float frequency[] = { 2000.0f, 3000.0f, 4000.0f, 8000.0f };

ESP32_FAST_PWM* PWM_Instance[NUM_OF_PINS];

char dashLine[] = "=====================================================================================";

void printPWMInfo(ESP32_FAST_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DC = ");
  Serial.print(PWM_Instance->getActualDutyCycle());
  Serial.print(", PWMPeriod = ");
  Serial.print(PWM_Instance->getPWMPeriod());
  Serial.print(", PWM Freq (Hz) = ");
  Serial.println(PWM_Instance->getActualFreq(), 4);
  Serial.println(dashLine);
}

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting PWM_Multi on "));
  Serial.println(ARDUINO_BOARD);
  Serial.println(ESP32_FAST_PWM_VERSION);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    PWM_Instance[index] = new ESP32_FAST_PWM(PWM_Pins[index], frequency[index], dutyCycle[index], PWM_chan[index],
                                             PWM_resolution);

    if (PWM_Instance[index])
    {
      PWM_Instance[index]->setPWM();
    }
  }

  Serial.println(dashLine);
  Serial.println("Index\tPin\tPWM_freq\tDutyCycle\tActual Freq");
  Serial.println(dashLine);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    if (PWM_Instance[index])
    {
      Serial.print(index);
      Serial.print("\t");
      Serial.print(PWM_Pins[index]);
      Serial.print("\t");
      Serial.print(frequency[index]);
      Serial.print("\t\t");
      Serial.print(dutyCycle[index]);
      Serial.print("\t\t");
      Serial.println(PWM_Instance[index]->getActualFreq(), 4);
    }
    else
    {
      Serial.println();
    }
  }

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    printPWMInfo(PWM_Instance[index]);
  }
}

void loop()
{
  //Long delay has no effect on the operation of hardware-based PWM channels
  delay(1000000);
}
