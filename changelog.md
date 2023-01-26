# ESP32_FastPWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP32_FastPWM.svg?)](https://www.ardu-badge.com/ESP32_FastPWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP32_FastPWM.svg)](https://github.com/khoih-prog/ESP32_FastPWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP32_FastPWM/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP32_FastPWM.svg)](http://github.com/khoih-prog/ESP32_FastPWM/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.1.0](#Releases-v110)
  * [Releases v1.0.1](#Releases-v101)
  * [Releases v1.0.0](#releases-v100)

---
---

## Changelog

### Releases v1.1.0

1. Add example [PWM_manual](https://github.com/khoih-prog/ESP32_FastPWM/tree/main/examples/PWM_manual) to demo how to correctly use PWM to generate waveform. Check [About DCValue in setPWM_manual #2](https://github.com/khoih-prog/AVR_PWM/discussions/2)
2. Add function `setPWM_DCPercentage_manual()` to facilitate the setting PWM DC manually by using `DCPercentage`, instead of `absolute DCValue` depending on varying resolution
3. Fix glitch when changing PWM frequency. Check [Frequency change on cycle end. #1](https://github.com/khoih-prog/ESP32_FastPWM/discussions/1)

### Releases v1.0.1

1. Add example [PWM_StepperControl](https://github.com/khoih-prog/ESP32_FastPWM/examples/PWM_StepperControl) to demo how to control Stepper Motor using PWM. Check [Using PWM to step a stepper driver #16](https://github.com/khoih-prog/RP2040_PWM/issues/16)


### Releases v1.0.0

1. Initial coding for ESP32, ESP32_S2, ESP32_S3 and ESP32_C3 boards using [ESP32 core](https://github.com/espressif/arduino-esp32)


