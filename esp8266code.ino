#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 4
#define RST_PIN 5
//SDA  SCK MOSI MISO GND RST 3.3V 
// D2  D5  D7   D6   GND D1  3.3V
#define WIFI_LED 0
#define SENT_LED 2
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[3];

const char* ssid     = " your SSID";
const char* password = " your password";

HTTPClient http; // Instance of the class
int httpCode;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  pinMode(WIFI_LED,OUTPUT);
  pinMode(SENT_LED,OUTPUT);
  digitalWrite(WIFI_LED,LOW);
  digitalWrite(SENT_LED,LOW);

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  Serial.println("Logs");
  Serial.println("----------------------------------------------");
  delay(100);
  Serial.println("System Power: OK");
  delay(100);
  Serial.println("Wifi Connection: ERR");
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  delay(100);

}

void loop() {
  //if(WiFi.status() == WL_CONNECTED){
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connecteddd");
    setup_wifi();
  }
  else {
    digitalWrite(WIFI_LED,HIGH);
    
      //------------------------------------------------------------------------------------------------------------------------------------------------------RFID
        // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
      //-----------------------------------------------------------------------------------------------------------------------------------------------------WIFI
      
      Serial.println("HTTP REQUEST: GET");
      //change with your own address                                                          // http request
      http.begin("http://ladybugtoys.co/nuri/api.php?cardID="+String(rfid.uid.uidByte[0])+"-"+String(rfid.uid.uidByte[1])+"-"+String(rfid.uid.uidByte[2])+"-"+String(rfid.uid.uidByte[3])); //HTTP // http://www.ladybugtoys.co/nuri/api.php?cardID=65-93-130-224
      httpCode = http.GET();
      if(httpCode == 200)
      {
        digitalWrite(SENT_LED,HIGH);
        delay(500);
        digitalWrite(SENT_LED,LOW);
        delay(500);
      }
      if (httpCode > 0) {
        Serial.println("HTTP CODE: " + String(httpCode));
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();

          if (payload.toInt() == 1) {
            Serial.println("HTTP POST OPERATION: OK");
          }
          else {
            Serial.println("HTTP POST OPERATION: ERR");
          }
        }
      }
      else {
        Serial.println("HTTP POST OPERATION: " + String(http.errorToString(httpCode).c_str()));
      }
  }
  else{
     Serial.println(F("The NUID tag is:"));
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
      //-----------------------------------------------------------------------------------------------------------------------------------------------------WIFI
      
      Serial.println("HTTP REQUEST: GET");
      //change with your own address                                                          //  http request
      http.begin("http://ladybugtoys.co/nuri/api.php?cardID="+String(rfid.uid.uidByte[0])+"-"+String(rfid.uid.uidByte[1])+"-"+String(rfid.uid.uidByte[2])+"-"+String(rfid.uid.uidByte[3])); //HTTP // http://www.ladybugtoys.co/nuri/api.php?cardID=65-93-130-224
      httpCode = http.GET();
      if(httpCode == 200)
      {
        digitalWrite(SENT_LED,HIGH);
        delay(500);
        digitalWrite(SENT_LED,LOW);
        delay(500);
      }

      if (httpCode > 0) {
        Serial.println("HTTP CODE: " + String(httpCode));
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();

          if (payload.toInt() == 1) {
            Serial.println("HTTP POST OPERATION: OK");
          }
          else {
            Serial.println("HTTP POST OPERATION: ERR");
          }
        }
      }
      else {
        Serial.println("HTTP POST OPERATION: " + String(http.errorToString(httpCode).c_str()));
      }
  }
      
  }
}


void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi Connection: ERR");
    digitalWrite(WIFI_LED,LOW);
    delay(500);
  }
  Serial.println("WiFi Connection: OK");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
