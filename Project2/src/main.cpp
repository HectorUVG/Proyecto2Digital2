//Hector Manuel de Leon Salguero
//Universidad del Valle de Guatmala
//19511
//Proyecto 2 
//Electronica digital 2
//*****************************************************************************
//Librerias
//*****************************************************************************
#include <Arduino.h>

//*****************************************************************************
//Definicion de pines
//*****************************************************************************
//sensor
#define sensor 35

//*****************************************************************************
//Prototipos de funciones
//*****************************************************************************

//para el promedio
void mediaMovilADC(void);

//temperatura a decenas, unidades y decimales
void tempAUnidades(void);
//*****************************************************************************
//Variables Globales
//*****************************************************************************
float temperatura = 0.0;

//variables al separar el valor del sensor
int decena = 0;
int unidad = 0;
int decimal = 0;

//Variables para sensor
int adcLM35 = 0;
int voltaje = 0;

//delay1
unsigned long lastTime;
unsigned int sampleTime = 500;

//delay1
unsigned long lastTime2;
unsigned int sampleTime2 = 3000;

//media movil
int numLecturas = 10;
float bufferLecturas[10];
int indexLecturas = 0;
long mAvgSuma = 0;
long adcfiltrado = 0;

//temperatura a decenas, unidades y decimales
int temp = 0;
//*****************************************************************************
//ISR
//*****************************************************************************

//*****************************************************************************
//Configuracion
//*****************************************************************************

void setup() {

  Serial.begin(115200);
  lastTime = millis();//delay de 500milisegundos
  lastTime2 = millis();//delay de 3000milisegundos
}


//*****************************************************************************
//Loop principal
//*****************************************************************************
void loop() {

   //llamar a la funcion del promedio
  mediaMovilADC();

  //definicion de decena unidad y decimal
  tempAUnidades();
}

//*****************************************************************************
//Funcion para media movil
//*****************************************************************************

void mediaMovilADC(){

  if(millis() - lastTime >= sampleTime){
    lastTime = millis(); //el if es un delay de 500milisegundos
  

    adcLM35 = (analogReadMilliVolts(sensor));//realiza la lectura convirtiendo a voltios

    mAvgSuma = mAvgSuma - bufferLecturas[indexLecturas] + adcLM35;
    bufferLecturas[indexLecturas] = adcLM35;
    indexLecturas++;
    if(indexLecturas >= numLecturas){
      indexLecturas = 0;
    }
    adcfiltrado = mAvgSuma/numLecturas;

    temperatura = adcfiltrado/10;
    
    Serial.print("ADCmillivolts: ");
    Serial.print(adcLM35);
    Serial.print(" mediaMovil: ");
    Serial.print(adcfiltrado);
    Serial.print(" temperatura: ");
    Serial.println(temperatura);
  }



}

//*****************************************************************************
//Funcion para separar decenas unidades y decimales
//*****************************************************************************

void tempAUnidades(){
  
  /**
   * Esta funcion descompone la temperatura para poder identificar las
   * decenas, unidades y decimales
   */
  
  temp = adcfiltrado;
  decena = temp/100;
  temp = temp - (decena*100);
  unidad = temp/10;
  temp = temp - (unidad*10);
  decimal = temp;
 
}

