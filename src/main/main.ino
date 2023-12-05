
// Include the header file for the functions
#include "functions.h"




// Define the pins for the GPS module
const int RXPin = 4, TXPin = 3;
const uint32_t GPSBaud = 9600;

// Define the pins for the TM1637 display
const int CLK = 5; 
const int DIO1 = 6; 
const int DIO2 = 7; 
const int DIO3 = 8; 

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
  Serial.println(F("Cruising the sea, With GPS you foresee"));
  defilerMessage(display1, F("Cruising the sea, With GPS you foresee"), 5);


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

  // Format the hours and minutes for a more attractive display
  char timeStr[6];
  sprintf(timeStr, "%02d:%02d", hours, minutes);

  // Display the time on the display
  display1.showNumberDecEx(atoi(timeStr), 0b11100000, true);

  /*
  Speed display -------------------------------------------------------------------
  */

  // Get the current speed in km/h
  float speedKmph = gps.speed.kmph();

  // Convert the speed to knots
  float speedKnots = speedKmph / 1.852;

  // Convert the speed to an integer for display
  int intSpeed = (int)speedKnots;

  // Get the decimal part of the speed
  int decSpeed = (int)((speedKnots - intSpeed) * 10);

  // Combine the integer and decimal parts for display
  int displaySpeed = intSpeed * 10 + decSpeed;

  // Display the speed on the second display
  display2.showNumberDec(displaySpeed, true, 4, 0);

  /*
  Curse display -------------------------------------------------------------------
  */

  // Get the current course
  float course = gps.course.deg();

  // Convert the course to an integer for display
  int intCourse = (int)course;

  // Get the decimal part of the course
  int decCourse = (int)((course - intCourse) * 10);

  // Combine the integer and decimal parts for display
  int displayCourse = intCourse * 10 + decCourse;

  // Display the course on the third display
  display3.showNumberDec(displayCourse, true, 4, 0);





  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10){
    Serial.println(F("No GPS data received: check wiring"));
    afficherMessage(display1, "ERR");
    afficherMessage(display2, "ERR");
    afficherMessage(display3, "ERR");}
}

















