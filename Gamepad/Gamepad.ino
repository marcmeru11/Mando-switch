/*
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ESP32USB.h"

extern "C" {
  #include "NSProtocol.h"
  #include "NSGamepad.h"
}

ESP32USB esp32USB;

// Gamepad
tNSGamepad nsGamepad;
// Datos del gamepad serializados para su envio
uint8_t buffer [NS_GAMEPAD_REPORT_SIZE];

// TO DO: Esto desaparece cuando todos los botones esten implementados.
// Pulsar tres veces el mismo boton, con una pausa suficiente entre pulsaciones.
// (ensayo/error: 100 ms)
void handshake() {

  int i = 0;

  for (i = 0; i<3; i++) {
    NSGamepadPressButton (Y , &nsGamepad);
    // Serializamos
    NSProtocolSerializeNSGamepadData (nsGamepad, buffer);
    // Enviamos el contenido del buffer
    esp32USB.write (NS_GAMEPAD_REPORT_SIZE, buffer);
    delay(100);
    NSGamepadReleaseButton (Y , &nsGamepad);
    // Serializamos
    NSProtocolSerializeNSGamepadData (nsGamepad, buffer);
    // Enviamos el contenido del buffer
    esp32USB.write (NS_GAMEPAD_REPORT_SIZE, buffer);
    delay(100);
  }

  Serial.println("Saludo terminado");

}

void setup() {

  Serial.begin(9600);

  NSGamepadReleaseAllButtons(&nsGamepad);

  esp32USB.begin();

  // TO DO: Borrar esta linea y esa funcion cuando todos los botones esten implementados
  handshake();
}

void loop() {

  // Detectamos pulsacion de botones y la registramos en nsGamepad
  // TO DO: !Esto no esta hecho!
  
  // Ejemplo: si se ha pulsado el boton B, hariamos:
  NSGamepadPressButton (B , &nsGamepad);
  // Ejemplo 2: si se ha soltado el boton B, hariamos:
  // NSGamepadReleaseButton (B , &nsGamepad);
  // Nota: B, como todas las constantes y tipos, esta declarado en NSTypes.h

  // Serializamos los datos contenidos en nsGamepad para su envio
  // TO DO: Hay que completar el codigo de esta funcion
  NSProtocolSerializeNSGamepadData (nsGamepad, buffer);

  // Enviamos el contenido del buffer
  esp32USB.write (NS_GAMEPAD_REPORT_SIZE, buffer);

  delay(100);
}
