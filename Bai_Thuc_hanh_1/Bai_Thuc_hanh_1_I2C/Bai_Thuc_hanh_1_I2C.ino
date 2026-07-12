#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define BH1750_ADDR 0x23   

void setup() {
  Serial.begin(115200);

  
  Wire.begin(SDA_PIN, SCL_PIN);

  Wire.beginTransmission(BH1750_ADDR);
  Wire.write(0x10);   
  Wire.endTransmission();

  delay(200);
}

void loop() {
  uint16_t data = 0;

 
  Wire.requestFrom(BH1750_ADDR, 2);

  if (Wire.available() == 2) {
    data = Wire.read();
    data = (data << 8) | Wire.read();

    
    float lux = data / 1.2;

    Serial.print("Anh sang: ");
    Serial.print(lux);
    Serial.println(" lux");
  } else {
    Serial.println("Read Error!");
  }

  delay(1000);
}