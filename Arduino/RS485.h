// RS485.h - Library to print data to RS485
#ifndef RS485_h
#define RS485_h
#include <ArduinoRS485.h>

// Function to configure RS485
void configureRS485(const int baudrate);

// Print text without new line
size_t printRS485(char* message);

// Print integer number
size_t printRS485(int num);

// Print text with new line
size_t printlnRS485(char* message);

#endif

 
