#include <Wire.h>

void setup() {
  Wire.begin(); // SDA=21, SCL=22 (ESP32 default)
  Serial.begin(115200);
  Serial.println("\nI2C Scanner Başlatıldı...");
}

void loop() {
  byte error, address;
  int cihaz_sayisi = 0;

  Serial.println("Taramaya başlandı...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C cihaz bulundu! Adres: 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
      cihaz_sayisi++;
    } else if (error == 4) {
      Serial.print("Bilinmeyen hata. Adres: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (cihaz_sayisi == 0)
    Serial.println("Hiç cihaz bulunamadı.");
  else
    Serial.println("Tarama tamamlandı.");

  delay(5000); // 5 saniye sonra tekrar tara
}
