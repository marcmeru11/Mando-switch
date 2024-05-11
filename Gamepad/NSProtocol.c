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
void NSProtocolDPadButtonsToByte(int up, int down, int left, int right, uint8_t *byte)
{

  // Hay que dar a la variable byte el valor correcto en funcion de que botones estan pulsados.
  // Por ej, si solo esta pulsado el boton de arriba, hariamos:
  //
  // *byte = NSGAMEPAD_DPAD_UP;
  //
  // Las constantes cuyo valor puede tomar byte estan definidas en NSTypes.h

  // TO DO
  if (up && !down)
  {

    if (left)
    {
      *byte = NSGAMEPAD_DPAD_UP_LEFT;
    }
    else if (right)
    {
      *byte = NSGAMEPAD_DPAD_UP_RIGHT;
    }
    else
    {
      *byte = NSGAMEPAD_DPAD_UP;
    }
  }
  else if (down && !up)
  {

    if (left)
    {
      *byte = NSGAMEPAD_DPAD_DOWN_LEFT;
    }
    else if (right)
    {
      *byte = NSGAMEPAD_DPAD_DOWN_RIGHT;
    }
    else
    {
      *byte = NSGAMEPAD_DPAD_DOWN;
    }
  }
  else if (right && !left)
  {
    *byte = NSGAMEPAD_DPAD_RIGHT;
  }
  else if (left && !right)
  {
    *byte = NSGAMEPAD_DPAD_LEFT;
  }
  else
  {
    *byte = NSGAMEPAD_DPAD_CENTERED;
  }
}

// Funcion que rellena los campos actionButtons y menuButtos de nsGamepad.
// El primer byte representa el estado de los primeros 8 botones (los de accion)
// del tipo tNSButtons.
// Estos botones ya se definieron en este mismo orden en el tipo enumerado tNSButtons de NSTypes.h:
//  Y B A X L R ZL ZR
// Cada bit representa si el boton correspondiente esta pulsado (1) o no lo esta (0).
// El peso del bit coincide con la posicion del boton en el enumerado (el boton Y va en el 0, el B en el 1...).
// Ejemplo: Si solo esta pulsado el boton B, es decir, el de indice 1, y el resto no lo estan,
// la secuenca seria: 00000010
// El segundo byte, menuButtons, corresponde al estado de los botones:
// MINUS PLUS LEFT_STICK RIGHT_STICK HOME CAPTURE
// (seis botones, los dos bits restantes los dejamos a 0)
void NSProtocolReportDataSetButtons(tNSGamepad nsGamepad, tNSGamepadReportData *NSGamepadReportData)
{

  // Primero los botones de accion, en el mismo orden que el enumerado:
  // Y B A X L R ZL ZR

  // Inicializamos a 0
  NSGamepadReportData->actionButtons = 0x00;
  int i;
  // Comenzamos por el primero de ellos, el Y (ver tNSButtons de NSTypes.h)
  for(i=0; i<ZR; i++){

    NSGamepadReportData->actionButtons = NSGamepadReportData->actionButtons | (uint8_t)nsGamepad.buttonsPressed[i]<<i;
  }


  // TO DO: Hacer el resto!
  // (Requiere uso de mascaras / desplazamientos logicos)
  // ¿Se puede generalizar usando un bucle?

  // Despues, van los botones de menu, en el mismo orden que el enumerado:
  //  MINUS PLUS LEFT_STICK RIGHT_STICK HOME CAPTURE
  // (Los bits de mas peso los dejariamos a cero, parece que depeden del fabricante, para botones extra)
  // Inicializamos a 0

  NSGamepadReportData->menuButtons = 0x00;
  for(i=MINUS; i<ZR; i++){

    NSGamepadReportData->actionButtons = NSGamepadReportData->actionButtons | (uint8_t)nsGamepad.buttonsPressed[i]<<i;
  }

  // TO DO: Hacerlos todos, igual que hicimos los de accion


  //! ASUMO QUE HAY QUE PASAR TAMBIEN LOS DPADS Y POSTERIORMENTE LOS  JOYSTICKS


  NSGamepadReportData->dPad= 0x00;
  
  //LE PASA EL ESTADO DE LOS BOTONES DEL DPAD, Y LUEGO LE PASA UN PUNTERO A DONDE TIENE QUE ESCRIBIR
  //NSProtocolDPadButtonsToByte(nsGamepad.buttonsPressed[UP] ,nsGamepad.buttonsPressed[DOWN] , nsGamepad.buttonsPressed[LEFT], nsGamepad.buttonsPressed[RIGHT], *byte);

  




}

// Valores por defecto del report que se envia a la Switch (sacado de documentacion "oficial")
void NSProtocolReportDataSetDefaultValues(tNSGamepadReportData *NSGamepadReportData)
{

  NSGamepadReportData->actionButtons = 0x00;
  NSGamepadReportData->menuButtons = 0x00;
  NSGamepadReportData->dPad = NSGAMEPAD_DPAD_CENTERED;
  NSGamepadReportData->leftXAxis = 0x80;
  NSGamepadReportData->leftYAxis = 0x80;
  NSGamepadReportData->rightXAxis = 0x80;
  NSGamepadReportData->rightYAxis = 0x80;
  NSGamepadReportData->filler = 0x00;
}


void NSProtocolSerializeNSGamepadData(tNSGamepad nsGamepad, uint8_t buffer[NS_GAMEPAD_REPORT_SIZE])
{

  tNSGamepadReportData NSGamepadReportData;

  // Cargamos los valores por defecto del report
  // (este paso nos lo podemos saltar cuando tengamos hecho el siguiente!)
  NSProtocolReportDataSetDefaultValues(&NSGamepadReportData);

  // Rellenamos NSGamepadReportData (tNSGamepadReportData) partiendo de
  // los campos de nsGamepad (tipo tNSGamepad).
  // Botones de accion y de menu:
  NSProtocolReportDataSetButtons(nsGamepad, &NSGamepadReportData);
  // TO DO: Hacer el resto de campos de NSGamepadReportData!

  // Finalmente, serializamos tHID_NSGamepadReportData (metemos los datos en el buffer).
  // TO DO: NO usar memcpy para la estructura completa (puede fallar si la estructura contiene "padding"),
  // hacerlo a mano: un memcpy para cada campo de la estructura, uno a uno, en el mismo orden en que
  // estan definidos en ella (que es el orden que establece el protocolo de la Nintendo Switch).
  memcpy(buffer, &NSGamepadReportData, NS_GAMEPAD_REPORT_SIZE);
}
