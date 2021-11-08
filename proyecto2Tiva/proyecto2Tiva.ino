

//***********************************************************************
//definicion de pines
//***********************************************************************

#define boton1 PF_4
#define boton2 PF_0

//***********************************************************************
//Prototipos de funciones
//***********************************************************************
void contBitsSuma(void);
void comunicacionESP(void);
//*****************************************************************************
// Variables Globales
//*****************************************************************************
//float voltajePot = 0;
float temperatura = 0;
int contador = 0;
String mensaje = "";
//***********************************************************************
//CONFIGURACION
//***********************************************************************

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
}

void loop() {

//  voltajePot = ((analogRead(pot2))*0.008);

  comunicacionESP();
  contBitsSuma(); 

  
 // Serial.print(voltajePot);
 // Serial.print("  ");
  Serial.print(contador);
  Serial.print("  ");
  Serial.println(temperatura);

  //delay(150);
}

//*****************************************************************************
//Funcion para realizar la suma y resta con los botones
//*****************************************************************************
void contBitsSuma() {
/*  if ( digitalRead(boton1) == LOW && contador < 255) {
    contador = contador + 1 ;
    mensaje = "";

  }

  if ( digitalRead(boton1) == LOW && contador >= 255) {
    contador = 0 ;

    mensaje = "";

  }

  if (digitalRead(boton2) == LOW && contador > 0) {
    contador = contador - 1 ;
    mensaje = "";

  }
  if ( digitalRead(boton2) == LOW && contador <= 0) {
    contador = 254 ;
    mensaje = "";

  }*/

  if ( digitalRead(boton1) == LOW ) {
    contador = temperatura ;
    mensaje = "";
  }
}

//*****************************************************************************
//Funcion para recibir datos de esp
//*****************************************************************************
void comunicacionESP(){
  if(Serial2.available()){//si hay algun dato esperando a ser leido...
    temperatura = Serial2.read();//el dato es guardado en la variable
    
  }
}
