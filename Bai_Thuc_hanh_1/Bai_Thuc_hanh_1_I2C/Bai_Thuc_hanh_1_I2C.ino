#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define BH1750_ADDR 0x23   // ADDR nối GND

void setup() {
  Serial.begin(115200);

  // Khởi tạo I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Bật BH1750 ở chế độ đo liên tục, độ phân giải cao
  Wire.beginTransmission(BH1750_ADDR);
  Wire.write(0x10);   // Continuous High Resolution Mode
  Wire.endTransmission();

  delay(200);
}

void loop() {
  uint16_t data = 0;

  // Yêu cầu BH1750 gửi 2 byte dữ liệu
  Wire.requestFrom(BH1750_ADDR, 2);

  if (Wire.available() == 2) {
    data = Wire.read();
    data = (data << 8) | Wire.read();

    // Chuyển sang đơn vị Lux
    float lux = data / 1.2;

    Serial.print("Anh sang: ");
    Serial.print(lux);
    Serial.println(" lux");
  } else {
    Serial.println("Read Error!");
  }

  delay(1000);
}