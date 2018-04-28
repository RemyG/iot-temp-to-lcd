#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>

// Data wire is plugged into pin D3 on the ESP8266 - GPIO 0
#define ONE_WIRE_BUS 0

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature DS18B20(&oneWire);

char temperatureCString[7];
char previousTemp[7] = "init";

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  Serial.begin(115200);

  Wire.begin(D4,D5);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("HELLO");
  lcd.setCursor(5, 1);
  lcd.print("WORLD");
  
  delay(10);

  DS18B20.begin();

  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
}

void getTemperature() {
  float tempC;
  float tempF;
  do {
    DS18B20.requestTemperatures();
    tempC = DS18B20.getTempCByIndex(0);
    dtostrf(tempC, 3, 1, temperatureCString);
    delay(100);
  } while (tempC == (-127.0));
}

void loop() {
  
  getTemperature();

  Serial.println(temperatureCString);
  Serial.println(previousTemp);

  if (strcmp(previousTemp,temperatureCString) != 0) {
    lcd.setCursor(1, 1);
    lcd.print(temperatureCString);
    strncpy(previousTemp, temperatureCString, 7);
  }

  delay(10000);
}   
