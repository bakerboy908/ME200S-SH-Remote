//Errors
#define MODE_ERROR                  0x80        // In case of receiving the command unable to execute under Camera during the receiving the Status
#define PARAMETER_ERROR             0x40        // In case of over value of parameter or wrong parameter length
#define COMMAND_ERROR               0x20        // In case of receiving the wrong commands (not prepared commands)
#define CAMERA_BUSY                 0x10        // Camera is unable to execute the commands in process to execute the former command.
#define SYSTOM_ERROR                0x1         // In case that the fatal accidents occur for some reason.

//Commands
#define CAMERA_VERSION_REQUEST      0x01BE      // Return the camera’s firmware version
#define SET_IRIS_POSITION           0x01A6      // set the iris possittion 
#define GET_IRIS_POSITION           0x01C3      // Request the current iris possition
#define FOCUS                       0x01A1      //Command for all focus's
#define SHUTTER_SPEED_CONTROL       0x01AD      //Control shutter speed
#define SHUTTER_SPEED_CONTROL_FINE  0x019D      //Control shutter speed
#define GAIN_CONTROL_FINE           0x19E       //Gain Control

#define SET_WHITE_BALANCE_KELV      0x01E0      //Set the white balance Temp
#define ND_FILTER_CONTROL           0x01B6      // Control the internal ND Filter
enum COMMAND_TYPE
{
    TYPE1 = 34,
    TYPE2 = 300
};
    
enum APATURE_VALUES
{
    F2_8 = 0xCF,
    F4_0 = 0xBF,
    F5_6 =  0xAF,
    F8 = 0x9F,
    F11 = 0x8F,
    F16 = 0x7F,
    F22 = 0x6F
};

enum GAIN_BALIES
{   
    G0 = 0x00,
    G3 = 0x01,
    G6 = 0x02,
    G9 = 0x03,
    G12 = 0x04,
    G15 = 0x05,
    G18 = 0x06
};