
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>

// Data wire is plugged into pin D3 on the ESP8266
#define ONE_WIRE_BUS D3

// LCD pins
#define SDA_PIN D4
#define SCL_PIN D5

#define TEMP_SIZE 7

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature DS18B20(&oneWire);

char temperatureCString[TEMP_SIZE];
char previousTemp[TEMP_SIZE] = "init";

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("HELLO");
  lcd.setCursor(5, 1);
  lcd.print("WORLD");
  
  delay(2000);

  DS18B20.begin();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp.:");
}

void getTemperature() {

  float tempC;
  do {
    DS18B20.requestTemperatures();
    tempC = DS18B20.getTempCByIndex(0);
    dtostrf(tempC, 3, 1, temperatureCString);
    if (tempC == (-127)) {
      delay(100);
    }
  } while (tempC == (-127.0));
}

void loop() {

  getTemperature();

  Serial.println(temperatureCString);

  if (strcmp(previousTemp,temperatureCString) != 0) {
    lcd.setCursor(7, 0);
    lcd.print(temperatureCString);
    strncpy(previousTemp, temperatureCString, TEMP_SIZE);
  }

  delay(2000);
}   
