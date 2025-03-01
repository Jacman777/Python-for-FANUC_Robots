# Python-for-FANUC_Robots
This repository contains example usage of Python executor functionality in R-50iA FANUC Robot controllers. 

This example demonstrate how to make a simple robot data logger on USB drive attached to Arduino Opta (micro PLC with IoT capabilities). 
Robot is connected by socket communication to send data to Arduino. 

<img src="https://github.com/Jacman777/Python-for-FANUC_Robots/blob/ef5fff10cd939185dc9e29b05abf3f38b2fad9f9/Images/connections.png" width=70% height=70%>


# Requirements to run example code
- FANUC Robot with R-50iA controller and minimum system software V10.10P/11  
- R553 (HMI Device) robot software option
- Arduino Opta (versions: AFX00001 or AFX00002 for RS-485 status print)
- USB stick to log data
  
Usage at Robot side:
![Robot program and settings](https://github.com/Jacman777/Python-for-FANUC_Robots/blob/af1d2c808c88d34105c07645e0fbf96fcf143948/Images/TP_screen.png)

RS-485 terminal output (optional):
![Terminal output](https://github.com/Jacman777/Python-for-FANUC_Robots/blob/af1d2c808c88d34105c07645e0fbf96fcf143948/Images/RealTerm_RS485.gif)

Example CSV log file: [Logfile](https://github.com/Jacman777/Python-for-FANUC_Robots/blob/af1d2c808c88d34105c07645e0fbf96fcf143948/Output/logFile.csv)

# Useful links
- [Introduction of Python for FANUC Robots](https://www.fanuc.co.jp/ja/product/new_product/2025/202501_r50ia.html)
- [Arduino library to handle USB storage](https://docs.arduino.cc/libraries/arduino_unifiedstorage/#class%20%60UFile%60)
- [USB data logging for Opta](https://docs.arduino.cc/tutorials/opta/usb-data-logging/)

