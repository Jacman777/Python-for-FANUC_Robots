#include <ArduinoRS485.h>
#include "RS485.h"
/* Library to configure and print to RS485 communication of Arduino */

void configureRS485(const int baudrate) {
// Function to configure RS485
    const auto bitduration { 1.f / baudrate };
    const auto wordlen { 9.6f }; // OR 10.0f depending on the channel configuration
    const auto preDelayBR { bitduration * wordlen * 3.5f * 1e6 };
    const auto postDelayBR { bitduration * wordlen * 3.5f * 1e6 };

    RS485.begin(baudrate);
    RS485.setDelays(preDelayBR, postDelayBR);
    RS485.noReceive();
}
// Print text without new line
size_t printRS485(char* message)
{
    RS485.beginTransmission();
    auto len = strlen(message);
    RS485.write(message, len);
    RS485.endTransmission();
}
// Print integer number
size_t printRS485(int num)
{
    char message[256] {};
    sprintf(message, "%d", num);
    RS485.beginTransmission();
    auto len = strlen(message);
    RS485.write(message, len);
    RS485.endTransmission();
}
// Print text with new line
size_t printlnRS485(char* message)
{
    printRS485(message);
    RS485.beginTransmission();
    RS485.write('\r');
    RS485.write('\n');
    RS485.endTransmission();
}
