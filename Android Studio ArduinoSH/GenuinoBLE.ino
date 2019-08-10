#include <CurieBLE.h>
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEService motorService("19B10010-E8F2-537E-4F6C-D104768A1214");
BLEService led2Service("19B10020-E8F2-537E-4F6C-D104768A1214");
BLEService motor2Service("19B10030-E8F2-537E-4F6C-D104768A1214");
//BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic motorCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic led2Characteristic("19B10021-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic motor2Characteristic("19B10031-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
const int ledPin = 9;     //Pin to use for LED
const int motorPin = 3;   //Pin to use for motor
const int led2Pin = 6;    //Pin to use for LED2
const int motor2Pin = 5;  //Pin to use for motor2
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);    //Set LED pin to output mode
  pinMode(motorPin, OUTPUT);  //Set motor pin to output mode
  pinMode(led2Pin, OUTPUT);   //Set LED pin to output mode
  pinMode(motor2Pin, OUTPUT); //Set motor pin to output mode
  //Begin initialization 
  BLE.begin();
  //Set advertised local name and service UUID:
  BLE.setLocalName("Orbital");              //Set name to appear when bluetooth devices are scanned using phone
  BLE.setAdvertisedService(ledService);
  BLE.setAdvertisedService(motorService);
  BLE.setAdvertisedService(led2Service);
  BLE.setAdvertisedService(motor2Service);
  
  //Add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);
  motorService.addCharacteristic(motorCharacteristic);
  led2Service.addCharacteristic(led2Characteristic);
  motor2Service.addCharacteristic(motor2Characteristic);
  //Add service
  BLE.addService(ledService);
  BLE.addService(motorService);
  BLE.addService(led2Service);
  BLE.addService(motor2Service);
  //Set the initial value for the characeristic:
  switchCharacteristic.setValue(0);
  motorCharacteristic.setValue(0);
  led2Characteristic.setValue(0);
  motor2Characteristic.setValue(0);
  
  //Start advertising
  BLE.advertise();
  Serial.println("BLE LED Peripheral");
}
void loop() {
  //Listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();
  //If a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    //Print the central's MAC address:
    Serial.println(central.address());
    //While the central is still connected to peripheral:
    while (central.connected()) {
      //If data is sent from phone to Arduino 101, use the value to control the appliances:
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value() == 0) {   //When data is 0, turn LED off
          Serial.println("LED off");
          digitalWrite(ledPin, LOW);
        }
        
        else{                                     //Else brighten the led according to the value sent
          Serial.println("LED1 on");
          int light = map(switchCharacteristic.value(),0,49,0,255); //Re-maps a number from one range to another
          analogWrite(ledPin, light);
        }
        
      }
      
      else if(motorCharacteristic.written()) {
          if (motorCharacteristic.value() == 0) { //When data is 0, turn motor off
            Serial.println("Motor off");
            digitalWrite(motorPin, LOW);
          }
          
          else {                             
            Serial.println("Motor on");           //Else spin the motor according to value sent
            analogWrite(motorPin, motorCharacteristic.value());
            Serial.println(motorCharacteristic.value());
          }
      }
      else if (led2Characteristic.written()) {
        if (led2Characteristic.value() == 0) {   //When data is 0, turn LED off
          Serial.println("LED off");
          digitalWrite(led2Pin, LOW);
        }
        
        else {                                  //Else brighten the led according to the value sent
        Serial.println("LED on");
          int lights = map(led2Characteristic.value(),0,49,0,255);
          analogWrite(led2Pin, lights);
        }
      }
      else if (motor2Characteristic.written()) {
        
        if (motor2Characteristic.value() == 0) {    //When data is 0, turn motor off
            Serial.println("Motor2 off");
            digitalWrite(motor2Pin, LOW);
          }
          
        else {
          Serial.println("Motor2 on");              //Else spin the motor according to value sent
          analogWrite(motor2Pin, motor2Characteristic.value());
          Serial.println(motor2Characteristic.value());
        }
      }
    }
    //When the central disconnects, print it out:
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
