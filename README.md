# ESP32_FastPWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP32_FastPWM.svg?)](https://www.ardu-badge.com/ESP32_FastPWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP32_FastPWM.svg)](https://github.com/khoih-prog/ESP32_FastPWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP32_FastPWM/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP32_FastPWM.svg)](http://github.com/khoih-prog/ESP32_FastPWM/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Why do we need this ESP32_FastPWM library](#why-do-we-need-this-ESP32_FastPWM-library)
  * [Features](#features)
  * [Why using hardware-based PWM is better](#why-using-hardware-based-pwm-is-better)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [More useful Information](#more-useful-information)
* [Usage](#usage)
  * [1. Create PWM Instance with Pin, Frequency, dutycycle, channel (default = 0) and PWM_resolution (default = 8)](#1-create-pwm-instance-with-pin-frequency-dutycycle-channel-default--0-and-pwm_resolution-default--8)
  * [2. Initialize PWM Instance](#2-Initialize-PWM-Instance)
  * [3. Set or change PWM frequency or dutyCycle](#3-set-or-change-PWM-frequency-or-dutyCycle)
  * [4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation](#4-Set-or-change-PWM-frequency-and-dutyCycle-manually-and-efficiently-in-waveform-creation)
* [Examples](#examples)
  * [ 1. PWM_Basic](examples/PWM_Basic)
  * [ 2. PWM_DynamicDutyCycle](examples/PWM_DynamicDutyCycle) 
  * [ 3. PWM_DynamicDutyCycle_Int](examples/PWM_DynamicDutyCycle_Int)
  * [ 4. PWM_DynamicFreq](examples/PWM_DynamicFreq)
  * [ 5. PWM_Multi](examples/PWM_Multi)
  * [ 6. PWM_MultiChannel](examples/PWM_MultiChannel)
  * [ 7. PWM_Waveform](examples/PWM_Waveform)
  * [ 8. PWM_StepperControl](examples/PWM_StepperControl) **New**
  * [ 9. PWM_manual](examples/PWM_manual) **New**
* [Example PWM_Multi](#example-PWM_Multi)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. PWM_DynamicDutyCycle on ESP32_DEV](#1-PWM_DynamicDutyCycle-on-ESP32_DEV)
  * [2. PWM_Multi on ESP32_DEV](#2-PWM_Multi-on-ESP32_DEV)
  * [3. PWM_DynamicFreq on ESP32S3_DEV](#3-PWM_DynamicFreq-on-ESP32S3_DEV)
  * [4. PWM_Waveform on ESP32S2_DEV](#4-PWM_Waveform-on-ESP32S2_DEV)
  * [5. PWM_Waveform on ESP32C3_DEV](#5-PWM_Waveform-on-ESP32C3_DEV)
  * [6. PWM_Waveform on ESP32S3_DEV](#6-PWM_Waveform-on-ESP32S3_DEV)
  * [7. PWM_manual on ESP32_DEV](#7-PWM_manual-on-ESP32_DEV)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---


### Why do we need this [ESP32_FastPWM library](https://github.com/khoih-prog/ESP32_FastPWM)

### Features

This hardware-based PWM library, a wrapper and enhancement around ESP32-core `ledc` code, enables you to use Hardware-PWM on `ESP32, ESP32_S2, ESP32_S3 and ESP32_C3` boards to create and output PWM. These purely hardware-based PWM channels can generate very high PWM frequencies, depending on CPU clock and acceptable accuracy. The maximum resolution can be 20-bit with very low frequencies. Normally 8, 12 or 16-bit resolution is good enough.

```cpp
// Max resolution is 20-bit
// Resolution 65536 (16-bit) for lower frequencies, OK @ 1K
// Resolution  4096 (12-bit) for lower frequencies, OK @ 10K
// Resolution  1024 (10-bit) for higher frequencies, OK @ 50K
// Resolution  256  ( 8-bit)for higher frequencies, OK @ 100K, 200K
// Resolution  128  ( 7-bit) for higher frequencies, OK @ 500K
```

This library is using the **same or similar functions** as other FastPWM libraries, as follows, to enable you to **port your PWM code easily between platforms**

 1. [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM)
 2. [**AVR_PWM**](https://github.com/khoih-prog/AVR_PWM)
 3. [**megaAVR_PWM**](https://github.com/khoih-prog/megaAVR_PWM)
 4. [**ESP32_FastPWM**](https://github.com/khoih-prog/ESP32_FastPWM)
 5. [**SAMD_PWM**](https://github.com/khoih-prog/SAMD_PWM)
 6. [**SAMDUE_PWM**](https://github.com/khoih-prog/SAMDUE_PWM)
 7. [**nRF52_PWM**](https://github.com/khoih-prog/nRF52_PWM)
 8. [**Teensy_PWM**](https://github.com/khoih-prog/Teensy_PWM)
 9. [**ATtiny_PWM**](https://github.com/khoih-prog/ATtiny_PWM)
10. [**Dx_PWM**](https://github.com/khoih-prog/Dx_PWM)
11. [**Portenta_H7_PWM**](https://github.com/khoih-prog/Portenta_H7_PWM)
12. [**MBED_RP2040_PWM**](https://github.com/khoih-prog/MBED_RP2040_PWM)
13. [**nRF52_MBED_PWM**](https://github.com/khoih-prog/nRF52_MBED_PWM)
14. [**STM32_PWM**](https://github.com/khoih-prog/STM32_PWM)

---

The most important feature is they're purely hardware-based PWM channels. Therefore, their operations are **not blocked by bad-behaving software functions / tasks**.

This important feature is absolutely necessary for mission-critical tasks. These hardware PWM-channels, still work even if other software functions are blocking. Moreover, they are much more precise (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to control external systems (Servo, etc.) requiring better accuracy.

New efficient `setPWM_manual()` and `setPWM_DCPercentage_manual()` functions enable waveform creation using PWM.

The [**PWM_Multi**](examples/PWM_Multi) example will demonstrate the usage of multichannel PWM using multiple Hardware-PWM blocks (slices). The 4 independent Hardware-PWM channels are used **to control 4 different PWM outputs**, with totally independent frequencies and dutycycles on `ESP32`.

Being hardware-based PWM, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.


### Why using hardware-based PWM is better

Imagine you have a system with a **mission-critical** function, controlling a robot or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use `hardware-based PWM`.

These hardware-based PWM channels still work even if other software functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software-based PWMs, using millis() or micros().

Functions using normal software-based PWMs, relying on loop() and calling millis(), won't work if the `loop()` or `setup()` is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

---

### Currently supported Boards

1. ESP32 boards, such as `ESP32_DEV`, etc.
2. ESP32S2-based boards, such as `ESP32S2_DEV`, `ESP32_S2 Saola`, Adafruit QTPY_ESP32S2, etc.
3. ESP32C3-based boards, such as `ESP32C3_DEV`, etc.
4. ESP32_S3 (ESP32S3_DEV, ESP32_S3_BOX, UM TINYS3, UM PROS3, UM FEATHERS3, FEATHER_ESP32S3_NOPSRAM and QTPY_ESP32S3_NOPSRAM, etc.)


---
---

## Prerequisites

1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
2. [`ESP32 Core 2.0.6+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/).



---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**ESP32_FastPWM**](https://github.com/khoih-prog/ESP32_FastPWM), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP32_FastPWM.svg?)](https://www.ardu-badge.com/ESP32_FastPWM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**ESP32_FastPWM**](https://github.com/khoih-prog/ESP32_FastPWM) page.
2. Download the latest release `ESP32_FastPWM-main.zip`.
3. Extract the zip file to `ESP32_FastPWM-main` directory 
4. Copy whole `ESP32_FastPWM-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**ESP32_FastPWM** library](https://registry.platformio.org/libraries/khoih-prog/ESP32_FastPWM) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/ESP32_FastPWM/installation). Search for **ESP32_FastPWM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---


### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- `ADC1` controls ADC function for pins **GPIO32-GPIO39**
- `ADC2` controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In `ADC2`, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the `ADC2`, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the `ADC2`, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use `ADC2` for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use `ADC2` with WiFi/BlueTooth (BT/BLE).
- Use `ADC1`, and pins **GPIO32-GPIO39**
- If somehow it's a must to use those pins serviced by `ADC2` (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE)

---
---

## More useful Information

### ESP32 Hardware Timers

  - **The ESP32, ESP32_S2 and ESP32_S3 has two timer groups, each one with two general purpose hardware timers.**
  - **The ESP32_C3 has two timer groups, each one with only one general purpose hardware timer.**
  - All the timers are based on **64-bit counters (except 54-bit counter for ESP32_S3 counter) and 16-bit prescalers.**
  - The timer counters can be configured to count up or down and support automatic reload and software reload.
  - They can also generate alarms when they reach a specific value, defined by the software. 
  - The value of the counter can be read by the software program.

---
---

## Usage

Before using any PWM `Timer` and `channel`, you have to make sure the `Timer` and `channel` has not been used by any other purpose.

```cpp
// Max resolution is 20-bit
// Resolution 65536 (16-bit) for lower frequencies, OK @ 1K
// Resolution  4096 (12-bit) for lower frequencies, OK @ 10K
// Resolution  1024 (10-bit) for higher frequencies, OK @ 50K
// Resolution  256  ( 8-bit)for higher frequencies, OK @ 100K, 200K
// Resolution  128  ( 7-bit) for higher frequencies, OK @ 500K

///////////////////////////////////////////////////////////////////

// All GPIO pins (but GPIO34-39) can be used to generate PWM
// For ESP32, number of channels is 16, max 20-bit resolution
// For ESP32_S2, ESP32_S3, number of channels is 8, max 20-bit resolution
// For ESP32_C3, number of channels is 6, max 20-bit resolution
```

#### 1. Create PWM Instance with Pin, Frequency, dutycycle, channel (default = 0) and PWM_resolution (default = 8)

```cpp
ESP32_FAST_PWM* PWM_Instance;

PWM_Instance = new ESP32_FAST_PWM(pinToUse, frequency, dutyCycle, channel, PWM_resolution);
```

#### 2. Initialize PWM Instance

```cpp
if (PWM_Instance)
{
  PWM_Instance->setPWM();
}
```

#### 3. Set or change PWM frequency or dutyCycle

To use `float new_dutyCycle`

```cpp
PWM_Instance->setPWM(PWM_Pins, new_frequency, new_dutyCycle);
```

such as 

```cpp
dutyCycle = 10.0f;
  
Serial.print(F("Change PWM DutyCycle to ")); Serial.println(dutyCycle);
PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);
```

---

To use `uint32_t new_dutyCycle` = `(real_dutyCycle * 65536) / 100`


```cpp
PWM_Instance->setPWM_Int(PWM_Pins, new_frequency, new_dutyCycle);
```

such as for `real_dutyCycle = 50%`

```cpp
// 50% dutyCycle = (real_dutyCycle * 65536) / 100
dutyCycle = 32768;

Serial.print(F("Change PWM DutyCycle to (%) "));
Serial.println((float) dutyCycle * 100 / 65536);
PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```

for `real_dutyCycle = 50%`

```cpp
// 20% dutyCycle = (real_dutyCycle * 65536) / 100
dutyCycle = 13107;

Serial.print(F("Change PWM DutyCycle to (%) "));
Serial.println((float) dutyCycle * 100 / 65536);
PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```

#### 4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation

Function prototype

```cpp
bool setPWM_manual(const uint8_t& pin, const uint16_t& DCValue);
bool setPWM_DCPercentage_manual(const uint8_t& pin, const float& DCPercentage);
```

Need to call only once for each pin


```cpp
PWM_Instance->setPWM(PWM_Pins, frequency, dutyCycle);
```

after that, if just changing `dutyCycle` / `level`, use 

```cpp
// For 50.0f dutycycle
new_level = 50.0f * ( 1 << PWM_Instance->getResolution() ) / 100.0f ;
PWM_Instance->setPWM_manual(PWM_Pins, new_level);
```

or better and much easier to use

```cpp
new_DCPercentage = 50.0f;
PWM_Instance->setPWM_DCPercentage_manual(PWM_Pins, new_DCPercentage);
```

---
---

### Examples: 

 1. [PWM_Basic](examples/PWM_Basic)
 2. [PWM_DynamicDutyCycle](examples/PWM_DynamicDutyCycle)
 3. [PWM_DynamicDutyCycle_Int](examples/PWM_DynamicDutyCycle_Int)
 4. [PWM_DynamicFreq](examples/PWM_DynamicFreq)
 5. [PWM_Multi](examples/PWM_Multi)
 6. [PWM_MultiChannel](examples/PWM_MultiChannel)
 7. [PWM_Waveform](examples/PWM_Waveform)
 8. [PWM_StepperControl](examples/PWM_StepperControl) **New**
 9. [PWM_manual](examples/PWM_manual) **New**

 
---
---

### Example [PWM_Multi](examples/PWM_Multi)

https://github.com/khoih-prog/ESP32_FastPWM/blob/09ea7daef68ab6660d298e9ef2e20f55d906416c/examples/PWM_Multi/PWM_Multi.ino#L12-L153


---
---

### Debug Terminal Output Samples

### 1. PWM_DynamicDutyCycle on ESP32_DEV

The following is the sample terminal output when running example [PWM_DynamicDutyCycle](examples/PWM_DynamicDutyCycle) on *ESP32_DEV**, to demonstrate the ability to provide high PWM frequencies and ability to change DutyCycle `on-the-fly`.


```cpp
Starting PWM_DynamicDutyCycle on ESP32_DEV
ESP32_FastPWM v1.1.0
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 8 , LEDC_CHANNELS = 16 , LEDC_MAX_BIT_WIDTH = 20
[PWM] ESP32_FastPWM: _dutycycle = 32768
[PWM] setPWM_Int: _dutycycle = 128 , DC % = 50.00
=====================================================================================
Change PWM DutyCycle to 90.00
[PWM] setPWM: _dutycycle = 58982 , frequency = 5000.00
[PWM] setPWM_Int: _dutycycle = 230 , DC % = 89.84
=====================================================================================
Actual data: pin = 16, PWM DC = 89.84, PWMPeriod = 200.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 20.00
[PWM] setPWM: _dutycycle = 13107 , frequency = 5000.00
[PWM] setPWM_Int: _dutycycle = 51 , DC % = 19.92
=====================================================================================
Actual data: pin = 16, PWM DC = 19.92, PWMPeriod = 200.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 90.00
[PWM] setPWM: _dutycycle = 58982 , frequency = 5000.00
[PWM] setPWM_Int: _dutycycle = 230 , DC % = 89.84
=====================================================================================
Actual data: pin = 16, PWM DC = 89.84, PWMPeriod = 200.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
```

---

### 2. PWM_Multi on ESP32_DEV

The following is the sample terminal output when running example [**PWM_Multi**](examples/PWM_Multi) on **ESP32_DEV**, to demonstrate the ability to provide high PWM frequencies on multiple `PWM-capable` pins.

```cpp
Starting PWM_Multi on ESP32_DEV
ESP32_FastPWM v1.1.0
[PWM] ESP32_FastPWM: new _channel = 0
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 8 , LEDC_CHANNELS = 16 , LEDC_MAX_BIT_WIDTH = 20
[PWM] ESP32_FastPWM: _dutycycle = 6553
[PWM] setPWM_Int: _dutycycle = 409 , DC % = 9.99
[PWM] ESP32_FastPWM: new _channel = 2
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 8 , LEDC_CHANNELS = 16 , LEDC_MAX_BIT_WIDTH = 20
[PWM] ESP32_FastPWM: _dutycycle = 19660
[PWM] setPWM_Int: _dutycycle = 1228 , DC % = 29.98
[PWM] ESP32_FastPWM: new _channel = 4
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 8 , LEDC_CHANNELS = 16 , LEDC_MAX_BIT_WIDTH = 20
[PWM] ESP32_FastPWM: _dutycycle = 32768
[PWM] setPWM_Int: _dutycycle = 2048 , DC % = 50.00
[PWM] ESP32_FastPWM: new _channel = 6
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 8 , LEDC_CHANNELS = 16 , LEDC_MAX_BIT_WIDTH = 20
[PWM] ESP32_FastPWM: _dutycycle = 58982
[PWM] setPWM_Int: _dutycycle = 3686 , DC % = 89.99
=====================================================================================
Index	Pin	PWM_freq	DutyCycle	Actual Freq
=====================================================================================
0	25	2000.00		10.00		2000.0000
1	27	3000.00		30.00		3000.0000
2	21	4000.00		50.00		4000.0000
3	22	8000.00		90.00		8000.0000
=====================================================================================
Actual data: pin = 16, PWM DC = 9.99, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=====================================================================================
=====================================================================================
Actual data: pin = 17, PWM DC = 29.98, PWMPeriod = 333.33, PWM Freq (Hz) = 3000.0000
=====================================================================================
=====================================================================================
Actual data: pin = 19, PWM DC = 50.00, PWMPeriod = 250.00, PWM Freq (Hz) = 4000.0000
=====================================================================================
=====================================================================================
Actual data: pin = 21, PWM DC = 89.99, PWMPeriod = 125.00, PWM Freq (Hz) = 8000.0000
=====================================================================================
```

---

### 3. PWM_DynamicFreq on ESP32S3_DEV

The following is the sample terminal output when running example [**PWM_DynamicFreq**](examples/PWM_DynamicFreq) on **ESP32S3_DEV**, to demonstrate the ability to change dynamically PWM frequencies.

```cpp
Starting PWM_DynamicFreq on ESP32S3_DEV
ESP32_FastPWM v1.1.0
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 8 , LEDC_CHANNELS = 8 , LEDC_MAX_BIT_WIDTH = 14
[PWM] ESP32_FastPWM: _dutycycle = 32768
[PWM] setPWM_Int: _dutycycle = 128 , DC % = 50.00
=====================================================================================
Change PWM Freq to 20000.00
[PWM] setPWM: _dutycycle = 32768 , frequency = 20000.00
[PWM] setPWM_Int: _dutycycle = 128 , DC % = 50.00
[PWM] setPWM_Int: change frequency to 20000.00 from 10000.00
=====================================================================================
Actual data: pin = 16, PWM DC = 50.00, PWMPeriod = 50.00, PWM Freq (Hz) = 20000.0000
=====================================================================================
Change PWM Freq to 10000.00
[PWM] setPWM: _dutycycle = 32768 , frequency = 10000.00
[PWM] setPWM_Int: _dutycycle = 128 , DC % = 50.00
[PWM] setPWM_Int: change frequency to 10000.00 from 20000.00
=====================================================================================
Actual data: pin = 16, PWM DC = 50.00, PWMPeriod = 100.00, PWM Freq (Hz) = 10000.0000
=====================================================================================
Change PWM Freq to 20000.00
[PWM] setPWM: _dutycycle = 32768 , frequency = 20000.00
[PWM] setPWM_Int: _dutycycle = 128 , DC % = 50.00
[PWM] setPWM_Int: change frequency to 20000.00 from 10000.00
=====================================================================================
Actual data: pin = 16, PWM DC = 50.00, PWMPeriod = 50.00, PWM Freq (Hz) = 20000.0000
=====================================================================================
Change PWM Freq to 10000.00
[PWM] setPWM: _dutycycle = 32768 , frequency = 10000.00
[PWM] setPWM_Int: _dutycycle = 128 , DC % = 50.00
[PWM] setPWM_Int: change frequency to 10000.00 from 20000.00
=====================================================================================
Actual data: pin = 16, PWM DC = 50.00, PWMPeriod = 100.00, PWM Freq (Hz) = 10000.0000
=====================================================================================
```

---


### 4. PWM_Waveform on ESP32S2_DEV

The following is the sample terminal output when running example [**PWM_Waveform**](examples/PWM_Waveform) on **ESP32S2_DEV**, to demonstrate how to use the `setPWM_manual()` function in wafeform creation


```cpp
Starting PWM_Waveform on ESP32S2_DEV
ESP32_FastPWM v1.1.0
[PWM] ESP32_FastPWM: new _channel = 0
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 8 , LEDC_CHANNELS = 8 , LEDC_MAX_BIT_WIDTH = 14
[PWM] ESP32_FastPWM: _dutycycle = 0
[PWM] setPWM: _dutycycle = 0 , frequency = 1000.00
[PWM] setPWM_Int: _dutycycle = 0 , DC % = 0.00
============================================================================================
Actual data: pin = 16, PWM DutyCycle = 0.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
============================================================================================
[PWM] setPWM_manual: DCValue = 0 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 204 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 409 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 614 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 819 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1024 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1228 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1433 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1638 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1843 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2048 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2252 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2457 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2662 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2867 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3072 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3276 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3481 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3686 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3891 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 4096 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3891 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3686 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3481 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3276 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3072 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2867 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2662 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2457 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2252 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2048 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1843 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1638 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1433 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1228 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1024 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 819 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 614 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 409 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 204 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 0 , _frequency = 1000.00
```

---

### 5. PWM_Waveform on ESP32C3_DEV

The following is the sample terminal output when running example [**PWM_Waveform**](examples/PWM_Waveform) on **ESP32C3_DEV**, to demonstrate how to use the `setPWM_manual()` function in wafeform creation


```cpp
Starting PWM_Waveform on ESP32C3_DEV
ESP32_FastPWM v1.1.0
[PWM] ESP32_FastPWM: new _channel = 0
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 6 , LEDC_CHANNELS = 6 , LEDC_MAX_BIT_WIDTH = 14
[PWM] ESP32_FastPWM: _dutycycle = 0
[PWM] setPWM: _dutycycle = 0 , frequency = 1000.00
[PWM] setPWM_Int: _dutycycle = 0 , DC % = 0.00
============================================================================================
Actual data: pin = 9, PWM DutyCycle = 0.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
============================================================================================
[PWM] setPWM_manual: DCValue = 0 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 204 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 409 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 614 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 819 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1024 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1228 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1433 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1638 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1843 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2048 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2252 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2457 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2662 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2867 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3072 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3276 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3481 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3686 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3891 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 4096 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3891 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3686 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3481 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3276 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3072 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2867 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2662 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2457 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2252 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2048 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1843 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1638 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1433 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1228 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1024 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 819 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 614 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 409 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 204 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 0 , _frequency = 1000.00
```

---

### 6. PWM_Waveform on ESP32S3_DEV

The following is the sample terminal output when running example [**PWM_Waveform**](examples/PWM_Waveform) on **ESP32S3_DEV**, to demonstrate how to use the `setPWM_manual()` function in wafeform creation


```cpp
Starting PWM_Waveform on ESP32S3_DEV
ESP32_FastPWM v1.1.0
[PWM] ESP32_FastPWM: new _channel = 0
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 8 , LEDC_CHANNELS = 8 , LEDC_MAX_BIT_WIDTH = 14
[PWM] ESP32_FastPWM: _dutycycle = 0
[PWM] setPWM: _dutycycle = 0 , frequency = 1000.00
[PWM] setPWM_Int: _dutycycle = 0 , DC % = 0.00
============================================================================================
Actual data: pin = 16, PWM DutyCycle = 0.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
============================================================================================
[PWM] setPWM_manual: DCValue = 0 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 204 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 409 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 614 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 819 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1024 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1228 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1433 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1638 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1843 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2048 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2252 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2457 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2662 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2867 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3072 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3276 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3481 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3686 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3891 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 4096 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3891 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3686 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3481 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3276 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 3072 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2867 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2662 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2457 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2252 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 2048 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1843 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1638 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1433 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1228 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 1024 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 819 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 614 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 409 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 204 , _frequency = 1000.00
[PWM] setPWM_manual: DCValue = 0 , _frequency = 1000.00
```


---

### 7. PWM_manual on ESP32_DEV

The following is the sample terminal output when running example [**PWM_manual**](examples/PWM_manual) on **ESP32_DEV**, to demonstrate how to use the `setPWM_manual()` and `setPWM_DCPercentage_manual()` functions in wafeform creation


```cpp
Starting PWM_manual on ESP32_DEV
ESP32_FastPWM v1.1.0
[PWM] ESP32_FastPWM: new _channel = 0
[PWM] ESP32_FastPWM: SOC_LEDC_CHANNEL_NUM = 8 , LEDC_CHANNELS = 16 , LEDC_MAX_BIT_WIDTH = 20
[PWM] ESP32_FastPWM: _dutycycle = 0
[PWM] setPWM_Int: _dutycycle = 0 , DC % = 0.00
=================================================================================================
Actual data: pin = 16, PWM DC = 0.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 0.00 , new_dc = 0
[PWM] setPWM_manual: DCValue = 0 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 0.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 5.00 , new_dc = 3276
[PWM] setPWM_manual: DCValue = 3276 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 5.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 10.00 , new_dc = 6553
[PWM] setPWM_manual: DCValue = 6553 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 10.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 15.00 , new_dc = 9830
[PWM] setPWM_manual: DCValue = 9830 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 15.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 20.00 , new_dc = 13107
[PWM] setPWM_manual: DCValue = 13107 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 20.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 25.00 , new_dc = 16384
[PWM] setPWM_manual: DCValue = 16384 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 25.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 30.00 , new_dc = 19660
[PWM] setPWM_manual: DCValue = 19660 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 30.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 35.00 , new_dc = 22937
[PWM] setPWM_manual: DCValue = 22937 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 35.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 40.00 , new_dc = 26214
[PWM] setPWM_manual: DCValue = 26214 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 40.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 45.00 , new_dc = 29491
[PWM] setPWM_manual: DCValue = 29491 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 45.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 50.00 , new_dc = 32768
[PWM] setPWM_manual: DCValue = 32768 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 50.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 55.00 , new_dc = 36044
[PWM] setPWM_manual: DCValue = 36044 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 55.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 60.00 , new_dc = 39321
[PWM] setPWM_manual: DCValue = 39321 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 60.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 65.00 , new_dc = 42598
[PWM] setPWM_manual: DCValue = 42598 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 65.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 70.00 , new_dc = 45875
[PWM] setPWM_manual: DCValue = 45875 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 70.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 75.00 , new_dc = 49152
[PWM] setPWM_manual: DCValue = 49152 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 75.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 80.00 , new_dc = 52428
[PWM] setPWM_manual: DCValue = 52428 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 80.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 85.00 , new_dc = 55705
[PWM] setPWM_manual: DCValue = 55705 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 85.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 90.00 , new_dc = 58982
[PWM] setPWM_manual: DCValue = 58982 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 90.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 95.00 , new_dc = 62259
[PWM] setPWM_manual: DCValue = 62259 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 95.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 100.00 , new_dc = 0
[PWM] setPWM_manual: DCValue = 0 , _frequency = 1000.00
=================================================================================================
Actual data: pin = 16, PWM DC = 0.00, PWMPeriod = 1000.00, PWM Freq (Hz) = 1000.0000
=================================================================================================
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PWM_LOGLEVEL_` from 0 to 4

```cpp
// These define's must be placed at the beginning before #include "ESP32_FastPWM.h"
// _PWM_LOGLEVEL_ from 0 to 4
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_      4
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [ESP32_FastPWM issues](https://github.com/khoih-prog/ESP32_FastPWM/issues)

---

## TO DO

1. Search for bug and improvement.

---

## DONE

 1. Basic hardware PWM-channels for `ESP32, ESP32_S2, ESP32_S3 and ESP32_C3` using [ESP32 core](https://github.com/espressif/arduino-esp32)
 2. Add example [PWM_StepperControl](https://github.com/khoih-prog/ESP32_FastPWM/tree/main/examples/PWM_StepperControl) to demo how to control Stepper Motor using PWM
 3. Add example [PWM_manual](https://github.com/khoih-prog/ESP32_FastPWM/tree/main/examples/PWM_manual) to demo how to correctly use PWM to generate waveform
 4. Add function `setPWM_DCPercentage_manual()` to facilitate the setting PWM DC manually by using DCPercentage, instead of absolute DCValue depending on varying PWMPeriod
 5. Fix glitch when changing PWM frequency
 
---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Thanks to [Paul van Dinther](https://github.com/dinther) for proposing new way to use PWM to drive Stepper-Motor in [Using PWM to step a stepper driver #16](https://github.com/khoih-prog/RP2040_PWM/issues/16), leading to v1.0.1


<table>
  <tr>
    <td align="center"><a href="https://github.com/dinther"><img src="https://github.com/dinther.png" width="100px;" alt="dinther"/><br /><sub><b>Paul van Dinther</b></sub></a><br /></td>
  </tr>
</table>



---

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/ESP32_FastPWM/blob/main/LICENSE)

---

## Copyright

Copyright (c) 2022- Khoi Hoang


