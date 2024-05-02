#ifndef NSPROTOCOL_H_
#define NSPROTOCOL_H_

#include "NSTypes.h"

// Funcion que devuelve un byte (8 bits) indicando el estado del D-PAD a partir
// del estado de pulsacion de cada uno de sus botones
void NSProtocolDPadButtonsToByte(int up, int down, int left, int right, uint8_t* byte);

// Funcion que devueve en dos bytes (16 bits) el estado de los primeros 14 botones
// del tipo tNSButtons
void NSProtocolButtonsToBytes (tNSGamepad nsGamepad,  uint16_t* twoBytes);

// Serializacion de la estructura que contiene las informacion de los botones pulsados
// (para su posterior envio a la NS por USB)
void NSProtocolSerializeNSGamepadData (tNSGamepad nsGamepad, uint8_t buffer [NS_GAMEPAD_REPORT_SIZE]);

#endif // NSPROTOCOL_H_