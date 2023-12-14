#include <Arduino.h>
#include <SPI.h>
#include "susCanalyzer.h"
#include "ghettoDBC.h"
#include "mcp2515_can.h"

// For Arduino MCP2515 seeed Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10



const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

///// can messages we care about 
int canIDwatch[7] = {
702, //BMS Voltages
703, //BMS thermistors 
704, //BMS temps
800, //Drain status bankA(?) maybe for balancing 
801, //bank b drain status
900, //BMS current
950 //BMS hard fault indi
};
/////
CAN_msg msg(0x12E, 8, nullptr);  // Create an instance of the CAN_msg class
CAN_msg BMS_Voltages(702, 8, nullptr);
/////

void setup() {
    Serial.begin(115200);
    while (CAN_OK != CAN.begin(CAN_1000KBPS)) {             // init can bus : baudrate = 500k
        Serial.println("Init fail is hat on");
        delay(1000);
    }
    Serial.println("Initialization complete");
}

int counter = 0;
int sampleLimit = 420;

void loop() {
    unsigned char len = 0;
    unsigned char buf[8];
    //in case you forget again &len passes len's addr to readMsgBuf() so readMsgBuf updates the value at that ddr
    if (CAN_MSGAVAIL == CAN.checkReceive() && counter < sampleLimit) {  
    //if (CAN_MSGAVAIL == CAN.checkReceive()){ // && counter < sampleLimit) {         // check if data coming
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
        counter++;
        unsigned long canID = CAN.getCanId();

        //forloop if length of canmsgids we care about loop through (canId == msgid[i]) etc
        if(msg.getID() == 0x12E){
          const uint8_t* msgData = msg.getData(); 

          Serial.print("Message ID: 0x");
          Serial.print(msg.getID(), HEX);
          Serial.print(" data:");
            for (int i = 0; i < msg.getLength(); i++) { // get length from msg the data
            Serial.print(msgData[i]);
            Serial.print(" ");//("\t");
            
          //Serial.println();
        }
        Serial.println();
      }
    }
}
