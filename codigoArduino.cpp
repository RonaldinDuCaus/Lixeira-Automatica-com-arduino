#include <Servo.h>

Servo tampa;

// Pinos do sensor ultrassônico
const int trigPin = 9;
const int echoPin = 8;

// Pino do servo
const int servoPin = 10;

// Distância para detectar (em cm)
const int distanciaLimite = 15;

long duracao;
int distancia;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  tampa.attach(servoPin);

  // Começa fechada
  tampa.write(0);

  Serial.println("Lixeira automatica iniciada");
}

void loop() {

  // Envia pulso ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lê o tempo do eco
  duracao = pulseIn(echoPin, HIGH);

  // Calcula distância
  distancia = duracao * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Se detectar objeto perto
  if (distancia > 0 && distancia <= distanciaLimite) {

    Serial.println("Movimento detectado - Abrindo tampa");

    // Abre a tampa
    tampa.write(180);

    // Fica aberta por 5 segundos
    delay(5000);

    // Fecha a tampa
    tampa.write(0);

    Serial.println("Tampa fechada");

    // Pequeno tempo para evitar repetir instantaneamente
    delay(1000);
  }

  delay(200);
}
