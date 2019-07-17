/**
 * File: Bluetooth Generic ArduinoSH
 * Version: 1.0
 * Authors: Ong Yu Xuan & Aw Rui Huan 
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
 * ||   13  || Button 1 ||     On (49) Off (48)    ||      On (1) Off (0)   ||
 * ||   12  || Button 2 ||     On (51) Off (50)    ||      On (3) Off (2)   ||
 * ||   11  || Button 3 ||     On (53) Off (52)    ||      On (5) Off (4)   ||
 * ||   10  || Button 4 ||     On (55) Off (54)    ||      On (7) Off (6)   ||
 */
#define BUTTON_1 13
#define BUTTON_1_OFF '0'
#define BUTTON_1_ON '1'

#define BUTTON_2 12
#define BUTTON_2_OFF '2'
#define BUTTON_2_ON '3'

#define BUTTON_3 11
#define BUTTON_3_OFF '4'
#define BUTTON_3_ON '5'

#define BUTTON_4 10
#define BUTTON_4_OFF '6'
#define BUTTON_4_ON '7'

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
 * pinMode declares the pins as output so that lights etc can be toggled.t
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
 * at the top of our code. 
 */
void loop() {
  if (Bluetooth.available()){ 
    int Data = Bluetooth.read();

    //Button 4's configuration
    if ( Data == BUTTON_4_ON ){  
      digitalWrite(BUTTON_4 , 1);
      Serial.println("Button 4 turned On!");
    }
    else if ( Data == BUTTON_4_OFF ){
       digitalWrite(BUTTON_4,0);
       Serial.println("Button 4 turned Off!");
    }
    
    //Button 3's configuration
    else if ( Data == BUTTON_3_ON ){  
      digitalWrite(BUTTON_3 , 1);
      Serial.println("Button 3 turned On!");
    }
    else if ( Data == BUTTON_3_OFF ){
       digitalWrite(BUTTON_3,0);
       Serial.println("Button 3 turned Off!");
    }
    
    //Button 2's configuration
    else if ( Data == BUTTON_2_ON ){  
      digitalWrite(BUTTON_2,1);
      Serial.println("Button 2 turned On!");
    }
    else if ( Data == BUTTON_2_OFF ){
       digitalWrite(BUTTON_2,0);
       Serial.println("Button 2 turned Off!");
    }  
    
    //Button 1's configuration
    else if ( Data == BUTTON_1_ON ){  
      digitalWrite(BUTTON_1,1);
      Serial.println("Button 1 turned On!");
    }
    else if ( Data == BUTTON_1_OFF ){
       digitalWrite(BUTTON_1,0);
       Serial.println("Button 1 turned Off!");
    }
    
    //Anything else is ignored.
    else{}
  }
  
delay(100) ;
}
