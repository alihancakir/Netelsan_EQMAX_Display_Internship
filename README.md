<p align="left"> 
   <img src="https://avatars.mds.yandex.net/i?id=d4bda66315afe0cebc3aaf1e5ff81cda1de4aeb3-12925719-images-thumbs&n=13" alt="Netelsan Logo" width="300">
</p>  

# NETELSAN Internship

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


  ---

## 📝 Day 6  

- Before starting the work on **I2C communication**, I made sure to understand everything about the process.
 
  Understanding I2C Protocol:
  <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/Understanding_I2C_(1).jpg" alt="Understanding I2C" width="400">
  </p>
  <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/Understanding_I2C(2).jpg" alt="Understanding I2C" width="400">
  </p>
  
- For the **coherent**, I examined the **AMT630A I2C specification** from  → [url](https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/AMT630A%20Driver%20Documents/Specifications_of_AMT630A.pdf)  
- Optimum frequency is **400 kHz**.

  <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/AMT630A_Specifications.jpg" alt="Configuration I2C" width="400">
  </p>

  > ✅ Prepared with the required knowledge for proper I2C implementation.

  ---

## 📝 Day 7

- **AMT630A** has a **3-byte command array** (see figure).  
  - **First byte**: Register group address  
  - **Second byte**: Sub-register address  
  - **Third byte**: Register value
 
   Command Array:
    <p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/Connect_To_AMT630A.jpg" alt="Connetion to AMT630A" width="400">
  </p>

- ⚠️ Attention:  
  - I2C address is fixed **7 bits** + **1 R/W bit**. It could be `0` or `1`.  
  - We are sending data **master → slave**.  
  - However, the first byte of the *command array* is **8 bits**.  
  - Therefore, we must **shift right**: `8 bits >> 1 = 7 bits`.  
  - The least significant bit (`2^0`) must always be **0** (write mode).  

   ```c
   --------------------------------------------------------------------------------------------------------------------------------
   |  Start Condition  |     Slave Address     |      R/W      |  ACK  |     DATA1     |  ACK  |     DATA1     |  Stop Condition  |
   --------------------------------------------------------------------------------------------------------------------------------
   |  SDA pull down    |  it must be 7 bit     |  it must be 0 |       |   it fixed    |       |   it fixed    |   SCL pull up    |
   |      delay        |  (convert to 7 bit    |  due to we    |       |    8 bits     |       |    8 bits     |      delay       |
   |  SCL pull down    |  from 8bit:(0xXX >>1) |  always write |       |               |       |               |   SDA pull up    |
   --------------------------------------------------------------------------------------------------------------------------------
   
   static void write_byte(uint8_t reg_addr, uint8_t data1, uint8_t data2) {
       //...
       i2c_master_write_to_device(
           I2C_MASTER_NUM, 
           reg_addr >> 1, 
           write_buf_3_bytes, 
           sizeof(write_buf_3_bytes), 
           I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS
       );
       //...
   }
   
   void app_main(void) {
       //...
       write_byte(0xBE, 0xC6, 0x40);
       write_byte(0xB6, 0x78, 0x02);
       //...
   }

- Due to occasional failures, **I2C communication was not always working fluently**.  
- Therefore, I tested the communication using an **I2C scanner code** to verify proper detection address.
  > ⚠️ Issue: I2C communication was not always working fluently.

<p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/Scanner_Consequence.jpg" alt="Scanner Consequence" width="400">
  </p>

  ---

## 📝 Day 8

- I examined the registers at [AMT630A register setting](https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/AMT630A%20Driver%20Documents/Ark%20AMT630A%20Register%20settings.pdf).  
- Example command array to set **brightness value 100**: `(0xB4, 0xD4, 0x64)`  
  - `0x64` corresponds to **decimal 100**.  
- Tested the definition and confirmed proper operation on the **test kit**.  

> ✅ Successfully verified register write and brightness control for AMT630A.  


  ---

## 📝 Day 9

- With **I2C**, connected and tested the **RGB display**.  
  - This means I finally reached the **target device**.  
- During the examination of **AMT630A register settings**, the **color register process** is defined as: `FB2AH`  
  - `FB` is the **MCU address**  
  - `2A` is the **register address**  
  - The next byte must be the **value**  

- Example command:  
```c
write_byte(0xB6, 0x2A, 0x20); // Set background color to green
```

[Video](https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/Videos/RGB_Test_EQMAX.mp4)

<p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/Display_RGB_Test.png" width="600">
  </p>

<p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/I2C_Communication_eventually_done_from_ESP32_TestKit_To_Target_Device.jpg" alt="Conneted the Target Device" width="600">
  </p>

  ---
  

## 📝 Day 10


> ✅ Test environment is now set up for running I2C and display control programs.

<p align="center">
  <img src="https://github.com/alihancakir/Archive-of-Nuvoton/blob/main/images/Test_Kit_Revised.jpg" alt="Test Kit Revised" width="600">
  </p>


  

  
