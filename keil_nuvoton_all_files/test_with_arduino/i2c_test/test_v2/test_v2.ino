#include <Wire.h>

#define AMT630A_ADDR 0x5B  // 0xB6 >> 1 = 7-bit adres

void setup() {
  Wire.begin();  // ESP32 default SDA=21, SCL=22
  Serial.begin(115200);

  // Slave'e 0x78, 0x02 gönder
  sendToAMT630A();
}

void loop() {
  // Örneğin sürekli gönderim için (her saniye):
  delay(1000);
  sendToAMT630A();
}

void sendToAMT630A() {
  Wire.beginTransmission(AMT630A_ADDR); // Slave adres (7-bit)
  Serial.println("data sending");
  Wire.write(0x78);  // İlk veri
  Wire.write(0x02);  // İkinci veri
  Wire.endTransmission(); // Stop condition
}
