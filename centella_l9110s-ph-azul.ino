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
#define B_1A 9
#define B_1B 6
#define A_1A 5
#define A_1B 3

// Factores de calibración de los motores (ajusta según sea necesario)
#define FACTOR_IZQ 1.0  // Ajusta la velocidad del motor izquierdo
#define FACTOR_DER 1.0  // Ajusta la velocidad del motor derecho

// Velocidades mínima y máxima
#define VEL_MIN 50   // Valor PWM mínimo (excepto 0)
#define VEL_MAX 255  // Valor PWM máximo


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

    // Si el comando es un número del 0 al 9, o 'q' ajustamos la velocidad
    if ((comando >= '0' && comando <= '9') || comando == 'q') {
      if (comando == '0') {
        velocidad = 0;  // Detenido
      } else if (comando == 'q') {
        velocidad = VEL_MAX;  // Velocidad máxima (100%)
      } else {
        velocidad = map(comando - '0', 1, 9, VEL_MIN, VEL_MAX);
      }

      Serial.print("Nueva velocidad: ");
      Serial.println(velocidad);
      return; // No cambiamos la dirección, solo ajustamos velocidad
    }

    // Control del robot según el comando recibido
    if (comando == 'S' ){ //Detenido
      digitalWrite(B_1A, HIGH);
      digitalWrite(B_1B, HIGH);
      digitalWrite(A_1A, HIGH);
      digitalWrite(A_1B, HIGH);
    }
    
    if (comando == 'F' ){ //Avanzar ⬆
      digitalWrite(B_1A, HIGH);
      digitalWrite(B_1B, LOW);
      digitalWrite(A_1A, HIGH);
      digitalWrite(A_1B, LOW);
    }

    if (comando == 'B'){ // Retroceder ⬇
      digitalWrite(B_1A, LOW);
      digitalWrite(B_1B, HIGH);
      digitalWrite(A_1A, LOW);
      digitalWrite(A_1B, HIGH);
    }

    if (comando == 'L' ){// Girar izquierda ⬅
      digitalWrite(B_1A, LOW);
      digitalWrite(B_1B, HIGH);
      digitalWrite(A_1A, HIGH);
      digitalWrite(A_1B, LOW);
    }

    if (comando == 'R' ){// Girar derecha ➡
      digitalWrite(B_1A, HIGH);
      digitalWrite(B_1B, LOW);
      digitalWrite(A_1A, LOW);
      digitalWrite(A_1B, HIGH);
    }

    if (comando == 'G' ){// Avanzar a la izquierda ⬆⬅
      analogWrite(B_1A, 255);
      analogWrite(B_1B, 0);
      analogWrite(A_1A, 150);
      analogWrite(A_1B, 0);
    }

    if (comando == 'H' ){// Retroceder a la izquierda ⬇➡
      analogWrite(B_1A, 0);
      analogWrite(B_1B, 255);
      analogWrite(A_1A, 0);
      analogWrite(A_1B, 150);
    }

    if (comando == 'I' ){// Avanzar a la derecha ⬆➡
      analogWrite(B_1A, 150);
      analogWrite(B_1B, 0);
      analogWrite(A_1A, 255);
      analogWrite(A_1B, 0);
    }

    if (comando == 'J' ){// Retroceder a la derecha ⬇➡
      analogWrite(B_1A, 0);
      analogWrite(B_1B, 150);
      analogWrite(A_1A, 0);
      analogWrite(A_1B, 255);
    }
  }
}
