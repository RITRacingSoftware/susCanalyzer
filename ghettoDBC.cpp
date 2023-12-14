#include "ghettoDBC.h"
//initialize class
CAN_msg::CAN_msg(uint32_t ID, uint8_t length, const uint8_t* data) {
    setID(ID);
    setLength(length);
    setData(data, length);
    
    //this->ID = ID;
    //this->length = length;
    //memcpy(this->data, data, sizeof(this->data)); //huh
}
//dont foget settergetter below  

uint32_t CAN_msg::getID() const {
    return ID;
}

uint8_t CAN_msg::getLength() const {
    return length;
}

const uint8_t* CAN_msg::getData() const {
    return data;
}

void CAN_msg::setID(uint32_t newID) {
    ID = newID;
}

void CAN_msg::setLength(uint8_t newLength) {
    length = newLength;
}

void CAN_msg::setData(const uint8_t* newData, uint8_t length) { 
    length = min(length,(uint8_t)8); //check if over 8 bytes (& size of array )
    memcpy(data, newData, sizeof(data));
}

void CAN_msg::printDetails() const {
    // Implement as needed
}