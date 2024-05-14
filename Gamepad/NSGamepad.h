#ifndef NSGAMEPAD_H_
#define NSGAMEPAD_H_

#include "NSTypes.h"

void NSGamepadPressButton (tNSButtons buttonIndex , tNSGamepad* NSGamepad);

void NSGamepadReleaseButton (tNSButtons buttonIndex , tNSGamepad* NSGamepad);

void NSGamepadReleaseAllButtons (tNSGamepad* NSGamepad);

void NSGamepadUpdateJoySticks(tNSJoySticks axis, int pos,tNSGamepad* NSGamepad);


// TO DO: Resto de botones y funcionalidades

#endif // NSGAMEPAD_H_