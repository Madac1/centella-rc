#include <SoftwareSerial.h>

// INSTRUCCIONES DE ACTIVIDAD
// Reescribir correctamente donde está conectado cada pin del Puente H (linea 14)
// Hacer un diagrama en el cuaderno para ilustrar las 8 direcciones del control remoto.
// Abrir el monitor serial para descubrir el comando que envia el control al centella.
// Anotar a que dirección corresponde cada comando.
// Escribir correctamente el comando que corresponde a cada dirección. (linea 40)

// Configuración del puerto serial por software
SoftwareSerial bluetoothSerial(10, 11); // RX, TX

// Pines de control del puente H
#define B_1A 0
#define B_1B 0
#define A_1A 0
#define A_1B 0

void setup() {
  // Configurar pines como salida
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);

  // Inicializar serial
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  Serial.println("Listo para recibir comandos.");
}

void loop() {
  if (bluetoothSerial.available()) {
    char comando = bluetoothSerial.read();
    Serial.print("Comando recibido: ");
    Serial.println(comando);

    // Control del robot según el comando recibido
    if (comando == 'x' ){ //Detenido
      digitalWrite(B_1A, HIGH);
      digitalWrite(B_1B, HIGH);
      digitalWrite(A_1A, HIGH);
      digitalWrite(A_1B, HIGH);
    }
    
    if (comando == 'x' ){ //Avanzar ⬆
      digitalWrite(B_1A, HIGH);
      digitalWrite(B_1B, LOW);
      digitalWrite(A_1A, HIGH);
      digitalWrite(A_1B, LOW);
    }

    if (comando == 'x'){ // Retroceder ⬇
      digitalWrite(B_1A, LOW);
      digitalWrite(B_1B, HIGH);
      digitalWrite(A_1A, LOW);
      digitalWrite(A_1B, HIGH);
    }

    if (comando == 'x' ){// Girar izquierda ⬅
      digitalWrite(B_1A, LOW);
      digitalWrite(B_1B, HIGH);
      digitalWrite(A_1A, HIGH);
      digitalWrite(A_1B, LOW);
    }

    if (comando == 'x' ){// Girar derecha ➡
      digitalWrite(B_1A, HIGH);
      digitalWrite(B_1B, LOW);
      digitalWrite(A_1A, LOW);
      digitalWrite(A_1B, HIGH);
    }

    if (comando == 'x' ){// Avanzar a la izquierda ⬆⬅
      analogWrite(B_1A, 255);
      analogWrite(B_1B, 0);
      analogWrite(A_1A, 150);
      analogWrite(A_1B, 0);
    }

    if (comando == 'x' ){// Retroceder a la izquierda ⬇➡
      analogWrite(B_1A, 0);
      analogWrite(B_1B, 255);
      analogWrite(A_1A, 0);
      analogWrite(A_1B, 150);
    }

    if (comando == 'x' ){// Avanzar a la derecha ⬆➡
      analogWrite(B_1A, 150);
      analogWrite(B_1B, 0);
      analogWrite(A_1A, 255);
      analogWrite(A_1B, 0);
    }

    if (comando == 'x' ){// Retroceder a la derecha ⬇➡
      analogWrite(B_1A, 0);
      analogWrite(B_1B, 150);
      analogWrite(A_1A, 0);
      analogWrite(A_1B, 255);
    }
  }
}
