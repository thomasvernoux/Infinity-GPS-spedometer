#include <TM1637Display.h>

// Définir les broches pour le module TM1637
const int CLK1 = 5; 
const int DIO1 = 6; 
const int DIO2 = 7; 

// Créer une instance de la classe TM1637Display
TM1637Display display1(CLK1, DIO1);
TM1637Display display2(CLK1, DIO2);

void setup() {
  // Initialiser l'afficheur
  display1.setBrightness(7); // Réglez la luminosité (0-7)
  display2.setBrightness(7); // Réglez la luminosité (0-7)
}

void loop() {
  // Afficher un nombre sur l'afficheur
  display1.showNumberDec(1234);
  display2.showNumberDec(3223);

  // Ajoutez ici d'autres traitements ou modifications d'affichage en fonction de vos besoins
}
