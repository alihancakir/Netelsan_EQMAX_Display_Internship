# NETELSAN Internship 🚀

## 📢 _**Task: Wake Up the Intercom Unit From Zero**_

All documentation related to the internship is shared here.

---

## 📝 Day 1

- I used a **NuMaker-M032SE V1.3** development board and a **Nu-Link-Pro programmer**.  
- Installed **Keil** → [Download here](https://www.nuvoton.com/tool-and-software/)  
- Examined the **datasheet** of M032SE.  

> ⚠️ Issue: Programmer (Nu-Link-Pro) was not working while using UART communication.

<p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/Nuvoton_NuMaker_032SE.jpg" alt="NuMaker Board" width="400">
</p>

---

## 📝 Day 2

- ✅ Solved: I reached the UART data on Arduino.  
-  GPIO and Clock configured using: [NuTool](https://www.nuvoton.com/tool-and-software/software-tool/general/nutool/)  
-  I2C, SPI, UART, and Serial Window tested.

  NNuTool-PinConfigure (Web application):
  <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/NuTool_web_config.jpg" alt="NuTool" width="400">
  </p>

---

## 📝 Day 3

- I got a schematic related MCU some periperhals about EQMAX(the target board)  
- The pins and circuit structure was roughly examined by reverse engineering.  
- Created a excel products document.

  EQMAX(Target Device):
  <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/The_Target_Board_EQMAX_4.3_Unit.jpg" alt="EQMAX" width="400">
  </p>  

  EQMAX Schematic:
  <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/EQMAX_Schematic.jpg" alt="EQMAX Schematic" width="400">
  </p>  

  Pins:
  
| Program Pins | TFT Display Pins | Ringtone Pins | Doorbell Pins | Button Pins |
|--------------|----------------|---------------|---------------|------------|
| PF.0 → PGD   | PC.1 → OSD_SCL | PA.3 → SES_SEVİYE_4 | PF.15 → İÇZİL_INPUT | PB.6 → TUS_ADC |
| PF.1 → PGC   | PC.0 → OSD_SDA | PA.2 → SES_SEVİYE_3 |               | PB.5 → KAPI_BUTON |
| NRESET → NRESET |              | PA.1 → SES_SEVİYE_2 |               | PB.4 → KAPICI_BUTON |
|              |                | PA.0 → SES_SEVİYE_1 |               | PB.3 → GÜVENLİK_BUTON |
|              |                |               |               | PB.2 → KİLİT_BUTON |

| Useless Pins | LED Pins | Communication Pins | Unknown Pins 1 | Unknown Pins 2 |
|--------------|---------|------------------|----------------|----------------|
| PB.1 → CMBR_SCL | PA.13 → PLED | PF.3 → HABERLEŞME_TX | PC.5 → ZOUT_PWM | PA.9 → MONITOR_BES |
| PB.0 → CMBR_SDA | PA.11 → LED | PF.2 → HABERLEŞME_RX | PC.4 → KAOI_ÖNÜNE_BAGLAN | PA.8 → ANFI_BES |
| PB.7 → CMBR_INT |           |                  | PC.3 → KAPICIYA_BAGLAN | PA.12 → IK_KONTROL |
|              |           |                  | PC.2 → KAPIYA_BAGLAN | PA.14 → VIDEO_SEÇ |
|              |           |                  | PF.5 → TONE | PF.4 → SES_BESLEME |  


---

## 📝 Day 4

- Searched driver **AMT630A datasheet** but no consequence due to confidential sheet. I made an estimation of the pins and connectors to help me.  
- Contrary to what I thought, instead of SPI, I should use **I2C communication** (We don't need fluently UI, although SPI is faster than I2C when driving the display).

  AMT630A Driver Estimation Pins:  
  <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/TFT_Driver_Contoller_AMT630A_Examinatiton_Reverse_Engineering.jpg" alt="AMT630 Driver Examination" width="600">
  </p> 
  

---

## 📝 Day 5

- A test kit built for TFT Display with **ESP32_DEVKitC**.  
- There was some issue with the ESP board: CP210X programmer circuit not working. I utilized the programmer from another project based on **CH340G**. Solved.

  > ❌ Fatal: I need the datasheet of AMT630A driver for run the display.

  Test Kit:
  <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/TFT_Display_WakeUp_Test_Kit.jpg" alt="Test Kit" width="600">
  </p>  
  
  Test Kit Schematic:
  <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/TFT_Test_Design_Schematic/Test_For_Tft/TFT_TEST_SCHEMATIC.jpg" alt="Test Kit Schematic" width="600">
  </p>  

