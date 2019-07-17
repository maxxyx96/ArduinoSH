/**
 * File: Bluetooth Dimmer ArduinoSH
 * Authors: Ong Yu Xuan & Aw Rui Huan 
 * Version: 1.0
 * 
 * This project works hand in hand with an application we
 * developed in MIT App Inventor, called ArduinoSH. We hope 
 * that this code provides useful insights and comments on 
 * the fundamentals of building a smart home by enabling 
 * connection with an Arduino Uno, an Arduino-compatible 
 * bluetooth module as well as a smartphone with 
 * our ArduinoSH application downloaded.
 * 
 * Links: To be generated.
 */


/**
 * SoftwareSerial allows us to convert most Arduino Uno 
 * pins to RX and TX, and is useful for adaptaion purposes. 
 */
#include <SoftwareSerial.h>


/**
 * In our Lineup, we utilise Pins 9 for RX,
 * and Pin 8 for TX. 
 * 
 * To facilitate understanding, "Bluetooth" is used to 
 * reference our communications between ArduinoSH and this code.
 */
SoftwareSerial Bluetooth(9, 8); // RX, TX

/**
 * Definition and mapping of buttons & states to numbers to simplify the 
 * code's understanding. 
 * 
 * The table lists our default mapping of pins & values to each buttons and state.  
 * 
 * ||Uno Pin|| ButtonNo || ArduinoSH State (Value) || Arduino State (Value) ||
 * ||   11  || Button 1 ||     On (49) Off (48)    ||      On (1) Off (0)   ||
 * ||   10  || Button 2 ||     On (51) Off (50)    ||      On (3) Off (2)   ||
 * ||   06  || Button 3 ||     On (53) Off (52)    ||      On (5) Off (4)   ||
 * ||   05  || Button 4 ||     On (55) Off (54)    ||      On (7) Off (6)   ||
 */
#define BUTTON_1 11
#define BUTTON_1_OFF 48 //'0'
#define BUTTON_1_ON 49 //'1'

#define BUTTON_2 10
#define BUTTON_2_OFF 50 //'2'
#define BUTTON_2_ON 51 //'3'

#define BUTTON_3 6
#define BUTTON_3_OFF 52 //'4'
#define BUTTON_3_ON 53 //'5'

#define BUTTON_4 5
#define BUTTON_4_OFF 54 //'6'
#define BUTTON_4_ON 55 //'7'

/**
 ****************** Code explaination for Void Setup. *********************
 * 
 * Bluetooth.begin(Baud Rate) starts the serial communication 
 * between the bluetooth module and smartphone. 
 * If baud rate 9600 does not work, try out 38400 as there may 
 * be different factory settings for the Bluetooth Module.
 * 
 * Serial.Begin(9600) is just a method to ensure that the Arduino
 * code written works, and it is not a software fault. To view the text,
 * open the Serial Monitor (Ctrl + Shift + M) & set baud rate to 9600.
 * 
 * pinMode declares the pins as output so that lights etc can be toggled.
 */ 
void setup() {

  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Waiting for command...");
  Bluetooth.println("Send 1 to turn on the LED. Send 0 to turn Off");
  pinMode(BUTTON_1, OUTPUT);
  pinMode(BUTTON_2, OUTPUT);
  pinMode(BUTTON_3, OUTPUT);
  pinMode(BUTTON_4, OUTPUT);
 
}

/**
 ******************** Code explaination for Void Loop ********************
 * 
 * Waits until data sent from our ArduinoSH Application is received 
 * by our bluetooth module, and reads the data to determine what is 
 * received, and subsequently, runs the actions that needs to be taken. 
 * 
 * In this case, our actions are turning on and off the pins defined 
 * at the top of our code with the desired intensity by using analogWrite. 
 */

//array variable to store the data
int data[2]; 

void loop() {
  
  //Commands are sent in a list of bytes.
  //Wait until 2 bytes arrive.
  while ((Bluetooth.available() < 2)) {} 
 
  //First byte entered will be the Button, Second byte will be the intensity of dimmer
  for (int i = 0; i < 2; i ++) {
    data[i]  = Bluetooth.read();
  }
  
  //Assign the datas to the individual variables for easier decoding. 
  int button = data[0];
  int intensity = data[1];

  
  if (button == BUTTON_1_ON) {
    Serial.print("button 1 on with intensity : ");
    Serial.println(intensity);    
    analogWrite(BUTTON_1, intensity);
  }

  else if (button == BUTTON_1_OFF) {
    intensity = 0;
    Serial.println("button 1 off");
    analogWrite(BUTTON_1, intensity);
  }

  else if (button == BUTTON_2_ON) {
    Serial.print("button 2 on with intensity : ");
    Serial.println(intensity);
    analogWrite(BUTTON_2, intensity);
  }

  else if (button == BUTTON_2_OFF) {
    intensity = 0;
    Serial.println("button 2 off");
    analogWrite(BUTTON_2, intensity);
  }

  else if (button == BUTTON_3_ON) {
    Serial.print("button 3 on with intensity : ");
    Serial.println(intensity);
    analogWrite(BUTTON_3, intensity);
  }

  else if (button == BUTTON_3_OFF) {
    intensity = 0;
    Serial.println("button 3 off");
    analogWrite(BUTTON_3, intensity);
  }

  else if (button == BUTTON_4_ON) {
    Serial.print("button 4 on with intensity : ");
    Serial.println(intensity);
    analogWrite(BUTTON_4, intensity);
  }

  else if (button == BUTTON_4_OFF) {
    intensity = 0;
    Serial.println("button 4 off");
    analogWrite(BUTTON_4, intensity);
  }
    
  else {} //Do nothing

}
