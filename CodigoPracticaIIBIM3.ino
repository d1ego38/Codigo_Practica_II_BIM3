//Librerias
#include <Wire.h>                   //libreria para usar el protocolo i2c
#include <SparkFun_ADXL345.h>       //libreria para usar el acelerometro ADXL345

#define azul 2
#define verde1 3
#define verde2 4
#define verde3 5
#define verde4 6
#define amarillo1 7
#define amarillo2 8
#define amarillo3 9
#define rojo1 10
#define rojo2 11

//Constructores
ADXL345 acelerometro_ADXL345 = ADXL345();    //constructor para poder utilizar el acelerometro

//Variables donde guardo las aceleraciones
int x;
int y;
int z;

//Variable donde guardo la magnitud del vector aceleracion
float magnitud_acc;

void setup() {
  Serial.begin(9600);             //Inicio la comunicacion serial del arduino hacia la computadora
  Serial.println("Uso del acelerometro ADXL345");
  acelerometro_ADXL345.powerOn();            //Enciendo el acelerometro
  acelerometro_ADXL345.setRangeSetting(8);   //Configuro la sensibilidad del acelerometro
  
  // Configuración de los pines de la barra LED
  pinMode(azul, OUTPUT);
  pinMode(verde1, OUTPUT);
  pinMode(verde2, OUTPUT);
  pinMode(verde3, OUTPUT);
  pinMode(verde4, OUTPUT);
  pinMode(amarillo1, OUTPUT);
  pinMode(amarillo2, OUTPUT);
  pinMode(amarillo3, OUTPUT);
  pinMode(rojo1, OUTPUT);
  pinMode(rojo2, OUTPUT);
}

void loop() {
  // Obtengo las aceleraciones por cada eje
  acelerometro_ADXL345.readAccel(&x, &y, &z);
  Serial.print("La aceleracion en x es de: ");
  Serial.println(x);
  Serial.print("La aceleracion en y es de: ");
  Serial.println(y);
  Serial.print("La aceleracion en z es de: ");
  Serial.println(z);

  // Obtengo la magnitud del vector aceleracion
  magnitud_acc = sqrtf((x * x) + (y * y) + (z * z));
  Serial.print("La magnitud del vector aceleracion es de: ");
  Serial.println(magnitud_acc);

  int mapeo_intensidad = map(magnitud_acc, 0, 256, 0, 12);

  // Reset de todos los LEDs
  digitalWrite(azul, LOW);
  digitalWrite(verde1, LOW);
  digitalWrite(verde2, LOW);
  digitalWrite(verde3, LOW);
  digitalWrite(verde4, LOW);
  digitalWrite(amarillo1, LOW);
  digitalWrite(amarillo2, LOW);
  digitalWrite(amarillo3, LOW);
  digitalWrite(rojo1, LOW);
  digitalWrite(rojo2, LOW);

  // Encender LEDs según la intensidad
  if (mapeo_intensidad >= 0 && mapeo_intensidad < 2) {
    digitalWrite(azul, HIGH);
  } 
  else if (mapeo_intensidad >= 2 && mapeo_intensidad < 6) {
    digitalWrite(verde1, HIGH);
    digitalWrite(verde2, HIGH);
    digitalWrite(verde3, HIGH);
    digitalWrite(verde4, HIGH);
  } 
  else if (mapeo_intensidad >= 6 && mapeo_intensidad < 9) {
    digitalWrite(amarillo1, HIGH);
    digitalWrite(amarillo2, HIGH);
    digitalWrite(amarillo3, HIGH);
  } 
  else if (mapeo_intensidad >= 9 && mapeo_intensidad <= 12) {
    digitalWrite(rojo1, HIGH);
    digitalWrite(rojo2, HIGH);
  }

  delay(1000);
