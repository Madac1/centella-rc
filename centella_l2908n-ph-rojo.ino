#include <SoftwareSerial.h>

// Configuración del puerto serial por software
SoftwareSerial bluetoothSerial(10, 11); // RX, TX

// Pines de dirección (digitales)
#define DIR_IZQ_A 6
#define DIR_IZQ_B 7
#define DIR_DER_A 2
#define DIR_DER_B 4

// Pines de velocidad (PWM)
#define VEL_IZQ 5
#define VEL_DER 3

// Factores de calibración de los motores (ajusta según sea necesario)
#define FACTOR_IZQ 1.0  // Ajusta la velocidad del motor izquierdo
#define FACTOR_DER 0.8  // Ajusta la velocidad del motor derecho
#define FACTOR_GIRO 0.2

// Velocidades mínima y máxima
#define VEL_MIN 50   // Valor PWM mínimo (excepto 0)
#define VEL_MAX 250  // Valor PWM máximo

int velocidad = 250; // Valor inicial de velocidad

class Motor{
  private:
    char motorPin;
    int target_velocity;
    bool input_a;
    bool input_b;
    unsigned long timestamp;
    int update_constant;
  public:
    int current_velocity;
    void velset(int target_vel);
    // 0 = stop, 1 = forward, 2 = backward
    //void direction(char direction);
    Motor(){
      motorPin = 0;
      target_velocity = 0;
      current_velocity = 0;
      input_a = 0;
      input_b = 0;
      timestamp = 0;
      update_constant = 4;
    };
    Motor(int pin, const int update_const){
      motorPin = pin;
      target_velocity = 0;
      current_velocity = 0;
      input_a = 0;
      input_b = 0;
      timestamp = 0;
      update_constant = update_const;
    };
};

void Motor::velset(int target_vel){
  if(target_vel == current_velocity){
    return;
  }
  if(target_vel > current_velocity)
  {
    current_velocity = current_velocity + update_constant;
  }
  else if(target_vel < current_velocity)
  {
    current_velocity = current_velocity - update_constant;
  }
  if(current_velocity >= 250){current_velocity = 250;}

  analogWrite(motorPin,current_velocity);
  return;
}

// 0 = stop, 1 = forward, 2 = backward
//void Motor::direction(char direction){}

void setup() {
  // Configurar pines como salida
  pinMode(DIR_IZQ_A, OUTPUT);
  pinMode(DIR_IZQ_B, OUTPUT);
  pinMode(DIR_DER_A, OUTPUT);
  pinMode(DIR_DER_B, OUTPUT);
  pinMode(VEL_IZQ, OUTPUT);
  pinMode(VEL_DER, OUTPUT);

  // Inicializar serial
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  Serial.println("Listo para recibir comandos.");
}

Motor motor_der(VEL_DER, 10);
Motor motor_izq(VEL_IZQ, 10);

void loop() {
  if (bluetoothSerial.available()) {
    char comando = bluetoothSerial.read();
    //Serial.print("Comando recibido: ");
    //Serial.println(comando);
    Serial.print(motor_izq.current_velocity);
    Serial.print(" ");
    Serial.println(motor_der.current_velocity);

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

    // DETENER con todos en HIGH
    if (comando == 'S') {
      digitalWrite(DIR_IZQ_A, HIGH);
      digitalWrite(DIR_IZQ_B, HIGH);
      digitalWrite(DIR_DER_A, HIGH);
      digitalWrite(DIR_DER_B, HIGH);
      motor_der.velset(0);
      motor_izq.velset(0);
    } 
    else if (comando == 'F') { // Avanzar
      digitalWrite(DIR_IZQ_A, HIGH);
      digitalWrite(DIR_IZQ_B, LOW);
      digitalWrite(DIR_DER_A, HIGH);
      digitalWrite(DIR_DER_B, LOW);
      motor_izq.velset(velocidad * FACTOR_IZQ);
      motor_der.velset(velocidad * FACTOR_DER);
    } 
    else if (comando == 'B') { // Retroceder
      digitalWrite(DIR_IZQ_A, LOW);
      digitalWrite(DIR_IZQ_B, HIGH);
      digitalWrite(DIR_DER_A, LOW);
      digitalWrite(DIR_DER_B, HIGH);
      motor_izq.velset(velocidad * FACTOR_IZQ);
      motor_der.velset(velocidad * FACTOR_DER);
    } 
    else if (comando == 'L') { // Girar izquierda
      digitalWrite(DIR_IZQ_A, LOW);
      digitalWrite(DIR_IZQ_B, HIGH);
      digitalWrite(DIR_DER_A, HIGH);
      digitalWrite(DIR_DER_B, LOW);
      motor_izq.velset(velocidad * FACTOR_IZQ);
      motor_der.velset(velocidad * FACTOR_DER);
    } 
    else if (comando == 'R') { // Girar derecha
      digitalWrite(DIR_IZQ_A, HIGH);
      digitalWrite(DIR_IZQ_B, LOW);
      digitalWrite(DIR_DER_A, LOW);
      digitalWrite(DIR_DER_B, HIGH);
      motor_izq.velset(velocidad * FACTOR_IZQ);
      motor_der.velset(velocidad * FACTOR_DER);
    } 
    else if (comando == 'G') { // Avanzar a la izquierda
      digitalWrite(DIR_IZQ_A, HIGH);
      digitalWrite(DIR_IZQ_B, LOW);
      digitalWrite(DIR_DER_A, HIGH);
      digitalWrite(DIR_DER_B, LOW);
      motor_izq.velset(velocidad * FACTOR_IZQ * FACTOR_GIRO);
      motor_der.velset(velocidad * FACTOR_DER);
    } 
    else if (comando == 'H') { // Retroceder a la izquierda
      digitalWrite(DIR_IZQ_A, LOW);
      digitalWrite(DIR_IZQ_B, HIGH);
      digitalWrite(DIR_DER_A, LOW);
      digitalWrite(DIR_DER_B, HIGH);
      motor_izq.velset(velocidad * FACTOR_IZQ * FACTOR_GIRO);
      motor_der.velset(velocidad * FACTOR_DER);
    } 
    else if (comando == 'I') { // Avanzar a la derecha
      digitalWrite(DIR_IZQ_A, HIGH);
      digitalWrite(DIR_IZQ_B, LOW);
      digitalWrite(DIR_DER_A, HIGH);
      digitalWrite(DIR_DER_B, LOW);
      motor_izq.velset(velocidad * FACTOR_IZQ);
      motor_der.velset(velocidad * FACTOR_DER * FACTOR_GIRO);
    } 
    else if (comando == 'J') { // Retroceder a la derecha
      digitalWrite(DIR_IZQ_A, LOW);
      digitalWrite(DIR_IZQ_B, HIGH);
      digitalWrite(DIR_DER_A, LOW);
      digitalWrite(DIR_DER_B, HIGH);
      motor_izq.velset(velocidad * FACTOR_IZQ);
      motor_der.velset(velocidad * FACTOR_DER * FACTOR_GIRO);
    }
  }
}


