/***************************************************************************
* Project : Measuring Altitude using BME680
* System : Arduino UNO R3
* Author : Asser Soliman 
****************************************************************************
* Description
* This is a project in which we connect enviromental sensor BME680 with 
* Arduino UNO R3 using I2C communication protocol and read pressure data
* which then can be used to get altitude using proper equation
***************************************************************************/

/******************** Includes Section Start ********************/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal.h>
/******************** Includes Section End ********************/

/******************** Definition Section Start ********************/
#define SEALEVELPRESSURE_HPA (1013.25)
#define rs  12
#define en  11
#define d4  5
#define d5  4
#define d6  3
#define d7  2
/******************** Definition Section End ********************/

/******************** Variables Section Start ********************/
bool status;
Adafruit_BME280 bme;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void printValues() 
{
  Serial.println();

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println("===============================================================");

  lcd.setCursor(0, 0); // top left

  lcd.print("Pressure = ");
  lcd.print(bme.readPressure() / 100.0F);
  lcd.println(" hPa");

  lcd.setCursor(0, 1); // bottom left

  lcd.print("Altitude = ");
  lcd.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  lcd.println(" m");

}
/******************** Functions Section End ********************/

/******************** Setup Section Start ********************/
void setup() 
{
  Serial.begin(9600);
  while(!Serial); // Waiting till serial communication is ready 

  lcd.begin(16, 2); 

  status = bme.begin(0x76);  // Communicating with sensor

  while (!status) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    delay(1000); 
    status = bme.begin(0x76);
  }
}
/******************** Setup Section End ********************/

/******************** Loop Section Start ********************/
void loop(void)
{ 
    printValues();
    delay(2000);
}
/******************** Loop Section End ********************/
