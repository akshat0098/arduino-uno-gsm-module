  /*********
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <SoftwareSerial.h>
#include <TinyGPS.h>


// Configure software serial port
SoftwareSerial SIM900(0, 1); 


#include "TinyGPS.h"

TinyGPS gps;

void setup() {
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  // Give time to your GSM shield log on to network
  delay(20000);

  
}

void SendMessage()
{
Serial.println ("Sending Message please wait….");
SIM900.println("AT+CMGF=1"); //Text Mode initialisation
delay(1000);
Serial.println ("Set SMS Number");
SIM900.println("AT+CMGS=\"+919369489827\"\r"); // Receiver’s Mobile Number
delay(1000);
Serial.println ("Set SMS Content");
SIM900.println("Bhai kya haal hain? (Brother how are you?) this messege has been sent through Arduino Uno not a mobile phone wink wink ");// Messsage content
delay(100);
Serial.println ("Done");
SIM900.println((char)26);// delay(1000);
Serial.println ("Message sent succesfully");

}

void loop() {
  delay(20000);
  SendMessage();

    while (Serial.available()) {
    int c = Serial.read();
    gps.encode(c);
    Serial.println("oh no, I'm never gonna exit this while loop");
  }

  long latitude, longitude;
  gps.get_position(&latitude, &longitude, NULL);
  Serial.print("Latitude:  "); Serial.println(latitude);
  Serial.print("Longitude:  "); Serial.println(longitude);
  
  
  //callSomeone();
}

void callSomeone() {
  // REPLACE THE X's WITH THE NUMER YOU WANT TO DIAL
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("ATD +919369489827;");
  delay(100);
  SIM900.println();
  
 // In this example, the call only last 30 seconds
 // You can edit the phone call duration in the delay time
  delay(30000);
  // AT command to hang up
  SIM900.println("ATH"); // hang up
}
