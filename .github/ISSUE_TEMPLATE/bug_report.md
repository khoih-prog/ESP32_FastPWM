---
name: Bug report
about: Create a report to help us improve
title: ''
labels: ''
assignees: ''

---

### Describe the bug

A clear and concise description of what the bug is.

### Steps to Reproduce

Steps to reproduce the behavior. Including the [MRE](https://stackoverflow.com/help/minimal-reproducible-example) sketches

### Expected behavior

A clear and concise description of what you expected to happen.

### Actual behavior

A clear and concise description of what you expected to happen.

### Debug and AT-command log (if applicable)

A clear and concise description of what you expected to happen.

### Screenshots

If applicable, add screenshots to help explain your problem.

---

### Information

Please ensure to specify the following:

* Arduino IDE version (e.g. 1.8.19) or Platform.io version
* `ESP32` Core Version (e.g. ESP32 core v2.0.6)
* `ESP32` Board type (e.g. ESP32_DEV Module, etc.)
* `ESP32-S2` Board type (e.g. ESP32S2_DEV Module, ESP32_S2_Saola, etc.)
* `ESP32_S3` Board type (e.g. ESP32S3_DEV, ESP32_S3_BOX, UM TINYS3, UM PROS3, UM FEATHERS3, etc.)
* `ESP32-C3` Board type (e.g. ESP32C3_DEV Module, etc.)
* Contextual information (e.g. what you were trying to achieve)
* Simplest possible steps to reproduce
* Anything that might be relevant in your opinion, such as:
  * Operating system (Windows, Ubuntu, etc.) and the output of `uname -a`
  * Network configuration


Please be educated, civilized and constructive as you've always been. Disrespective posts against [GitHub Code of Conduct](https://docs.github.com/en/site-policy/github-terms/github-event-code-of-conduct) will be ignored and deleted.

---

### Example

```
Arduino IDE version: 1.8.19
ESP32 core v2.0.6
ESP32S3_DEV Module
OS: Ubuntu 20.04 LTS
Linux xy-Inspiron-3593 5.15.0-58-generic #64~20.04.1-Ubuntu SMP Fri Jan 6 16:42:31 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux

Context:
I encountered a crash while using TimerInterrupt.

Steps to reproduce:
1. ...
2. ...
3. ...
4. ...
```

### Additional context

Add any other context about the problem here.

---

### Sending Feature Requests

Feel free to post feature requests. It's helpful if you can explain exactly why the feature would be useful.

There are usually some outstanding feature requests in the [existing issues list](https://github.com/khoih-prog/ESP32_FastPWM/issues?q=is%3Aopen+is%3Aissue+label%3Aenhancement), feel free to add comments to them.

---

### Sending Pull Requests

Pull Requests with changes and fixes are also welcome!

Please use the `astyle` to reformat the updated library code as follows (demo for Ubuntu Linux)

1. Change directory to the library GitHub

```
xy@xy-Inspiron-3593:~$ cd Arduino/xy/ESP32_FastPWM_GitHub/
xy@xy-Inspiron-3593:~/Arduino/xy/ESP32_FastPWM_GitHub$
```

2. Issue astyle command

```
xy@xy-Inspiron-3593:~/Arduino/xy/ESP32_FastPWM_GitHub$ bash utils/restyle.sh
```

