#include "ghettoDBC.cpp"


//length is CAN.readMsgBuf(&len)
class CAN_msg {
public:
  CAN_msg(uint32_t ID, uint8_t length, const uint8_t* data);
      // Getter methods
    uint32_t getID() const;
    uint8_t getLength() const;
    const uint8_t* getData() const;

    //setter 
    void setID();
    void setLength();
    void setData();

    //other stuff hey remember const means doesn't modify or something i forgot comp problem solving was a while ago
    void printDetails() const;


private:
  uint32_t ID;
  uint8_t length; 
  const uint8_t* data[8];
};