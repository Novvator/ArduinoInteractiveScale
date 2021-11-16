# ArduinoInteractiveScale
An arduino project that combines the HX711 weight sensor and a speaker to play sound effects when an object is picked up.

## Components:
* Arduino Pro Micro (used Arduino Nano for the schematic)
* Speaker
* HX711 1kg Load Cell module
* Powerbank or any type of power input for the arduino

## Schematic:
![SCHEME](https://github.com/Novvator/ArduinoInteractiveScale/blob/main/images/schematic.png)

## Preview images:
![image1](https://github.com/Novvator/ArduinoInteractiveScale/blob/main/images/image1.jpg)
![image2](https://github.com/Novvator/ArduinoInteractiveScale/blob/main/images/image2.jpg)

### Specifications:
The arduino sketch detects if one of the game cartridges has been picked up and plays the Metroid item pick up sound once.\
Each time the arduino is booted up it recalibrates and resets the scale so the user doesn't have to do it manually.\
The speaker is connected to 3 pins so that it plays 3 channels of music input with the music file provided.

### Libraries used:
* [Arduino Playtune](https://github.com/LenShustek/arduino-playtune) to play the midi file
* [Miditones](https://github.com/LenShustek/miditones) to convert .mid file into C code
* [HX711_ADC](https://github.com/olkal/HX711_ADC) to use the weight sensor



