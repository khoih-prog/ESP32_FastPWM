/****************************************************************************************************************************
  PWM_manual.ino
  
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
******************************************************************************************************************************/

#define _PWM_LOGLEVEL_       4

#define UPDATE_INTERVAL       1000L

// Using setPWM_DCPercentage_manual if true
#define USING_DC_PERCENT      true

#include "ESP32_FastPWM.h"

#if ARDUINO_ESP32C3_DEV
  #define pinToUse       9
#else
  #define pinToUse       16
#endif

// Max resolution is 20-bit
// Resolution 65536 (16-bit) for lower frequencies, OK @ 1K
// Resolution  4096 (12-bit) for lower frequencies, OK @ 10K
// Resolution  1024 (10-bit) for higher frequencies, OK @ 50K
// Resolution  256  ( 8-bit)for higher frequencies, OK @ 100K, 200K
// Resolution  128  ( 7-bit) for higher frequencies, OK @ 500K
int PWM_resolution       = 10;

ESP32_FAST_PWM* PWM_Instance;

float    frequency = 1000.0f;

#if USING_DC_PERCENT
  float    dutycyclePercent = 0.0f;
  float    DCStepPercent = 5.0f;
#else
  uint16_t dutycycle = 0;
  uint16_t DCStep;
#endif

// Max resolution is 20-bit
// Resolution 65536 (16-bit) for lower frequencies,  OK @ 1K
// Resolution  4096 (12-bit) for lower frequencies,  OK @ 10K
// Resolution  1024 (10-bit) for higher frequencies, OK @ 50K
// Resolution  256  ( 8-bit) for higher frequencies, OK @ 100K, 200K
// Resolution  128  ( 7-bit) for higher frequencies, OK @ 500K
uint8_t resolution = 16;
uint8_t channel    = 0;

char dashLine[] = "=================================================================================================";


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

  delay(100);

  Serial.print(F("\nStarting PWM_manual on "));
  Serial.println(ARDUINO_BOARD);
  Serial.println(ESP32_FAST_PWM_VERSION);

  // Create a dummy instance 
  // channel 0, 16-bit resolution
  PWM_Instance = new ESP32_FAST_PWM(pinToUse, frequency, 0, channel, resolution);
  // Default channel 0, 8-bit resolution
  //PWM_Instance = new ESP32_FAST_PWM(pinToUse, frequency, 0);

  if (PWM_Instance)
  {
    PWM_Instance->setPWM();
 
    //printPWMInfo(PWM_Instance);
  }
  else
  {
    Serial.print(F("Stop here forever"));

    while (true)
      delay(10000);
  }

#if !USING_DC_PERCENT    
  // 5% steps
  DCStep = round((1 << resolution) / 20.0f);
#endif
}

void loop()
{
  static unsigned long update_timeout = UPDATE_INTERVAL;

  // Update DC every UPDATE_INTERVAL (1000) milliseconds
  if (millis() > update_timeout)
  {
#if USING_DC_PERCENT
    PWM_Instance->setPWM_DCPercentage_manual(pinToUse, dutycyclePercent);

    dutycyclePercent += DCStepPercent;

    if (dutycyclePercent > 100.0f)
      dutycyclePercent = 0.0f;
#else
    if (dutycycle > (1 << resolution))
    {
      PWM_Instance->setPWM_manual(pinToUse, (1 << resolution));
      dutycycle = 0;
    }
    else
    {
      // Funny kludge to get around ESP32 bug, adding 4 to dutycycle each loop !!!
      if (dutycycle < DCStep)
        dutycycle = 0;
  
      PWM_Instance->setPWM_manual(pinToUse, dutycycle);
      dutycycle += DCStep;
    }
#endif

    printPWMInfo(PWM_Instance);
    
    update_timeout = millis() + UPDATE_INTERVAL;
  }
}
