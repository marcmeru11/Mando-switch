#include "NSProtocol.h"

// Funcion que devuelve un byte (8 bits) indicando el estado del D-PAD a partir
// del estado de pulsacion de cada uno de sus botones.
// Sacado directamente de los protocolos de la NS:
// Hay combinaciones no validas, que deben sustituirse por "centrado":
// The direction pad is limited to 8 directions plus centered. This means
// some combinations of 4 dpad buttons are not valid and cannot be sent.
// Button down = true(1)
// Valid: Any 1 button down, any 2 adjacent buttons down, no buttons down
// Invalid: all other combinations.
// ej3: Pulsado arriba y abajo => esta combinacion no es valida
// por lo que debe sustituirse por centrado
void NSProtocolDPadButtonsToByte(int up, int down, int left, int right, uint8_t* byte) {

  // Hay que dar a la variable byte el valor correcto en funcion de que botones estan pulsados.
  // Por ej, si solo esta pulsado el boton de arriba, hariamos:
  //
  // *byte = NSGAMEPAD_DPAD_UP;
  //
  // Las constantes cuyo valor puede tomar byte estan definidas en NSTypes.h

  // TO DO

  if(up && !down){

    if(left){

    }else if(right){

    }else{
      *byte=NSGAMEPAD_DPAD_UP;
    }



  }else if(down && !up ){

  }else if(right && !left){

  }else if (left && !right){

  }else{
      *byte=NSGAMEPAD_DPAD_CENTERED;
  }





}

// Funcion que devueve en dos bytes (16 bits) un valor que representa el estado de los primeros 14 botones
// del tipo tNSButtons.
// Segun el protocol NS, el estado de los siguientes 14 botones se envia como un entero de 16 bits
// en el que cada bit representa si el boton correspondiente esta pulsado (1) o no lo esta (0).
// Los dos bits restantes (hasta 16) van a 0:
//
//  Y,
//  B,
//  A,
//  X,
//  LEFT_TRIGGER,
//  RIGHT_TRIGGER,
//  LEFT_THROTTLE,
//  RIGHT_THROTTLE,
//  MINUS,
//  PLUS,
//  LEFT_STICK,
//  RIGHT_STICK,
//  HOME,
//  CAPTURE

// ... estos botones ya se definieron en este mismo orden en el tipo enumerado tNSButtons de NSTypes.h.
// El peso del bit coincide con la posicion del boton en el enumerado (el boton Y va en el 0, el B en el 1...).
// Ejemplo: Si solo esta pulsado el boton B, es decir, el de indice 1, y el resto no lo estan,
 // la secuenca seria: 00000000 00000010
void NSProtocolButtonsToBytes (tNSGamepad nsGamepad,  uint16_t* twoBytes) {

  // Inicializamos *twoBytes a 0
  *twoBytes = 0;

  // Comenzamos por el primero de ellos, el Y (ver tNSButtons de NSTypes.h)
  *twoBytes = *twoBytes | (uint16_t) nsGamepad.buttonsPressed[Y];

  // Siguiente: B
  *twoBytes = *twoBytes | (uint16_t) nsGamepad.buttonsPressed[B] << 1;

  // TO DO: Hacer el resto! 
  // (Requiere uso de mascaras / desplazamientos logicos)
  // ¿Se puede generalizar usando un bucle?

  int i;
  for (i = 0; i < UP; i++) {
       *twoBytes = *twoBytes | (uint16_t) nsGamepad.buttonsPressed[i] << i;

  }
  //!ns si está bien 




}

// Valores por defecto del report que se envia a la Switch (sacado de documentacion "oficial")
void NSProtocolReportDataSetDefaultValues (tNSGamepadReportData*  NSGamepadReportData) {

  NSGamepadReportData->buttons = 0x00;
  NSGamepadReportData->dPad = NSGAMEPAD_DPAD_CENTERED;
  NSGamepadReportData->leftXAxis = 0x80;
  NSGamepadReportData->leftYAxis = 0x80;
  NSGamepadReportData->rightXAxis = 0x80; 
  NSGamepadReportData->rightYAxis = 0x80;
  NSGamepadReportData->filler = 0x00;

}

void NSProtocolSerializeNSGamepadData (tNSGamepad nsGamepad, uint8_t buffer [NS_GAMEPAD_REPORT_SIZE]) {

  tNSGamepadReportData  NSGamepadReportData;
 
  // Cargamos los valores por defecto del report
  // (este paso nos lo podemos saltar cuando tengamos hecho el siguiente!)
  NSProtocolReportDataSetDefaultValues (&NSGamepadReportData);  //!esta en la clase nstypes

  // Pasamos de nsGamepad (tipo tNSGamepad) a tNSGamepadReportData
  NSProtocolButtonsToBytes (nsGamepad, &NSGamepadReportData.buttons);
  // TO DO: Hacer el resto de campos de NSGamepadReportData!




  // Finalmente, serializamos tHID_NSGamepadReportData (metemos los datos en el buffer).
  // TO DO: NO usar memcpy para la estructura completa (puede fallar si la estructura contiene "padding"),
  // hacerlo a mano: un memcpy para cada campo de la estructura, uno a uno, en el mismo orden en que
  // estan definidos en ella (que es el orden que establece el protocolo de la Nintendo Switch).
  //*memcpy(buffer, &NSGamepadReportData, NS_GAMEPAD_REPORT_SIZE);

  

}




