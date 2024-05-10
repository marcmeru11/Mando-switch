#include <Arduino.h>

#if CONFIG_TINYUSB_HID_ENABLED

#include "NSTypes.h"
#include "ESP32USB.h"

// Aqui indicamos el report descriptor especifico para el anfitrion destino (en nuestro caso, la Nintendo Switch)
static uint8_t* reportDescriptor = NSReportDescriptor;
size_t reportDescriptorSize = sizeof(NSReportDescriptor);

// De aqui en adelante, en principio, no habria que tocar nada

ESP32USB::ESP32USB() : hid() {

  static bool initialized = false;
  startMillis = 0;

  USB.VID(0x0f0d);
  USB.PID(0x00c1);
  USB.usbClass(0);
  USB.usbSubClass(0);
  USB.usbProtocol(0);

  if (!initialized) {
    initialized = true;
    hid.addDevice(this, reportDescriptorSize);
  }

}

void ESP32USB::begin() {

  hid.begin();
  USB.begin();

}

// Uso interno (no tocar)
uint16_t ESP32USB::_onGetDescriptor(uint8_t* dst) {
  memcpy(dst, reportDescriptor, reportDescriptorSize);
  return reportDescriptorSize;
}

// Envio por USB del contenido del buffer
bool ESP32USB::write(size_t len, void* buffer) {

  if (startMillis != millis()) {
    return hid.SendReport(0, buffer, len);
    startMillis = millis();
  }

}

#endif // CONFIG_TINYUSB_HID_ENABLED