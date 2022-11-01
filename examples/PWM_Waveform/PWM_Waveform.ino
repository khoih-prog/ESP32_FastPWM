/****************************************************************************************************************************
  PWM_Waveform.ino

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
int PWM_resolution       = 12;

//creates pwm instance
ESP32_FAST_PWM* PWM_Instance;

typedef struct
{
  uint16_t level;
} PWD_Data;

// Data for 0-100%
PWD_Data PWM_data[] =
{
  {   0 },
  {   5 },
  {  10 },
  {  15 },
  {  20 },
  {  25 },
  {  30 },
  {  35 },
  {  40 },
  {  45 },
  {  50 },
  {  55 },
  {  60 },
  {  65 },
  {  70 },
  {  75 },
  {  80 },
  {  85 },
  {  90 },
  {  95 },
  { 100 },
  {  95 },
  {  90 },
  {  85 },
  {  80 },
  {  75 },
  {  70 },
  {  65 },
  {  60 },
  {  55 },
  {  50 },
  {  45 },
  {  40 },
  {  35 },
  {  30 },
  {  25 },
  {  20 },
  {  15 },
  {  10 },
  {   5 },
  {   0 },
};

#define NUM_PWM_POINTS      ( sizeof(PWM_data) / sizeof(PWD_Data) )

float frequency = 1000.0f;
float dutyCycle = 0.0f;

uint8_t channel = 0;

// You can select any value
PWD_Data PWM_data_idle = PWM_data[0];

char dashLine[] = "============================================================================================";

void printPWMInfo(ESP32_FAST_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DutyCycle = ");
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

  Serial.print(F("\nStarting PWM_Waveform on "));
  Serial.println(ARDUINO_BOARD);
  Serial.println(ESP32_FAST_PWM_VERSION);

  // Create a dummy instance
  PWM_Instance = new ESP32_FAST_PWM(pinToUse, frequency, dutyCycle, channel, PWM_resolution);

  if (PWM_Instance)
  {
    // setPWM_manual(uint8_t pin, uint16_t level)
    PWM_Instance->setPWM(pinToUse, frequency, 0);

    printPWMInfo(PWM_Instance);
  }
}

void updateDC()
{
  static uint16_t index = 0;

  static uint32_t actualDC;

  actualDC =  (uint32_t) PWM_data[index].level * (1 << PWM_resolution) / 100;

  // Mapping data according to resolution
  PWM_Instance->setPWM_manual(pinToUse, actualDC );

  // Use at low freq to check
  //printPWMInfo(PWM_Instance);

  index = (index + 1) % NUM_PWM_POINTS;
}

void check_status()
{
#define UPDATE_INTERVAL     100L

  static unsigned long update_timeout = UPDATE_INTERVAL;

  // Update DC every UPDATE_INTERVAL (100) milliseconds
  if (millis() > update_timeout)
  {
    updateDC();
    update_timeout = millis() + UPDATE_INTERVAL;
  }
}

void loop()
{
  check_status();
}
