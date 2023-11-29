#include <SoftwareSerial.h>

// Définir les broches RX et TX pour la communication avec le module NEO-6M
// Assurez-vous de connecter correctement les broches RX et TX du module GPS à ces broches.
const int rxPin = 4; // Connectez le TX du module GPS à la broche 2 de l'Arduino
const int txPin = 3; // Connectez le RX du module GPS à la broche 3 de l'Arduino

// Créer une instance de la classe SoftwareSerial
SoftwareSerial gpsSerial(rxPin, txPin);

void setup() {
  // Ouvrir la communication série standard à la vitesse de votre module GPS
  Serial.begin(115200);
  
  // Ouvrir la communication série avec le module GPS à la vitesse de communication de ce module
  gpsSerial.begin(9600);
}

void loop() {
  // Lire les données du module GPS et les afficher dans le moniteur série
  if (gpsSerial.available()) {
    char c = gpsSerial.read();
    Serial.print(c);
  }
  
  // Vous pouvez ajouter d'autres traitements ici en fonction de vos besoins
}
