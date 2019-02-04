/////screen
#include <Wire.h>
#include "Adafruit_INA219.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
Adafruit_INA219 ina219;
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 11
#define DELTAY 21
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
/////////////////////////////BME280
#include "BlueDot_BME280.h"
BlueDot_BME280 bme280 = BlueDot_BME280();
//////////////////////////////
void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  Serial.println(F("Basic Weather Station"));
  bme280.parameter.communication = 0;
  bme280.parameter.I2CAddress = 0x76;
  bme280.parameter.sensorMode = 0b11;
  bme280.parameter.IIRfilter = 0b100;                    //Setup for IIR Filter
  bme280.parameter.humidOversampling = 0b101;            //Setup Humidity Oversampling
  bme280.parameter.tempOversampling = 0b101;             //Setup Temperature Ovesampling
  bme280.parameter.pressOversampling = 0b101;            //Setup Pressure Oversampling
  bme280.parameter.pressureSeaLevel = 1013.25;           //default value of 1013.25 hPa
  bme280.parameter.tempOutsideCelsius = 15;              //default value of 15°C
  if (bme280.init() != 0x60)
  {
    while (1);
  }
  else
  {
    Serial.println(F("BME280 detected!"));
  }
  Serial.println();
  Serial.println();
  

}
void loop()
{

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("T:");
  display.print(bme280.readTempC());
  display.print(" C, A:");
  display.print(bme280.readAltitudeMeter());
  display.print("m");
  display.setCursor(0, 10);
  display.print("H: ");
  display.print(bme280.readHumidity());
  display.print(" %");
  display.setCursor(0, 20);
  display.print("P: ");
  display.print(bme280.readPressure());
  display.print(" hPa");
  display.display();
  delay(1000);


}
