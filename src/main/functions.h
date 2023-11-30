


#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <TM1637Display.h>


extern SoftwareSerial ss;
extern TinyGPSPlus gps;


void smartDelay(unsigned long ms);
void printFloat(float val, bool valid, int len, int prec);
void printInt(unsigned long val, bool valid, int len);
void printDateTime(TinyGPSDate &d, TinyGPSTime &t);
void printStr(const char *str, int len);
void afficherMessage(TM1637Display& display, const char *message);
void defilerMessage(TM1637Display& display, const char *message, int delayTime);





