#ifndef ESP32USB_H_
#define ESP32USB_H_

#include "USB.h"
#include "USBHID.h"

#if CONFIG_TINYUSB_HID_ENABLED

class ESP32USB: public USBHIDDevice {
  public:
    ESP32USB(void);
    void begin();
    // Escribe (y envia) el contenido del buffer por USB
    bool write(size_t len, void* buffer);

    // uso interno
    uint16_t _onGetDescriptor(uint8_t* buffer);

  protected:
  
    USBHID hid;
    bool initialized;
    uint32_t startMillis;

};

#endif  // CONFIG_TINYUSB_HID_ENABLED
#endif  // ESP32USB_H_