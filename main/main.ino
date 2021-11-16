
#include <HX711_ADC.h>
#include <Playtune.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

//pins:
const int HX711_dout = 5; //mcu > HX711 dout pin
const int HX711_sck = 6; //mcu > HX711 sck pin

//initialize playtune object
Playtune pt;

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;

void setup() {
  
  Serial.begin(57600); delay(10);
  Serial.println();
  Serial.println("Starting...");

  

  LoadCell.begin();
  float calibrationValue;
  calibrationValue = 696.0; //set calibration value
#if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); 
#endif
  //EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }

//initialize pt channels in pins 2,3,4
  pt.tune_initchan(2);
  pt.tune_initchan(3);
  pt.tune_initchan(4);
  
  
}

//metroid item pick up sound in 3 channels
const unsigned char PROGMEM metroid [] = {
0x90,45, 0x91,65, 1,32, 0x81, 0,58, 0x91,70, 0x92,62, 1,32, 0x81, 0x82, 0,58, 0x91,72, 0x92,65, 1,32, 0x81, 
0x82, 0,58, 0x91,74, 0x92,70, 1,4, 0x80, 0,28, 0x81, 0x82, 0,58, 0x90,69, 0x91,45, 0x92,76, 1,33, 0x82, 0,57, 
0x92,72, 1,4, 0x80, 0,29, 0x82, 0,57, 0x90,67, 0x92,64, 1,33, 0x80, 0,58, 0x90,72, 1,3, 0x81, 0x82, 0,29, 
0x80, 0,63, 0x90,43, 0x91,77, 0x92,70, 1,32, 0x81, 0,58, 0x91,74, 1,3, 0x82, 0,29, 0x81, 0,58, 0x91,70, 
0x92,65, 1,32, 0x81, 0x82, 0,58, 0x91,67, 0x92,62, 1,4, 0x80, 0,28, 0x81, 0x82, 0,58, 0x90,57, 0x91,69, 0x92,62, 
5,18, 0x80, 0x81, 0x82, 0xF0};



void retroid()
{
  pt.tune_playscore(metroid);
  Serial.println("played sound");
}




void loop() {
  
  static boolean newDataReady = 0;
  const int serialPrintInterval = 100; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) 
  {
    float i = LoadCell.getData();
    Serial.print("Load_cell output val: ");
    Serial.println(i);
    newDataReady = 0;
  }
      
  //if the cartridge is picked up play the sound once
  if( LoadCell.getData()<-10 && millis()>t) 
  {
    retroid();
    t = millis();
  }

  //check if the cartridge has been put back to reset
  if (LoadCell.getData()>-5)
  {
    t = 0;
  }
      

  
}

  
