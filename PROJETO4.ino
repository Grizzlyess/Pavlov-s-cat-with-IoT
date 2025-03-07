#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Ultrasonic.h>
#include "Servo.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978



// Configuração Wi-Fi
const char* ssid = "Nome da rede";
const char* password = "senha";

// Configuração do servidor web
ESP8266WebServer server(80);

Servo foodServo;
const int triggerPin = 5;  // Pino Trigger do sensor ultrassônico
const int echoPin = 4;     // Pino Echo do sensor ultrassônico
const int buzzerPin = 14;  // Pino do buzzer
const int servoPin = 0;   // Pino do servo motor

Ultrasonic ultrasonic(triggerPin, echoPin);
const float distancia_maxima=30;

int melody1[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5}; // Melodia para alimentação
int melody2[] = {NOTE_G4, NOTE_F4, NOTE_D4, NOTE_C4}; 
int durations[] = {4, 4, 4, 4}; // Duração de cada nota

void playMelody(int melody[], int noteDurations[]) {
  // Itera sobre as notas da melodia
  for (int i = 0; i < 4; i++) {
    int noteDuration = 1000 / noteDurations[i];   // Calcula a duração de cada nota
    tone(buzzerPin, melody[i], noteDuration);     // Toca a nota no buzzer
    delay(noteDuration * 1.30);                   // Adiciona uma pausa entre as notas
    noTone(buzzerPin);                            // Para o som do buzzer
  }
}

bool achei_um_gatinho() {

    float distancia = ultrasonic.read(); // Mede a distância em cm
  
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    return distancia < distancia_maxima;  // Se a distância for menor que 30cm, gato detectado!
}

void dispenseFood() {
  foodServo.write(90);
  delay(1000);
  foodServo.write(0);
}

void handleTocarMusicaCerta() {
    int melody[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5}; 
    Serial.println("Comando recebido: Tocar Música Certa!");
    server.send(200, "text/plain", "Tocando a musica certa !!! Procurando um gatinho..."); // Notas da música
    playMelody(melody1, durations);
    playMelody(melody1, durations);
    playMelody(melody1, durations);
    
    
    if (achei_um_gatinho()) {
        Serial.println("GATO DETECTADO! Liberando comida...");
        dispenseFood();
        server.send(200, "text/plain", "Achei um gatinho!!! Liberando petiscos...");
    } else {
        Serial.println("Nenhum gato detectado. Comida não será liberada.");
        server.send(200, "text/plain", "Nao achei nenhum gatinho...");
    }
}


// Rota para tocar música errada
void handleTocarMusicaErrada() {
  Serial.println("Comando recebido: Tocar Música Errada!");
  server.send(200, "text/plain", "Tocando a musica errada !!!");
  playMelody(melody2, durations);
  playMelody(melody2, durations);
  playMelody(melody2, durations);
  
}

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado!");
    Serial.println(WiFi.localIP());

    foodServo.attach(servoPin);
    foodServo.write(0);

    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);

    server.on("/tocar_musica_certa", handleTocarMusicaCerta);
    server.on("/tocar_musica_errada", handleTocarMusicaErrada);

    server.begin();
}

void loop() {
  server.handleClient();
}

