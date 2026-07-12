#include <SPI.h>
#include <BMI160Gen.h>

// Định nghĩa chính xác các chân cắm trên board test của bạn
const int SPI_SCK  = 4;   // SCL nối GPIO4
const int SPI_MISO = 5;   // SAO nối GPIO5
const int SPI_MOSI = 6;   // SDA nối GPIO6
const int SPI_CS   = 7;   // CS nối GPIO7

void setup() {
  Serial.begin(115200);
  while (!Serial); // Chờ mở Serial Monitor

  // 1. Ép chân CS lên mức CAO trước để ngắt chế độ I2C mặc định của BMI160
  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS, HIGH);
  delay(20); // Chờ một chút để cảm biến ổn định trạng thái SPI

  Serial.println("--- BẮT ĐẦU KHỞI TẠO BMI160 SPI ---");

  // 2. Định nghĩa lại chân SPI phần cứng của ESP32-C3
  // Lệnh này ép toàn bộ hệ thống SPI của chip chạy trên các chân 4, 5, 6, 7
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);

  // 3. Khởi tạo BMI160 theo cú pháp chuẩn của thư viện
  // Thư viện sẽ tự động giao tiếp qua bộ chân SPI đã cấu hình ở bước trên
  BMI160.begin(BMI160GenClass::SPI_MODE, SPI_CS);
  
  // 4. Thiết lập dải đo cho cảm biến
  BMI160.setAccelerometerRange(2); // Dải đo gia tốc +/- 2g
  BMI160.setGyroRange(250);        // Dải đo vòng quay +/- 250 độ/giây
  
  Serial.println("Cấu hình xong! Đang đọc dữ liệu...");
}

void loop() {
  int gx, gy, gz;         // Biến lưu dữ liệu Vòng quay (Gyro)
  int ax, ay, az;         // Biến lưu dữ liệu Gia tốc (Accel)

  // Đọc dữ liệu thực tế từ cảm biến BMI160
  BMI160.readGyro(gx, gy, gz);
  BMI160.readAccelerometer(ax, ay, az);

  // In kết quả ra Serial Monitor
  Serial.print("Gia toc [X, Y, Z]: ");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t|\t");
  
  Serial.print("Vong quay [X, Y, Z]: ");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);

  delay(200); // Đọc dữ liệu sau mỗi 200ms cho dễ nhìn
}