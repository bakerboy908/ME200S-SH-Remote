//Errors
#define MODE_ERROR                  0x80        // In case of receiving the command unable to execute under Camera during the receiving the Status
#define PARAMETER_ERROR             0x40        // In case of over value of parameter or wrong parameter length
#define COMMAND_ERROR               0x20        // In case of receiving the wrong commands (not prepared commands)
#define CAMERA_BUSY                 0x10        // Camera is unable to execute the commands in process to execute the former command.
#define SYSTOM_ERROR                0x1         // In case that the fatal accidents occur for some reason.

//Commands
#define CAMERA_VERSION_REQUEST      0x01BE      // Return the camera’s firmware version
#define SET_IRIS_POSITION           0x01A6      // set the iris possittion 
#define FOCUS                       0x01A1      //Command for all focus's
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