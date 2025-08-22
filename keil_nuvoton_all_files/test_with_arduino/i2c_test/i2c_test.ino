#include <Wire.h>

#define I2C_ADDRESS 0x23  // Yazmak istediğin cihazın I2C adresi

void setup() {
  Wire.begin();  // ESP32’de default SDA=21, SCL=22
  Serial.begin(115200);
}

void loop() {
  uint8_t data1 = 0xB4;
  uint8_t data2 = 0xD4;
  uint8_t data3 = 0x64;

  Wire.beginTransmission(I2C_ADDRESS); // Cihaza yazma başlat
  Wire.write(data1);                    // 1. byte
  Wire.write(data2);                    // 2. byte
  Wire.write(data3);                    // 3. byte
  uint8_t result = Wire.endTransmission(); // Yazmayı bitir ve sonucu al

  if(result == 0) {
    Serial.println("I2C yazma başarılı!");
  } else {
    Serial.print("I2C yazma hatası: ");
    Serial.println(result);
  }

  delay(1000); // 1 saniye bekle
}
