# InspectionSystem
Description:
IZTECH student card reader is the inspection system for users. 
For the lectures and exams, students sign the paper to understand the attendance. 
Instead of this time wasting situation, we offered our project. 
When students come to the class, s/he scans his/her card to card reader that is placed door of the class. 
When lecturer came the class, s/he will see students that in class. 
Lecturer can also see lists after the lecture that is saved in the database.
	
Block Diagram:

  Student Card (13.56 MHz RFID Card)
      |
      v
  Card Reader (RC522)
      |
      v
  Wifi Module (NodeMCU Esp8266 development board)
      |
      v
  Database
      |
      v
  Website
   
   
Hardware:

NodeMCU: NodeMCU is ESP8266 development board that contains USB-TTL converter and voltage regulator. 
It is useful for prototyping. ESP8266 is a Wi-Fi module that is very famous Wi-Fi module because of its price. 
It contains ESP-01 to ESP-14. NodeMCU has ESP-12E model. It supports SPI/I2C and UART on-box communication.

RC522: The MFRC522 is an integrated reader/writer IC for contactless communication at 13.56 MHz. 
The MFRC522 reader supports ISO/IEC 14443 A/MIFARE and NTAG. 
Typical operating distance in Read/Write mode up to 50 mm depending on the antenna size. 

Setup:
1.	Arduino IDE -> File -> Preferences
2.	The link given below were added to Additional Boards Manager URLs. 
    http://arduino.esp8266.com/stable/package_esp8266com_index.json
3.	Arduino IDE -> Settings -> Boards -> Board Manager
4.	Esp8266 Boards and libraries were installed.
5.  Setup the MFRC522 library with link given below.
    https://github.com/miguelbalboa/rfid
