////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////  Author: Jiri Kucera                                   ////
////  Description: ESP32 bluetooth classic                  ////
////                                                        ////
////  Using board: ESP32 DEV KIT V1                         ////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////  include libraries                                     ////
////////////////////////////////////////////////////////////////

#include "BluetoothSerial.h" 

////////////////////////////////////////////////////////////////
////  Check and set Bluetooth Serial                        ////
////////////////////////////////////////////////////////////////

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


BluetoothSerial SerialBT;

////////////////////////////////////////////////////////////////
////  Set LED pin                                           ////
////////////////////////////////////////////////////////////////

// GPIO where LED is connected
const int ledPin =  5;

////////////////////////////////////////////////////////////////
////  Declare incoming message variables                    ////
////////////////////////////////////////////////////////////////

String incomingMessage;
char incomingChar; 

////////////////////////////////////////////////////////////////
////  Setup                                                 ////
////////////////////////////////////////////////////////////////

void setup() {
  // set digital pin to control as an output
  pinMode(ledPin, OUTPUT);

  //initialize serial for debugging 
  Serial.begin(115200);

  //initialize bluetooth
  SerialBT.begin("MyESP32"); 
  Serial.println("The device started, now you can pair it with bluetooth!");
}

////////////////////////////////////////////////////////////////
////  Loop                                                  ////
////////////////////////////////////////////////////////////////

void loop() {
  // if text arrived in from BT serial...
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      incomingMessage += String(incomingChar);
    }
    else{
      incomingMessage = "";
    }
    Serial.write(incomingChar);  
  }
  
  //check messageincomingChar
  if (incomingMessage=="led_on")
  {
    digitalWrite(ledPin, HIGH);
    SerialBT.println("LED on");
  }
  if (incomingMessage=="led_off")
  {
    digitalWrite(ledPin, LOW);
    SerialBT.println("LED off");
  }
  if (incomingMessage=="help")
  {
    SerialBT.println("Send 'led_on' to turn LED on");
    SerialBT.println("Send 'lef_off' to turn LED on");
  }    
}
