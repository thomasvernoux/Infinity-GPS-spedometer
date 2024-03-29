
#include "functions.h"

// This custom version of delay() ensures that the gps object
// is being "fed".
void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

// This function prints a floating point number with a specified length and precision.
// If the number is not valid, it prints asterisks.
void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}


// This function prints an integer with a specified length.
// If the integer is not valid, it prints asterisks.
void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

// This function prints the date and time from a GPS object.
// If the date or time is not valid, it prints asterisks.
void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

void afficherMessage(TM1637Display& display, const char *message) {
  uint8_t data[] = {0, 0, 0, 0};
  
  // Parcourez chaque caractère du message
  for (int i = 0; i < strlen(message) && i < 4; i++) {
    // Obtenez le code segment pour le caractère actuel
    data[i] = display.encodeDigit(message[i]);
  }
  
  // Affichez les données sur l'afficheur
  display.setSegments(data);
}

void defilerMessage(TM1637Display& display, const __FlashStringHelper *message, int delayTime) {
  PGM_P p = reinterpret_cast<PGM_P>(message); // Convert the __FlashStringHelper* to PGM_P
  int len = strlen_P(p); // Get the length of the message using strlen_P()
  
  for (int i = 0; i < len; i++) { // Loop through each character of the message
    uint8_t data[] = {0, 0, 0, 0}; // Initialize an array to hold the encoded characters
    
    // Loop through each digit of the display
    for (int j = 0; j < 4; j++) {
      if (i + j < len) { // Check if the current character is within the length of the message
        // Get the current character and convert it to a digit
        char c = (char)pgm_read_byte_near(p + i + j);
        data[j] = display.encodeDigit(c - '0'); // Encode the digit for display
      }
    }
    
    display.setSegments(data); // Display the encoded digits on the display
    
    delay(delayTime); // Wait before moving to the next character
  }
}




