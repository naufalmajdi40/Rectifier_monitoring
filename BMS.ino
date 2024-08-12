//Lora
#define INTERVAL_MESSAGE1 5000
#include <lorawan.h>

//LIB for MCP
#include <Adafruit_MCP23X17.h>

//LIB for PZEM 01T
#include <PZEM004Tv30.h>
#define PZEM_RX_PIN 13
#define PZEM_TX_PIN 25


const char *devAddr = "0003bae3";
const char *nwkSKey = "666fd1dc5734b8e52c5b65da67f26aa1";
const char *appSKey = "7b6ba06d5309e0b03b1cb5c64d6dded1";

const unsigned long interval = 3000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent
unsigned int counter = 0;     // message counter

char myStr[50];
char outStr[255];
byte recvStatus = 0;

const sRFM_pins RFM_pins = {
  .CS = 18,
  .RST = 14,
  .DIO0 = 26,
  .DIO1 = 3,
  .DIO2 = -1,
  .DIO5 = -1,
};


//#SoftwareSerial pzem(2, 3); // RX, TX
float temp1 = 0;
float temp2 = 0;
float hum1 = 0;
float hum2 = 0;
float teg1 = 0;
float teg2 = 0;
float teg3 = 0;
float arus1 = 0;
float arus2 = 0;
float arus3 = 0;
int di[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
String dtSerial = "";
String dataSensor = "";
byte perintah[3][6] = {
  {0x01, 0x04, 0x00, 0x00, 0x00, 0x08}, //
  {0x02, 0x04, 0x00, 0x00, 0x00, 0x08}, 
  {0x04, 0x04, 0x00, 0x01, 0x00, 0x02}//suhu
};

//byte perintah[]={0x1,0x6,0x1,0x1,0x00,0x04};
byte bufferDataModbus[100];
byte *ptr;
int flag = 0;
Adafruit_MCP23X17 mcp;
PZEM004Tv30 pzem(Serial1, PZEM_RX_PIN, PZEM_TX_PIN);
void setup() { 
  Serial.begin(9600, SERIAL_8N2);
  Serial1.begin(9600, SERIAL_8N2, PZEM_RX_PIN, PZEM_TX_PIN);
  Serial2.begin(9600, SERIAL_8N2);
  Serial.println();
  ptr = bufferDataModbus;
  if (!lora.init()) {
    Serial.println("RFM95 not detected");
    delay(5000);
    return;
  }
  if (!mcp.begin_I2C(0x20)) {
    //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("MCP not detected");
    while (1);
  }
  for (int i = 0 ; i < 10; i++) {
    mcp.pinMode(i, INPUT_PULLUP);
  }
  lora.setDeviceClass(CLASS_A);

  // Set Data Rate
  lora.setDataRate(SF8BW125);

  // set channel to random
  lora.setChannel(MULTI);

  // Put ABP Key and DevAddress here
  lora.setNwkSKey(nwkSKey);
  lora.setAppSKey(appSKey);
  lora.setDevAddr(devAddr);

  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

}

void loop()
{
  
  if (millis() - previousMillis > interval) {
    sprintf(myStr, dataSensor.c_str(), counter);
    Serial.print("Sending: ");
    Serial.println(myStr);
    lora.sendUplink(myStr, strlen(myStr), 0, 1);
    counter++;
    //displayOled();
    lora.update();
    previousMillis = millis();
  }
sendModbus();
  //recvStatus = lora.readData(outStr);
  if (recvStatus) {
    Serial.println(outStr);
  }
  delay(200);
  flag++;
  if (flag > 2) {

    bacaSensor();
    flag = 0;
  }
}
