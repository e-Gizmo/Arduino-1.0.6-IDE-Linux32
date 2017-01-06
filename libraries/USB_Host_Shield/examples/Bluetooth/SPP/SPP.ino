/*
 Example sketch for the RFCOMM/SPP Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or 
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <SPP.h>
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
SPP SerialBT(&Btd); // This will set the name to the defaults: "Arduino" and the pin to "1234"
//SPP SerialBT(&Btd, "Lauszus's Arduino","0000"); // You can also set the name and pin like so

boolean firstMessage = true;

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nSPP Bluetooth Library Started"));
}
void loop() {
  Usb.Task();
  if(SerialBT.connected) {
    if(firstMessage) {
      firstMessage = false;
      SerialBT.println(F("Hello from Arduino")); // Send welcome message
    }
    if(Serial.available())
      SerialBT.print(Serial.read());
    if(SerialBT.available())
      Serial.write(SerialBT.read());
  } 
  else 
    firstMessage = true;
}
