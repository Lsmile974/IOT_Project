#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

// Remplace par tes informations Wi-Fi
const char* ssid = "Nom_du_réseau";
const char* password = "Mot_de_passe";

AsyncWebServer server(80);

// Pins GPIO pour les LEDs
int redPin = 32; 
int greenPin = 33;
int bluePin = 25;
int yellowPin = 26;

// Pins GPIO pour les boutons
int buttonRed = 4;
int buttonGreen = 5;
int buttonBlue = 18;
int buttonYellow = 19;

// Séquence de couleurs du jeu
String sequence[100]; 
int sequenceIndex = 0; 
bool acceptingInput = false;

void setup() {
  // Démarre le moniteur série
  Serial.begin(115200);
  
  // Connexion Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion...");
  }
  Serial.println("Connecté au Wi-Fi");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());

  // Initialisation des pins LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  
  // Initialisation des pins boutons
  pinMode(buttonRed, INPUT_PULLUP);
  pinMode(buttonGreen, INPUT_PULLUP);
  pinMode(buttonBlue, INPUT_PULLUP);
  pinMode(buttonYellow, INPUT_PULLUP);

  // Serve la page HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Démarrer le serveur
  server.begin();
}

void loop() {
  // Vérifier si l'on attend une entrée de l'utilisateur (après avoir joué une séquence)
  if (acceptingInput) {
    // Si l'utilisateur appuie sur le bouton rouge
    if (digitalRead(buttonRed) == LOW) {
      delay(200); // anti-rebond
      handleInput("red");
    }
    // Si l'utilisateur appuie sur le bouton vert
    if (digitalRead(buttonGreen) == LOW) {
      delay(200); // anti-rebond
      handleInput("green");
    }
    // Si l'utilisateur appuie sur le bouton bleu
    if (digitalRead(buttonBlue) == LOW) {
      delay(200); // anti-rebond
      handleInput("blue");
    }
    // Si l'utilisateur appuie sur le bouton jaune
    if (digitalRead(buttonYellow) == LOW) {
      delay(200); // anti-rebond
      handleInput("yellow");
    }
  }

  // Ajouter ici d'autres logiques ou vérifier si la séquence est terminée
}

// Fonction pour gérer l'entrée utilisateur
void handleInput(String color) {
  // Vérifier si la couleur correspond à la séquence
  if (color == sequence[sequenceIndex]) {
    Serial.println("Bon choix !");
    sequenceIndex++;

    if (sequenceIndex == sizeof(sequence) / sizeof(sequence[0])) {
      Serial.println("Gagné, nouvelle séquence !");
      // Passer à une nouvelle séquence
      nextRound();
    }
  } else {
    Serial.println("Erreur, Game Over !");
    // Réinitialiser le jeu
    resetGame();
  }
}

// Fonction pour démarrer une nouvelle séquence
void nextRound() {
  sequenceIndex = 0;
  acceptingInput = false;

  // Ajouter une nouvelle couleur aléatoire à la séquence
  String newColor = getRandomColor();
  sequence[sequenceIndex] = newColor;
  Serial.println("Nouvelle séquence : " + newColor);
  
  // Jouer la séquence
  playSequence();
}

// Fonction pour choisir une couleur aléatoire
String getRandomColor() {
  int randomIndex = random(0, 4);
  switch (randomIndex) {
    case 0: return "red";
    case 1: return "green";
    case 2: return "blue";
    case 3: return "yellow";
  }
  return "";
}

// Fonction pour jouer la séquence de couleurs
void playSequence() {
  acceptingInput = false;
  for (int i = 0; i <= sequenceIndex; i++) {
    String color = sequence[i];
    lightUpColor(color);
    delay(1000); // Attendre avant de jouer la prochaine couleur
  }
  acceptingInput = true; // Laisser l'utilisateur entrer sa réponse après la séquence
}

// Fonction pour allumer les LEDs
void lightUpColor(String color) {
  // Éteindre toutes les LEDs avant d'en allumer une nouvelle
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(yellowPin, LOW);

  if (color == "red") {
    digitalWrite(redPin, HIGH);
  } else if (color == "green") {
    digitalWrite(greenPin, HIGH);
  } else if (color == "blue") {
    digitalWrite(bluePin, HIGH);
  } else if (color == "yellow") {
    digitalWrite(yellowPin, HIGH);
  }
}

// Fonction pour réinitialiser le jeu
void resetGame() {
  sequenceIndex = 0;
  acceptingInput = false;
  Serial.println("Réinitialisation du jeu...");
  // Éteindre toutes les LEDs
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(yellowPin, LOW);
}
