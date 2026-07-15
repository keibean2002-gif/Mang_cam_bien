#include <SPI.h>
#include <BMI160Gen.h>


const int SPI_SCK  = 4;   // SCL nối GPIO4
const int SPI_MISO = 5;   // SAO nối GPIO5
const int SPI_MOSI = 6;   // SDA nối GPIO6
const int SPI_CS   = 7;   // CS nối GPIO7

void setup() {
  Serial.begin(115200);
  while (!Serial); 

  
  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS, HIGH);
  delay(20); 

  Serial.println("--- BẮT ĐẦU KHỞI TẠO BMI160 SPI ---");

  
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);

  
  BMI160.begin(BMI160GenClass::SPI_MODE, SPI_CS);
  
  
  BMI160.setAccelerometerRange(2); 
  BMI160.setGyroRange(250);        
  
  Serial.println("Cấu hình xong! Đang đọc dữ liệu...");
}

void loop() {
  int gx, gy, gz;       
  int ax, ay, az;         
  BMI160.readGyro(gx, gy, gz);
  BMI160.readAccelerometer(ax, ay, az);

  Serial.print("Gia toc [X, Y, Z]: ");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t|\t");
  
  Serial.print("Vong quay [X, Y, Z]: ");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);

  delay(200); 
}