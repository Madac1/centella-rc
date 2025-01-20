#include <SoftwareSerial.h>

//RECORDATORIO: Invertir TX y RX para enviar comandos AT.

// *** ZONA DE CONFIGURACIÓN ***
String nombreBluetooth = "CENTELLA, EL ESCURRI";  // Nombre deseado para el módulo Bluetooth
String contrasenaBluetooth = "0909";             // Contraseña deseada (4 dígitos)
int version = 1;
// ******************************

// Configuración del puerto serial por software (pines para Arduino Uno)
SoftwareSerial bluetoothSerial(10, 11);  // RX, TX

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  // Interfaz de bienvenida
  Serial.println(F("=============================="));
  Serial.println(F("  Proyecto: cambiarNombreBluetooth"));
  Serial.println(F("  Configurando módulo HC-06..."));
  Serial.println(F("==============================\n"));

  // Prueba de comunicación con el módulo
  Serial.print(F("Verificando conexión con el módulo... "));
  if (!enviarComandoAT("AT")) {
    Serial.println(F("¡OK!\n"));
  } else {
    Serial.println(F("ERROR: Verifica TX y RX (¿Invertidos?)"));
    while (true);  // Detiene ejecución si no hay comunicación
  }

  // Configurar el nombre del módulo
  Serial.print(F("Cambiando nombre del Bluetooth... "));
  if (!enviarComandoAT("AT+NAME" + nombreBluetooth)) {
    Serial.println(F("¡Nombre cambiado con éxito!\n"));
  } else {
    Serial.println(F("ERROR al cambiar el nombre.\n"));
  }

  // Configurar la contraseña del módulo
  Serial.print(F("Cambiando contraseña del Bluetooth... "));
  if (!enviarComandoAT("AT+PIN" + contrasenaBluetooth)) {
    Serial.println(F("¡Contraseña cambiada con éxito!\n"));
  } else {
    Serial.println(F("ERROR al cambiar la contraseña.\n"));
  }

  Serial.println(F("=============================="));
  Serial.println(F("  Configuración completada."));
  Serial.println(F("  Desconecta y usa el módulo."));
  Serial.println(F("=============================="));
}

void loop() {
  // Reenvío de datos entre el monitor serial y el Bluetooth
  if (bluetoothSerial.available()) Serial.write(bluetoothSerial.read());
  if (Serial.available()) bluetoothSerial.write(Serial.read());
}

// Función para enviar un comando AT y verificar su respuesta
bool enviarComandoAT(String comando) {
  bluetoothSerial.print(comando);  // Enviar sin salto de línea
  delay(1000);  // Dar tiempo al módulo para responder

  String respuesta = "";
  while (bluetoothSerial.available()) {
    respuesta += (char)bluetoothSerial.read();
  }

  return (respuesta.indexOf("OK") == -1);  // Retorna 0 si tuvo éxito, 1 si falló
}
