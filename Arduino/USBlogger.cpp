#include "RS485.h"
#include <Arduino_UnifiedStorage.h>
/* Function to initialize USB storage to file
	Be careful! If file exists it will be deleted! */
int USBInit(USBStorage &uStorage, UFile &file, const char *filename){
	String writeText = "";
  int bytesAvailible = 0;
  int bytesWritten = 0;
  if (!uStorage.isMounted()){    
    if (!uStorage.begin()) {
        printlnRS485("Failed to initialize USB storage");
        return 1;
    }
  	else{printlnRS485("USB storage initialized");}
  }
    // Check if USB storage is mounted
    if (!uStorage.isMounted()) {
        printlnRS485("USB storage not mounted");
        return 2;
    }
    // Create or open the file
    file = uStorage.getRootFolder().createFile(filename, FileMode::APPEND);
    // Check if file was created
    if (!file.exists()) {
        printlnRS485("Failed to create or open logFile.csv!");
        return 3;
    }
    // Check if there is anything written
    if (!file.changeMode(FileMode::READ)){
      printlnRS485("Failed to open in READ mode!");
      return 4;
    }
    bytesAvailible = file.available();
    printRS485("Bytes in file: ");
    printRS485(bytesAvailible);
    printlnRS485("");
    if (bytesAvailible == 0) {
      // Open to write
      if (!file.changeMode(FileMode::APPEND)){
        printlnRS485("Failed to open in APPEND mode!");
        return 5;
      }
    }
    else{
    //Create new file with new header
        //Drop the old file
          if (!file.remove()){
            printlnRS485("Failed to remove previous file!");
            return 5;
          }
          // Create new file
          file = uStorage.getRootFolder().createFile(filename, FileMode::APPEND);
          // Check if file was created
          if (!file.exists()) {
            printlnRS485("Failed to create or open logFile.csv!");
            return 3;
          }
    }
	return 0; 
}


// Function to write a row of data into the file
bool writeRow(const char *content){
}	
