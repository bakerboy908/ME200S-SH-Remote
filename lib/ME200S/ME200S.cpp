#include <ME200S.hpp>
ME200S::ME200S(/* args */)
{
    receivedData_vec.setStorage(commandReplyStorage);
    // Serial1.begin(9600); // setup the storage for the reply;
}

ME200S::~ME200S()
{
}
bool ME200S::cameraVersionRequest() // array size is hard coded as it does not change;
{
    char vector_data[1];
    Vector<char> paramaters(vector_data);
    paramaters.push_back(0);
    sendCommand(CAMERA_VERSION_REQUEST, paramaters);
    return commandReplay(TYPE1, 10);
}

bool ME200S::sendCommand(uint16_t Command, Vector<char> Paramaters_)
{
    // Serial1.println();
    Serial1.write(Header_);
    Serial1.write(Device_Num_ >> 8);
    Serial1.write(Device_Num_);
    Serial1.write(Command >> 8);
    Serial1.write(Command);
    for (unsigned int i = 0; i <= Paramaters_.size() - 1; i++)
    {
        Serial1.print(Paramaters_[i], HEX);
    }
    Serial1.write(End_Mark_);
    return true;
}
// bool ME200S::sendCommand(uint16_t Command, Vector<char> Paramaters_)
// {
//     Serial1.print(Header_, HEX);
//     Serial1.print(Device_Num_, HEX);
//     Serial1.print(Command, HEX);
//     for (unsigned int i = 0; i < Paramaters_.size(); i++)
//     {
//         Serial1.print(Paramaters_[i], HEX);
//     }
//     Serial1.print(End_Mark_, HEX);
//     return true;
// }

bool ME200S::commandReplay(unsigned long commandType, int Paramater_Size)
{
    byte buffer[MAX_REPLAY_SIZE];
    auto currenttime = millis();                       // commandType;
    while (millis() - currenttime < commandType + 500) // while the command hasnt timed out;
    {
        if (Serial1.available() >= 1) // Paramater_Size + 6)
        {
            auto size = Serial1.readBytesUntil(0xEF, buffer, MAX_REPLAY_SIZE);
            Serial.println();
            Serial.println("Buffer Contents");
            for (auto i = 0; i < size; i++)
            {
                Serial.print(buffer[i], HEX);
            }
            if (buffer[3] == 0x30 && buffer[4] == 0x030) // if no errors
            {
                receivedData_vec.clear();
                for (auto i = 0; i < Paramater_Size; i++)
                {
                    receivedData_vec.push_back(buffer[i+5]);
                }
            }

            Serial.println();
            Serial.println("Command Replay vector Contents");
            printArray();
            // if (Serial1.read() == 0xFE)
            // {
            //     if (Serial1.read() == 0x30)
            //     {
            //         if (Serial1.read() == 0x30)
            //         {
            //             if (Serial1.read() == 0x30 && Serial1.read() == 0x30)
            //             {

            //                 receivedData_vec.clear();
            //                 replyStorageSize = 0;
            //                 for (auto i = 0; i < Paramater_Size - 1; i++)
            //                 {
            //                     auto data = Serial1.read();
            //                     receivedData_vec.push_back(data);

            //                     replyStorage[i] = data;
            //                     replyStorageSize++;
            //                 }
            //                 recivedBufferSize = Paramater_Size;
            //                 Serial1.flush();
            //                 return true;
            //             }
            //             else
            //             {
            //                 Serial.println("ERROR");
            //                 for (auto i = 0; i < 1; i++)
            //                 {
            //                     receivedData_vec.push_back(Serial1.read());
            //                     /* code */
            //                 }
            //             }
            //         }
            //     }
            // }
        }
    }
    Serial1.flush();
    return false;
}
// bool ME200S::commandReplay(unsigned long commandType, int Paramater_Size)
// {
//     auto currenttime = millis();                       // commandType;
//     while (millis() - currenttime < commandType + 500) // while the command hasnt timed out;
//     {
//         if (Serial1.available() >= Paramater_Size + 6)
//         {
//             if (Serial1.read() == 0xFE)
//             {
//                 if (Serial1.read() == 0x30)
//                 {
//                     if (Serial1.read() == 0x30)
//                     {
//                         if (Serial1.read() == 0x30 && Serial1.read() == 0x30)
//                         {

//                             receivedData_vec.clear();
//                             replyStorageSize = 0;
//                             for (auto i = 0; i < Paramater_Size - 1; i++)
//                             {
//                                 auto data = Serial1.read();
//                                 receivedData_vec.push_back(data);

//                                 replyStorage[i] = data;
//                                 replyStorageSize++;
//                             }
//                             recivedBufferSize = Paramater_Size;
//                             Serial1.flush();
//                             return true;
//                         }
//                         else
//                         {
//                             Serial.println("ERROR");
//                             for (auto i = 0; i < 1; i++)
//                             {
//                                 receivedData_vec.push_back(Serial1.read());
//                                 /* code */
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     Serial1.flush();
//     return false;
// }
void ME200S::printArray()
{
    Serial.print("Paramater Size: ");
    Serial.println(receivedData_vec.size());
    for (int i = 0; i < receivedData_vec.size(); i++)
    {
        Serial.print(receivedData_vec.at(i));
    }
    Serial.println();
}
bool ME200S::receivedData(char data[])
{

    if (receivedData_vec.size() > 0)
    {
        for (int i = receivedData_vec.size(); i > 0; i--)
        {
            data[i] = receivedData_vec.back();
            receivedData_vec.pop_back();
        }

        return true;
    }
    return false;
}

// ╔═════════════════╦══════════╦═════════════════╦══════════╗
// ║ Parameter Value ║ F number ║ Parameter Value ║ F number ║
// ╠═════════════════╬══════════╬═════════════════╬══════════╣
// ║ FF              ║      1.0 ║ 7F              ║       16 ║
// ║ EF              ║      1.4 ║ 6F              ║       22 ║
// ║ DF              ║      2.0 ║ 5F              ║       32 ║
// ║ CF              ║      2.8 ║ 4F              ║       45 ║
// ║ BF              ║      4.0 ║ 3F              ║       64 ║
// ║ AF              ║      5.6 ║ 2F              ║       90 ║
// ║ 9F              ║      8.0 ║ 1F              ║      128 ║
// ║ 8F              ║       11 ║ 0F              ║      181 ║
// ╚═════════════════╩══════════╩═════════════════╩══════════╝

bool ME200S::setApature(uint16_t Apature)
{
    uint8_t char1 = (Apature & 0xF0) >> 4;
    uint8_t char2 = (Apature & 0xf);

    char vector_data[2];
    Vector<char> paramaters(vector_data);
    paramaters.push_back(char1);
    paramaters.push_back(char2);
    sendCommand(SET_IRIS_POSITION, paramaters);
    return commandReplay(TYPE2, 0);
}
bool ME200S::setApatureBlocking(uint16_t Apature)
{
    uint8_t char1 = (Apature & 0xF0) >> 4;
    uint8_t char2 = (Apature & 0xf);

    char vector_data[2];
    Vector<char> paramaters(vector_data);
    paramaters.push_back(char1);
    paramaters.push_back(char2);
    bool success = false;
    while (receivedData_vec[0] != (Apature & 0xF0) >> 4 && receivedData_vec[1] != (Apature & 0xF))
    {
        sendCommand(SET_IRIS_POSITION, paramaters);
        commandReplay(TYPE2, 0);
        this->irisPossition();
        printArray();
    }
}

bool ME200S::AutoFocus(bool enable)
{
    char vector_data[2];
    Vector<char> paramaters(vector_data);
    if (enable)
    {
        paramaters.push_back('0');
        /* code */
    }
    else
    {
        paramaters.push_back('1');
        /* code */
    }

    sendCommand(FOCUS, paramaters);
    return commandReplay(TYPE2, 2);
}

bool ME200S::oneShotAF()
{
    char vector_data[2];
    Vector<char> paramaters(vector_data);

    paramaters.push_back('A');

    sendCommand(FOCUS, paramaters);
    return commandReplay(TYPE2, 2);
}

/*
Iris Possitions
F2.8 = C
F4.0 = B
F5.6 = A
F8.0 = 9
F11 =  8
F16 =  7
F22 =  6
*/
bool ME200S::irisPossition()
{
    char vector_data[2];
    Vector<char> paramaters(vector_data);

    paramaters.push_back(0x2);
    Serial1.flush();
    sendCommand(GET_IRIS_POSITION, paramaters);
    return commandReplay(TYPE2, 2);
}
void ME200S::printArrayDirect()
{
    Serial.println();
    int size = receivedData_vec.size();
    Serial.print("Direct array print: ");
    for (auto i = 0; i < size; i++)
    {
        Serial.print(commandReplyStorage[i]);
    }
    Serial.println();
}
void ME200S::printReplyStorage()
{
    Serial.println("Reply Storage Contents: ");
    for (auto i = 0; i < replyStorageSize; i++)
    {
        Serial.print((char)replyStorage[i]);
    }
}