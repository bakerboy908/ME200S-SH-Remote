#ifndef ME200S_T
#define ME200S_T
#include <stdint.h>
#include <Vector.h>
#include <ME200S_Definitions.h>
#include <Arduino.h>
const int ELEMENT_COUNT_MAX = 4;
const int MAX_REPLAY_SIZE = 64;
class ME200S
{
private:


    const uint8_t Header_ = 0xFF;
    const uint8_t End_Mark_ = 0xEF;

    const uint16_t Device_Num_ = 0x3030;
    uint16_t Error_Code_; 
    bool sendCommand(uint16_t Command,Vector<char> Paramaters_);

    char commandReplyStorage[MAX_REPLAY_SIZE];
    Vector<char> receivedData_vec;
    bool commandReplay(unsigned long  commandType, int Paramater_Size);
    byte replyStorage[MAX_REPLAY_SIZE];
    int replyStorageSize = 0;




    /* data */
public:

    int recivedBufferSize;
    ME200S(/* args */);
    ~ME200S();
    bool setApature(uint16_t Apature);
    bool setApatureBlocking(uint16_t Apature);
    bool oneShotAF();
    bool AutoFocus(bool enable);
    void ShutterControl();
    void statusUpdate();
    bool cameraVersionRequest(); // array size is hard coded as it does not change;
    bool receivedData(char data[]);           // Returns a pointer to the paramater data;
    void printArray();
    bool irisPossition();
    void printArrayDirect();
    void printReplyStorage();

};



#endif
