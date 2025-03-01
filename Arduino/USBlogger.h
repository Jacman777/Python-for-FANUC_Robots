// USBlogger.h - Library to save data to the file on USB storage
#ifndef USBlogger_h
#define USBlogger_h
#include <Arduino_UnifiedStorage.h>
/* Function to initialize USB storage to file
	Be careful! If header text will change all previous data will be deleted! 
	Return 0 if all good*/
int USBInit(USBStorage &uStorage,UFile &file, const char *filename);

// Function to write a row of data into the file
int writeRow(const char *content);   
#endif

 
