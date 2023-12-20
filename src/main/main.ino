
// Include the header file for the functions
#include "functions.h"




// Define the pins for the GPS module
const int RXPin = 7, TXPin = 6;
const uint32_t GPSBaud = 9600;

// Define the pins for the TM1637 display
const int CLK = 5; 
const int DIO1 = 4; 
const int DIO2 = 3; 
const int DIO3 = 2; 

const int brightness = 7;

// Create an instance of the TinyGPSPlus class
TinyGPSPlus gps;

// Create instances of the TM1637Display class
TM1637Display display1(CLK, DIO1);
TM1637Display display2(CLK, DIO2);
TM1637Display display3(CLK, DIO3);

// Create a serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  // Begin the serial communication
  Serial.begin(115200);
  ss.begin(GPSBaud);

  // Initialize the display and set the brightness
  display1.setBrightness(brightness); // Réglez la luminosité (0-7)
  display2.setBrightness(brightness); // Réglez la luminosité (0-7)
  display3.setBrightness(brightness); // Réglez la luminosité (0-7)

  // Print a startup message
  //Serial.println(F("Cruising the sea, With GPS you foresee"));



}

void loop()
{

  /*
    Time display -------------------------------------------------------------------
  */

  // Get the current hours and minutes
  int hours = gps.time.hour();
  int minutes = gps.time.minute();

  // Adjust for timezone (Paris is UTC +1)
  hours = hours + 1;

  // Adjust for daylight saving time
  if ((month() > 3 && month() < 10) || (month() == 3 && day() >= 26) || (month() == 10 && day() < 29)) {
    hours = hours + 1;
  }

  // Handle overflow
  if (hours >= 24) {
    hours = hours - 24;
  }

  // Display the time on the display
  display1.showNumberDecEx((100*hours + minutes), 0b11100000, true);



  /*
  Speed display -------------------------------------------------------------------
  */

  // Get the current speed in km/h
  float speedKmph = gps.speed.kmph();

  // Convert the speed to knots
  float speedKnots = speedKmph ;// 1.852; //   /!\ attention romu

  int speedKnots_100;
  speedKnots_100 = 100 * speedKnots;

  // Display the speed on the second display
  display2.showNumberDecEx(speedKnots_100, 0b11100000, true);



  /*
  Curse display -------------------------------------------------------------------
  */

  // Get the current course
  float course = gps.course.deg();

  Serial.println(course);

  
  display3.showNumberDec(course, false, 4, 0);





  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10){
    Serial.println(F("No GPS data received: check wiring"));
    afficherMessage(display1, "ERR");
    afficherMessage(display2, "ERR");
    afficherMessage(display3, "ERR");}
}

















