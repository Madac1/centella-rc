#include <SoftwareSerial.h>

// Pines para el módulo Bluetooth
int pinRX = 10;
int pinTX = 11;

// Configurar Bluetooth en los pines RX y TX
SoftwareSerial bluetooth(pinRX, pinTX);

void setup() {
  // Iniciar comunicación con Bluetooth y monitor serial
  bluetooth.begin(9600);
  Serial.begin(9600);

  // Mensaje inicial
  Serial.println("Chat iniciado.");
}

void loop() {
  // Revisar si hay algo escrito en el monitor serial
  if (Serial.available() > 0) {
    int letra = Serial.read();  // Leer una letra
    bluetooth.write(letra);    // Enviar esa letra por Bluetooth
  }

  // Revisar si hay algo enviado desde el celular
  if (bluetooth.available() > 0) {
    int letra = bluetooth.read();  // Leer una letra
    Serial.write(letra);          // Mostrar esa letra en el monitor serial
  }
}
