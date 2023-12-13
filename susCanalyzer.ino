#include <Arduino.h>
#include <SPI.h>
#include "susCanalyzer.h"
#include "ghettoDBC.h"
#define CAN_2515
// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

const int LED        = 8;
boolean ledON        = 1;
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

void setup() {
    SERIAL_PORT_MONITOR.begin(115200);
    pinMode(LED, OUTPUT);

    while (CAN_OK != CAN.begin(CAN_1000KBPS)) {             // init can bus : baudrate = 500k
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");
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

        //SERIAL_PORT_MONITOR.println("-----------------------------");
        /*
        SERIAL_PORT_MONITOR.print("get data from ID: 0x");
        SERIAL_PORT_MONITOR.print(canId, HEX);
        Serial.print(" data:");
        */
        //forloop if length of canmsgids we care about loop through (canId == msgid[i]) etc
        if(canID == 0x12E){
          SERIAL_PORT_MONITOR.print("get data from ID: 0x");
          SERIAL_PORT_MONITOR.print(canID, HEX);
          Serial.print(" data:");
        
            for (int i = 0; i < len; i++) { // print the data
            SERIAL_PORT_MONITOR.print(buf[i]);
            SERIAL_PORT_MONITOR.print(" ");//("\t");
            if (ledON && i == 0) {

                digitalWrite(LED, buf[i]);
                ledON = 0;
                //delay(500);
            } else if ((!(ledON)) && i == 4) {

                digitalWrite(LED, buf[i]);
                ledON = 1;
            }
          //SERIAL_PORT_MONITOR.println();
        }
        SERIAL_PORT_MONITOR.println();
      }
        
        /*
        for (int i = 0; i < len; i++) { // print the data
            SERIAL_PORT_MONITOR.print(buf[i]);
            SERIAL_PORT_MONITOR.print(" ");//("\t");
            if (ledON && i == 0) {

                digitalWrite(LED, buf[i]);
                ledON = 0;
                //delay(500);
            } else if ((!(ledON)) && i == 4) {

                digitalWrite(LED, buf[i]);
                ledON = 1;
            }
        }
        */
        //SERIAL_PORT_MONITOR.println();
    }
}

//END FILE
