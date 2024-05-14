#ifndef NSTYPES_H_
#define NSTYPES_H_

#include "stdint.h"
#include "stddef.h"

// ** Tipos de datos impuestos por el protocolo de la Nintendo Switch (sacados de la documentacion) **
// Dpad directions
#define NSGAMEPAD_DPAD_UP  0
#define NSGAMEPAD_DPAD_UP_RIGHT 1
#define NSGAMEPAD_DPAD_RIGHT 2
#define NSGAMEPAD_DPAD_DOWN_RIGHT 3
#define NSGAMEPAD_DPAD_DOWN 4
#define NSGAMEPAD_DPAD_DOWN_LEFT 5
#define NSGAMEPAD_DPAD_LEFT 6
#define NSGAMEPAD_DPAD_UP_LEFT 7
#define NSGAMEPAD_DPAD_CENTERED 0xF

// ** Tipos de datos impuestos por el protocolo de comunicacion USB OTG de la Nintendo Switch **

// Tamanio del mensaje del protocolo para gamepads de la Nintendo Switch (en bytes)
#define NS_GAMEPAD_REPORT_SIZE 8

// Report descriptor.
// Datos binarios que especifican tipo de dispositivo y detalles de los informes (reports) 
// que se enviaran por USB.
// Es imprescindible especificar este dato para que el dispositivo 
// se indetifique y funcione correctamente (quien utilice esta clase deberá hacerlo).
// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
static uint8_t NSReportDescriptor[] = {
  // Gamepad for Nintendo Switch
  // 14 buttons, 1 8-way dpad, 2 analog sticks (4 axes)
  0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
  0x09, 0x05,        // Usage (Game Pad)
  0xA1, 0x01,        // Collection (Application)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x01,        //   Logical Maximum (1)
  0x35, 0x00,        //   Physical Minimum (0)
  0x45, 0x01,        //   Physical Maximum (1)
  0x75, 0x01,        //   Report Size (1)
  0x95, 0x0E,        //   Report Count (14)
  0x05, 0x09,        //   Usage Page (Button)
  0x19, 0x01,        //   Usage Minimum (0x01)
  0x29, 0x0E,        //   Usage Maximum (0x0E)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,
                     //   Preferred State,No Null Position)
  0x95, 0x02,        //   Report Count (2)
  0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,
                     //   Preferred State,No Null Position)
  0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
  0x25, 0x07,        //   Logical Maximum (7)
  0x46, 0x3B, 0x01,  //   Physical Maximum (315)
  0x75, 0x04,        //   Report Size (4)
  0x95, 0x01,        //   Report Count (1)
  0x65, 0x14,        //   Unit (System: English Rotation, Length: Centimeter)
  0x09, 0x39,        //   Usage (Hat switch)
  0x81, 0x42,        //   Input (Data,Var,Abs,No Wrap,Linear,
                     //   Preferred State,Null State)
  0x65, 0x00,        //   Unit (None)
  0x95, 0x01,        //   Report Count (1)
  0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,
                     //   Preferred State,No Null Position)
  0x26, 0xFF, 0x00,  //   Logical Maximum (255)
  0x46, 0xFF, 0x00,  //   Physical Maximum (255)
  0x09, 0x30,        //   Usage (X)
  0x09, 0x31,        //   Usage (Y)
  0x09, 0x32,        //   Usage (Z)
  0x09, 0x35,        //   Usage (Rz)
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x04,        //   Report Count (4)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,
                     //   Preferred State,No Null Position)
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x01,        //   Report Count (1)
  0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,
                     //   Preferred State,No Null Position)
  0xC0,              // End Collection
};

// Estructura del mensaje (contenido del buffer) tal cual debe enviarse a la Nintendo Switch,
// siguiendo su protocolo
// 14 Buttons, 4 Axes, 1 D-Pad
typedef struct {
  uint8_t actionButtons;
  uint8_t menuButtons;
  uint8_t dPad;
  uint8_t leftXAxis;
  uint8_t leftYAxis;
  uint8_t rightXAxis;
  uint8_t rightYAxis;
  uint8_t filler;
} tNSGamepadReportData;

// ** Tipos de datos definidos por nosotros (como queramos) **

typedef enum {NOT_PRESSED = 0, PRESSED} tNSButtonState;

typedef enum {
  Y = 0,
  B,
  A,
  X,
  L,
  R,
  ZL,
  ZR,
  MINUS,
  PLUS,
  LEFT_STICK,
  RIGHT_STICK,
  HOME,
  CAPTURE,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  RESERVED_LAST_BUTTON_UNUSED
} tNSButtons;

typedef enum {
  RIGHTY=0, 
  RIGHTX,
  LEFTY,
  LEFTX,
  AUX

} tNSJoySticks;

// TO DO: Completar
typedef struct {

  tNSButtonState buttonsPressed[RESERVED_LAST_BUTTON_UNUSED];

  // Definir el resto de campos utiles
  int joyStickPos[AUX];



} tNSGamepad;


#endif