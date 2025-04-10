#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>

// Remplace ces valeurs par tes informations Wi-Fi
const char* ssid = "testest";
const char* password = "Motdepasse";

// Serveur web sur le port 80
WebServer server(80);

const int buttonG = 12;
const int ledG = 18;
const int buttonY = 14;
const int ledY = 5;
const int buttonB = 27;
const int ledB = 17;
const int buttonR = 26;
const int ledR = 16;
const int buzzer = 32;

//MQTT
const char* publishTopic = "/simon/online";
const char* subscribeTopic = "/gilbert/#";
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;
const char* clientId = "PremierTest"; // Must be unique on the broker
WiFiClient espClient;
PubSubClient client(espClient);

bool gState = false;
bool yState = false;
bool bState = false;
bool rState = false;

double listInput[] = {5, 17, 17, 18, 5, 16};
int inputsNumber = 6;

// put function declarations here:
//int myFunction(int, int);
int update();
void IRAM_ATTR gTrigger();
void IRAM_ATTR yTrigger();
void IRAM_ATTR bTrigger();
void IRAM_ATTR rTrigger();
void connectToMQTT();
int sequence(int i, double *tab);
void lightUp(int a);
void soundUp(int a);
void inputCheck(double *tab);

void setup() {
  Serial.begin(115200);

  //WiFi.begin(ssid, password);
  //while (WiFi.status() != WL_CONNECTED) {
    //delay(1000);
    //Serial.println("Connexion au Wi-Fi...");
  //}
  //Serial.println("Connecté au Wi-Fi");
  

  //server.begin();
  //Serial.println("Serveur démarré");
  //Serial.println(WiFi.localIP());


  pinMode(buttonG, INPUT_PULLUP);
  attachInterrupt(buttonG, gTrigger, CHANGE);
  pinMode(ledG, OUTPUT);

  pinMode(buttonY, INPUT_PULLUP);
  attachInterrupt(buttonY, yTrigger, CHANGE);
  pinMode(ledY, OUTPUT);

  pinMode(buttonB, INPUT_PULLUP);
  attachInterrupt(buttonB, bTrigger, CHANGE);
  pinMode(ledB, OUTPUT);

  pinMode(buttonR, INPUT_PULLUP);
  attachInterrupt(buttonR, rTrigger, CHANGE);
  pinMode(ledR, OUTPUT);

  pinMode(buzzer, OUTPUT);
}

void loop() {
  //server.handleClient();
  Serial.println("Starting loop");
  sequence(0, listInput);
  Serial.println("Sequence End");
  lightUp(0);
  Serial.println("Lights shutDown");
  inputCheck(listInput);
  Serial.println("Update done");
}

int update() {
  int light = 0;
  if (gState) {
    digitalWrite(ledG, HIGH);
    tone(buzzer, 262, 10);
    light = ledG;
  } else {
    digitalWrite(ledG, LOW);
  }

  if (yState) {
    digitalWrite(ledY, HIGH);
    tone(buzzer, 294, 10);
    light = ledY;
  } else {
    digitalWrite(ledY, LOW);
  }

  if (bState) {
    digitalWrite(ledB, HIGH);
    tone(buzzer, 330, 10);
    light = ledB;
  } else {
    digitalWrite(ledB, LOW);
  }

  if (rState) {
    digitalWrite(ledR, HIGH);
    tone(buzzer, 349, 10);
    light = ledR;
  } else {
    digitalWrite(ledR, LOW);
  }
  return light;
}

void IRAM_ATTR gTrigger() {
  gState = !gState;
}

void IRAM_ATTR yTrigger() {
  yState = !yState;
}

void IRAM_ATTR bTrigger() {
  bState = !bState;
}

void IRAM_ATTR rTrigger() {
  rState = !rState;
}

void connectToMQTT() {
  client.setServer(mqttServer, mqttPort);
  Serial.print("Connecting to MQTT broker");
  while (!client.connected()) {
    if (client.connect(clientId)) {
      Serial.println("\nConnected to MQTT broker");
    } else {
      Serial.print(".");
    }
  }
}

int sequence(int i, double *tab){
  if (inputsNumber < i){
    return 0;
  }
  int input = tab[i];
  lightUp(input);
  soundUp(input);
  delay(1000);
  return sequence(i+1, tab);
}

void lightUp(int a){
  if (a == 5){
    digitalWrite(a, HIGH);
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(18, LOW);
  }
  else if (a == 16){
    digitalWrite(a, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(17, LOW);
    digitalWrite(18, LOW);
  }
  else if (a == 17){
    digitalWrite(a, HIGH);
    digitalWrite(16, LOW);
    digitalWrite(5, LOW);
    digitalWrite(18, LOW);
  }
  else if (a == 18){
    digitalWrite(a, HIGH);
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(5, LOW);
  }
  else{
    digitalWrite(5, LOW);
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(18, LOW);
  }
}

void soundUp(int a){
  if (a == 5){
    tone(buzzer, 294, 10);
  }
  else if (a == 16){
    tone(buzzer, 349, 10);
  }
  else if (a == 17){
    tone(buzzer, 330, 10);
  }
  else if (a == 18){
    tone(buzzer, 262, 10);
  }
}

void inputCheck(double *tab){
  int i = 0;
  bool interrupt = false;
  while (i < inputsNumber){
    bool waitingInput = true;
    int playerInput = 0;
    while (waitingInput){
      playerInput = update();
      if (playerInput != 0){
        waitingInput = false;
        if (playerInput =! tab[i]){
          interrupt = true;
          tone(buzzer, 180, 10);
          digitalWrite(ledR, HIGH);
        }
        else{
          tone(buzzer, 412, 10);
          digitalWrite(ledG, HIGH);
        }
      }
    }
    i ++;
    if (interrupt){
      i = inputsNumber;
    }
  }
}