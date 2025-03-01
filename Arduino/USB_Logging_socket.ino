//#include <Arduino_UnifiedStorage.h>
//#include <ArduinoRS485.h>
#include "RS485.h"
#include "USBlogger.h"
#include <Ethernet.h>

USBStorage usbStorage;
UFile logFile;

// Initialize the Ethernet server 
// with the MAC, IP address and port you want to use
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 177);
EthernetServer server(9900);

int buttonState = 0;
int result = 0; 
bool USBconnected = false;
bool fileInit = false;
bool unmountReq = false;

void connectionCallbackMethod(){
    USBconnected = true;
    fileInit = false;
}

void disconnectedCallbackMethod(){
    USBconnected = false;
    fileInit = false;
    digitalWrite(LED_USER, LOW);
}

void setup() {
  int result = 0;
  // Initialize USER LED (Blue) as an output
  pinMode(LED_USER, OUTPUT);
  // Initialize USER Button as an input
  pinMode(BTN_USER, INPUT);
  // Interrupt configuration for User Button
  attachInterrupt(digitalPinToInterrupt(BTN_USER), userBtnISR, RISING);
  // Configure RS485 with a baud rate of 9600
  configureRS485(9600);
  printlnRS485("RS485 Initialized");
  // Start the Ethernet connection and the server
  Ethernet.begin(mac, ip);
  // Start server
  server.begin();
  //Check if User Button is pressed at startup
  buttonState = digitalRead(BTN_USER);

  if (buttonState == HIGH){//User Button not pressed
    // Initialize USB storage
    usbStorage = USBStorage();
    usbStorage.onConnect(connectionCallbackMethod);
    usbStorage.onDisconnect(disconnectedCallbackMethod);
    logFile = UFile();
    char header[150] = "Timestamp,Device_ID,Data_Type,Value\n";
    if (!USBInit(usbStorage, logFile, "logFile.csv")){
      USBconnected = true;
      fileInit = true;
      digitalWrite(LED_USER, HIGH);
    }
  }
}

void loop() {
  char charLine[150]; //TO BE moved to global variables!!!

  // Listen for incoming clients
  EthernetClient client = server.available();
  
  if (unmountReq){
    unmountUSB();
  }
  
  if (USBconnected && !fileInit){
    if (!USBInit(usbStorage, logFile, "logFile.csv")){
      fileInit = true;
      digitalWrite(LED_USER, HIGH);
     }
  }
  if (client) {
    printRS485("New client connected IP: ");
    const char* address = client.remoteIP().toString().c_str();  
    printlnRS485((char*)address);
    String currentData = "";
    while (client.connected()) {
      if (unmountReq){
        unmountUSB();
      }
      if (USBconnected && !fileInit){
        if (!USBInit(usbStorage, logFile, "logFile.csv")){
          fileInit = true;
          digitalWrite(LED_USER, HIGH);
        }
      }
      
      if (client.available()) { //Some bytes are availible to read
        char c = client.read();      
        currentData += c;
        if (c == '\n') {
          // Parse the data
          strcpy(charLine,currentData.c_str());
          printlnRS485(charLine);
          //Write data if log file is initialised
          if (fileInit){
             logFile.write(charLine);
          }
          currentData = "";
        }
      }
    }
    // Give the client time to receive the data
    delay(1);
    // Close the connection
    client.stop();
    printlnRS485("Client disconnected");
  }
}

void userBtnISR(){
  unmountReq = true;
}

void unmountUSB(){
   if (usbStorage.isMounted()){
    if (fileInit){
      logFile.close();
      fileInit = false;
    }
      usbStorage.unmount();
      USBconnected = false;
      printlnRS485("USB unmounted");
  }
  else{
    printlnRS485("USB is not mounted");
    USBconnected = false; 
  }
  digitalWrite(LED_USER, LOW);
  unmountReq = false;
}