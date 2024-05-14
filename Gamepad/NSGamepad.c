#include "NSGamepad.h"



void NSGamepadPressButton (tNSButtons buttonIndex , tNSGamepad* NSGamepad) {

  NSGamepad->buttonsPressed[buttonIndex] = PRESSED;


}

void NSGamepadReleaseButton (tNSButtons buttonIndex , tNSGamepad* NSGamepad) {

  NSGamepad->buttonsPressed[buttonIndex] = NOT_PRESSED;

}

void NSGamepadReleaseAllButtons (tNSGamepad* NSGamepad) {

  int i = 0;

  for (i = 0; i < RESERVED_LAST_BUTTON_UNUSED; i++) {
     NSGamepad->buttonsPressed[i] = NOT_PRESSED;
  }

}

// TO DO: Resto de botones y funcionalidades

void NSGamepadUpdateJoySticks(tNSJoySticks axis, int pos,tNSGamepad* NSGamepad){
  if (pos > 1948 && pos < 2148){
    NSGamepad->joyStickPos[axis] = 128;
  } else {
    NSGamepad->joyStickPos[axis] = ((pos*255)/4095);
  }
}