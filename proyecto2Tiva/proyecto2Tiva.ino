
#include <SPI.h>
#include <SD.h>
#include "pitches.h"

File archivo;
//***********************************************************************
//definicion de pines
//***********************************************************************

#define boton1 PF_4
#define boton2 PF_0
#define NOTE_C4_1 260

//***********************************************************************
//Prototipos de funciones
//***********************************************************************
void contBitsSuma(void);
void comunicacionESP(void);
void guardarSD(void);
void musicaRead(void);
void musicaWrite(void);
//*****************************************************************************
// Variables Globales
//*****************************************************************************
//float voltajePot = 0;
int temperatura = 0;
int contador = 0;
String mensaje = "";
int banderaBTN1 = 0;
int banderaBTN2 = 0;
int buzzerPin  = PF_1;

int melodyRead[] = {
   NOTE_B4, NOTE_A4, NOTE_G4, NOTE_B4,NOTE_A4,NOTE_G4};
   
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurationsRead[] = {
  4, 4, 2, 4, 4, 2};

int melodyWrite[] = {
   NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4,NOTE_B4,NOTE_A4,
   NOTE_G4};
   
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurationsWrite[] = {
  4, 4, 4, 4, 4, 4, 2};

//***********************************************************************
//CONFIGURACION
//***********************************************************************

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);

//INICIALIZACION DE LA SD----------------------
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  pinMode(PA_3, OUTPUT);
  SPI.setModule(0);
//Estamos inicializando la SD
  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
 //-------------------------------------------------

  
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);

  pinMode(buzzerPin,OUTPUT);
}

void loop() {

//  voltajePot = ((analogRead(pot2))*0.008);

  comunicacionESP();
  //contBitsSuma(); 

  
 // Serial.print(voltajePot);
 // Serial.print("  ");
  Serial.print(contador);
  Serial.print("  ");
  Serial.println(temperatura);


  if ( digitalRead(boton2) == LOW && banderaBTN2 == 0) {
    musicaWrite();
    guardarSD();
    banderaBTN2 = 1;
    delay(250);
     banderaBTN2 = 0;
    mensaje = "";
  }



  if ( digitalRead(boton1) == LOW  && banderaBTN1 == 0) {
    musicaRead();
    contador = temperatura ;
    banderaBTN1 = 1;
    delay(250);
    banderaBTN1 = 0;
    mensaje = "";
  }

  //delay(150);
}

//*****************************************************************************
//Funcion para realizar la suma y resta con los botones
//*****************************************************************************
/*void contBitsSuma() {
  banderaBTN1 = 1;
  banderaBTN2 = 1;
  if ( digitalRead(boton2) == LOW && banderaBTN2 = 1) {
    guardarSD();
    banderaBTN2 = 0;
    mensaje = "";
  }



  if ( digitalRead(boton1) == LOW  && banderaBTN1 = 1) {
    contador = temperatura ;
    banderaBTN1 = 0;
    mensaje = "";
  }
}*/

//*****************************************************************************
//Funcion para recibir datos de esp
//*****************************************************************************
void comunicacionESP(){
  if(Serial2.available()){//si hay algun dato esperando a ser leido...
    temperatura = Serial2.read();//el dato es guardado en la variable
    }  
  }
  

  //*****************************************************************************
//Funcion para Guardar datos en la sd
//*****************************************************************************
void guardarSD(){
    //Parametros: (tipo de arcuivo, que se va a hacer)
    archivo = SD.open("Datos.txt", FILE_WRITE);
  
    // if the file opened okay, write to it:
    if (archivo) {
      Serial.print("Writing to test.txt...");
      archivo.println(temperatura);
      // close the file:
      archivo.close();
      Serial.println("done.");
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening Datos.txt");
    }
  }



  //*****************************************************************************
//Funcion Musica al leer dato
//*****************************************************************************
void musicaRead(){
    for (int thisNote = 0; thisNote < 26; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurationsRead[thisNote];
    tone(buzzerPin, melodyRead[thisNote],noteDuration);

    int pauseBetweenNotes = noteDuration + 50;      //delay between pulse
    delay(pauseBetweenNotes);
    
    noTone(buzzerPin);                // stop the tone playing
  }
}

  //*****************************************************************************
//Funcion para musica al guardar dato
//*****************************************************************************
void musicaWrite(){
    for (int thisNote = 0; thisNote < 26; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurationsWrite[thisNote];
    tone(buzzerPin, melodyWrite[thisNote],noteDuration);

    int pauseBetweenNotes = noteDuration + 50;      //delay between pulse
    delay(pauseBetweenNotes);
    
    noTone(buzzerPin);                // stop the tone playing
    }
 }
