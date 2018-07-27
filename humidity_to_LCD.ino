#include <TT_LiquidCrystal.h>
#include <cactus_io_AM2302.h>

#define AM2302_PIN 2     // what pin on the arduino is the DHT22 data line connected to

TT_LiquidCrystal lcd;
AM2302 dht(AM2302_PIN);

void setup() {
  lcd.begin(16,2);
  dht.begin();
  Serial.begin(9600);
  Serial.println("RH\t\tTemp (F)\n");
}

void loop() {
  dht.readHumidity();
  dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(dht.humidity) || isnan(dht.temperature_C)) {
    Serial.println("DHT sensor read failure!");
    return;
  }
  lcd.setCursor(0,0);   // set cursor to 1st column, 1st row
  lcd.print("Humidity: ");
  lcd.print(dht.humidity); lcd.print("%");
  Serial.print(dht.humidity); Serial.print(" %\t\t");
  lcd.setCursor(0,1);   // set cursor to 1st column, 2nd row
  lcd.print("Temp: ");
  lcd.print(dht.temperature_F); lcd.print("F");
  Serial.print(dht.temperature_F); Serial.print(" *F\n");

  // Wait a few seconds between measurements. The AM2302 should not be read at a higher frequency of
  // about once every 2 seconds. So we add a 3 second delay to cover this.
  delay(3000);
}
