#include <ME200S.hpp>
ME200S::ME200S(/* args */)
{
    receivedData_vec.setStorage(commandReplyStorage);
    Serial1.begin(9600); // setup the storage for the reply;
}

ME200S::~ME200S()
{
}
bool ME200S::cameraVersionRequest() // array size is hard coded as it does not change;
{
    char vector_data[1];
    Vector<char> paramaters(vector_data);
    paramaters.push_back('0');
    sendCommand(CAMERA_VERSION_REQUEST, paramaters);
    return commandReplay(TYPE1, 10);
}

bool ME200S::sendCommand(uint16_t Command,Vector<char> Paramaters_)
{
    Serial1.print(Header_,HEX);
    Serial1.print(Device_Num_,HEX);
    Serial1.print(Command,HEX);
    for (unsigned int i = 0; i < Paramaters_.size(); i++)
    {
        Serial1.print(Paramaters_[i],HEX);
    }
    Serial1.print(End_Mark_,HEX);
    return true;
}

bool ME200S::commandReplay(int commandType, int Paramater_Size)
{
    while (millis() % commandType != 0) // while the command hasnt timed out;
    {   
        if (Serial1.available() >= Paramater_Size)
        {
            Serial1.println(Paramater_Size);
            for (auto i = 0; i < Paramater_Size; i++)
            {
                receivedData_vec.push_back(Serial.read());
            }
            recivedBufferSize = Paramater_Size;
            return true;
        }
    }
    return false;
}
bool ME200S::receivedData(char data[])
{
    if (receivedData_vec.size() > 0)
    {
        for (auto i = receivedData_vec.size(); i < 1; i--)
        {
            data[i] = receivedData_vec.back();
            receivedData_vec.pop_back();
        }
        return true;
    }
    return false;
}