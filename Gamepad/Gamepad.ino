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

extern "C"
{
#include "NSProtocol.h"
#include "NSGamepad.h"
}

ESP32USB esp32USB;

// Gamepad
tNSGamepad nsGamepad;

//Constantes mandop
const int MAX_JOYSTICK_VALUE = 4095;
const int JOYSTICK_TRANSFER_BITS = 255;
const int JOYSTICK_MEDIUM_VALUE = 128;
const int ASSISTANCE_VALUE = 10;

// Datos del gamepad serializados para su envio
uint8_t buffer[NS_GAMEPAD_REPORT_SIZE];

// TO DO: Esto desaparece cuando todos los botones esten implementados.
// Pulsar tres veces el mismo boton, con una pausa suficiente entre pulsaciones.
// (ensayo/error: 100 ms)

// DECLARACION DE LOS PINES
const int B_BUTTON = 15;
const int A_BUTTON = 18;
const int X_BUTTON = 8;
const int Y_BUTTON = 16;

// CRUCETA
const int UP_DIRECTION_BUTTON = 36;
const int RIGHT_DIRECTION_BUTTON = 37;
const int LEFT_DIRECTION_BUTTON = 39;
const int DOWN_DIRECTION_BUTTON = 40;

// EXTRAS
const int MINUS_BUTTON = 0;
const int BACK_BUTTON = 35;
const int PLUS_BUTTON = 46;
const int HOME_BUTTON = 3;

// GATILLOS
const int BACK_LEFT_TRIGGER_BUTTON = 48;
const int LEFT_TRIGGER_BUTTON = 45;
const int BACK_RIGHT_TRIGGER_BUTTON = 9;
const int RIGHT_TRIGGER_BUTTON = 10;

// JOYSTICKS
const int RIGHT_JOYSTICK_Y_AXIS = 5;
const int RIGHT_JOYSTICK_X_AXIS = 4;
const int RIGHT_JOYSTICK_BUTTON = 6;

const int LEFT_JOYSTICK_Y_AXIS = 2;
const int LEFT_JOYSTICK_X_AXIS = 1;
const int LEFT_JOYSTICK_BUTTON = 42;

// estados;
int b_button_pressed, a_button_pressed, y_button_pressed, x_button_pressed;

// EXTRAS
int minus_button_pressed, back_button_pressed, plus_button_pressed, home_button_pressed;

// cruceta
int up_dir_button_pressed, left_dir_button_pressed, right_dir_button_pressed, down_dir_button_pressed;

// gatillos
int back_left_trigger_button_pressed, left_trigger_button_pressed, back_right_trigger_button_pressed, right_trigger_button_pressed;

// joysticks
int left_joystick_button_pressed, right_joystick_button_pressed;
int left_x, left_y, right_x, right_y;


void pressButtons(){
  if(b_button_pressed == LOW){
    //Serial.println("B");
    NSGamepadPressButton(B, &nsGamepad);
  }
  if(a_button_pressed == LOW){
    //Serial.println("A");
    NSGamepadPressButton(A, &nsGamepad);
  }
  if(y_button_pressed == LOW){
    //Serial.println("Y");
    NSGamepadPressButton(Y, &nsGamepad);
  }
  if(x_button_pressed == LOW){
    //Serial.println("X");
    NSGamepadPressButton(X, &nsGamepad);
  }

  // EXTRAS
  if(minus_button_pressed == LOW){
    //Serial.println("MINUS");
    NSGamepadPressButton(MINUS, &nsGamepad);
  }
  if(back_button_pressed == LOW){
    //Serial.println("BACK");
    NSGamepadPressButton(CAPTURE, &nsGamepad);
  }
  if(plus_button_pressed == LOW){
    //Serial.println("PLUS");
    NSGamepadPressButton(PLUS, &nsGamepad);
  }
  if(home_button_pressed == LOW){
    //Serial.println("HOME");
    NSGamepadPressButton(HOME, &nsGamepad);
  }

  // cruceta
  if(up_dir_button_pressed == LOW){
    //Serial.println("UP");
    NSGamepadPressButton(UP, &nsGamepad);
  }
  if(left_dir_button_pressed == LOW){
    //Serial.println("LEFT");
    NSGamepadPressButton(LEFT, &nsGamepad);
  }
  if(right_dir_button_pressed == LOW){
    //Serial.println("RIGHT");
    NSGamepadPressButton(RIGHT, &nsGamepad);
  }
  if(down_dir_button_pressed == LOW){
    //Serial.println("DOWN");
    NSGamepadPressButton(DOWN, &nsGamepad);
  }

  // gatillos
  if(back_left_trigger_button_pressed == LOW){
    //Serial.println("BACK_LEFT_TRIGGER");
    NSGamepadPressButton(ZL, &nsGamepad);
  }
  if(left_trigger_button_pressed == LOW){
    //Serial.println("LEFT_TRIGGER");
    NSGamepadPressButton(L, &nsGamepad);
  }
  if(back_right_trigger_button_pressed == LOW){
    //Serial.println("BACK_RIGHT_TRIGGER");
    NSGamepadPressButton(ZR, &nsGamepad);
  }
  if(right_trigger_button_pressed == LOW){
    //Serial.println("RIGHT_TRIGGER");
    NSGamepadPressButton(R, &nsGamepad);
  }

  // joysticks
  if(left_joystick_button_pressed == LOW){
    //Serial.println("LEFT_JOYSTICK");
    NSGamepadPressButton(LEFT_STICK, &nsGamepad);
  }
  if(right_joystick_button_pressed == LOW){
    //Serial.println("RIGHT_JOYSTICK");
    NSGamepadPressButton(RIGHT_STICK, &nsGamepad);
  }


}

void releaseButtons(){
  if(b_button_pressed == HIGH){
    NSGamepadReleaseButton(B, &nsGamepad);
  }
  if(a_button_pressed == HIGH){
    NSGamepadReleaseButton(A, &nsGamepad);
  }
  if(y_button_pressed == HIGH){
    NSGamepadReleaseButton(Y, &nsGamepad);
  }
  if(x_button_pressed == HIGH){
    NSGamepadReleaseButton(X, &nsGamepad);
  }

  // EXTRAS
  if(minus_button_pressed == HIGH){
    NSGamepadReleaseButton(MINUS, &nsGamepad);
  }
  if(back_button_pressed == HIGH){
    NSGamepadReleaseButton(CAPTURE, &nsGamepad);
  }
  if(plus_button_pressed == HIGH){
    NSGamepadReleaseButton(PLUS, &nsGamepad);
  }
  if(home_button_pressed == HIGH){
    NSGamepadReleaseButton(HOME, &nsGamepad);
  }

  // cruceta
  if(up_dir_button_pressed == HIGH){
    NSGamepadReleaseButton(UP, &nsGamepad);
  }
  if(left_dir_button_pressed == HIGH){
    NSGamepadReleaseButton(LEFT, &nsGamepad);
  }
  if(right_dir_button_pressed == HIGH){
    NSGamepadReleaseButton(RIGHT, &nsGamepad);
  }
  if(down_dir_button_pressed == HIGH){
    NSGamepadReleaseButton(DOWN, &nsGamepad);
  }

  // gatillos
  if(back_left_trigger_button_pressed == HIGH){
    NSGamepadReleaseButton(ZL, &nsGamepad);
  }

  if(left_trigger_button_pressed == HIGH){
    NSGamepadReleaseButton(L, &nsGamepad);
  }
  if(back_right_trigger_button_pressed == HIGH){
    NSGamepadReleaseButton(ZR, &nsGamepad);
  }
  if(right_trigger_button_pressed == HIGH){
    NSGamepadReleaseButton(R, &nsGamepad);
  }

  // joysticks
  if(left_joystick_button_pressed == HIGH){
    NSGamepadReleaseButton(LEFT_STICK, &nsGamepad);
  }
  if(right_joystick_button_pressed == HIGH){
    NSGamepadReleaseButton(RIGHT_STICK, &nsGamepad);
  }

  
}

void declarePinModes(){
  pinMode(B_BUTTON, INPUT_PULLUP);
  pinMode(A_BUTTON, INPUT_PULLUP);
  pinMode(Y_BUTTON, INPUT_PULLUP);
  pinMode(X_BUTTON, INPUT_PULLUP);

  // EXTRAS
  pinMode(MINUS_BUTTON, INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);
  pinMode(PLUS_BUTTON, INPUT_PULLUP);
  pinMode(HOME_BUTTON, INPUT_PULLUP);

  // cruceta
  pinMode(UP_DIRECTION_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_DIRECTION_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_DIRECTION_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_DIRECTION_BUTTON, INPUT_PULLUP);

  // gatillos
  pinMode(BACK_LEFT_TRIGGER_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_TRIGGER_BUTTON, INPUT_PULLUP);
  pinMode(BACK_RIGHT_TRIGGER_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_TRIGGER_BUTTON, INPUT_PULLUP);

  // joysticks
  pinMode(RIGHT_JOYSTICK_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_JOYSTICK_BUTTON, INPUT_PULLUP);
}

void handshake()
{

  int i = 0;

  for (i = 0; i < 3; i++)
  {
    NSGamepadPressButton(Y, &nsGamepad);
    // Serializamos
    NSProtocolSerializeNSGamepadData(nsGamepad, buffer);
    // Enviamos el contenido del buffer
    esp32USB.write(NS_GAMEPAD_REPORT_SIZE, buffer);
    delay(50);
    NSGamepadReleaseButton(Y, &nsGamepad);
    // Serializamos
    NSProtocolSerializeNSGamepadData(nsGamepad, buffer);
    // Enviamos el contenido del buffer
    esp32USB.write(NS_GAMEPAD_REPORT_SIZE, buffer);
    delay(50);
  }
}

void setup()
{

  Serial.begin(9600);
  
  NSGamepadReleaseAllButtons(&nsGamepad);
  declarePinModes();
  esp32USB.begin();

  handshake();
}

void loop()
{
  // TO DO: !Esto no esta hecho!
  // Ejemplo: si se ha pulsado el boton B, hariamos:
  
  // Ejemplo 2: si se ha soltado el boton B, hariamos:
  // NSGamepadReleaseButton (B , &nsGamepad);
  pressedButtonsDetection();

  int* leftJoyStick = (int*)malloc(2*sizeof(int));
  leftJoyStick[0] = MAX_JOYSTICK_VALUE - analogRead(LEFT_JOYSTICK_X_AXIS);
  leftJoyStick[1] = analogRead(LEFT_JOYSTICK_Y_AXIS);
  set256bits(leftJoyStick);
  leftJoyStick = joyStickAssistance(leftJoyStick);

  int* rightJoyStick = (int*)malloc(2*sizeof(int));
  rightJoyStick[0] = MAX_JOYSTICK_VALUE - analogRead(RIGHT_JOYSTICK_X_AXIS);
  rightJoyStick[1] = analogRead(RIGHT_JOYSTICK_Y_AXIS);
  set256bits(rightJoyStick);
  rightJoyStick = joyStickAssistance(rightJoyStick);

  NSGamepadUpdateJoySticks(LEFTX, leftJoyStick[0], &nsGamepad );
  NSGamepadUpdateJoySticks(LEFTY, leftJoyStick[1], &nsGamepad );
  NSGamepadUpdateJoySticks(RIGHTX, rightJoyStick[0], &nsGamepad );
  NSGamepadUpdateJoySticks(RIGHTY, rightJoyStick[1], &nsGamepad );
  Serial.printf("\n%d, %d // %d, %d", leftJoyStick[0], leftJoyStick[1], rightJoyStick[0], rightJoyStick[1]);

  // Serializamos los datos contenidos en nsGamepad para su envio
  NSProtocolSerializeNSGamepadData(nsGamepad, buffer);

  // Enviamos el contenido del buffer
  esp32USB.write(NS_GAMEPAD_REPORT_SIZE, buffer);
  
  free(leftJoyStick);
  free(rightJoyStick);

  delay(20);
}

void pressedButtonsDetection(){
  //ABXY
  b_button_pressed = digitalRead(B_BUTTON);
  a_button_pressed = digitalRead(A_BUTTON);
  y_button_pressed = digitalRead(Y_BUTTON);
  x_button_pressed = digitalRead(X_BUTTON);

  // EXTRAS
  minus_button_pressed = digitalRead(MINUS_BUTTON);
  back_button_pressed = digitalRead(BACK_BUTTON);
  plus_button_pressed = digitalRead(PLUS_BUTTON);
  home_button_pressed = digitalRead(HOME_BUTTON);

  // cruceta
  up_dir_button_pressed = digitalRead(UP_DIRECTION_BUTTON);
  left_dir_button_pressed = digitalRead(LEFT_DIRECTION_BUTTON);
  right_dir_button_pressed = digitalRead(RIGHT_DIRECTION_BUTTON);
  down_dir_button_pressed = digitalRead(DOWN_DIRECTION_BUTTON);
  
  // gatillos
  back_left_trigger_button_pressed = digitalRead(BACK_LEFT_TRIGGER_BUTTON);
  left_trigger_button_pressed = digitalRead(LEFT_TRIGGER_BUTTON);
  back_right_trigger_button_pressed = digitalRead(BACK_RIGHT_TRIGGER_BUTTON);
  right_trigger_button_pressed = digitalRead(RIGHT_TRIGGER_BUTTON);

  // joysticks
  left_joystick_button_pressed = digitalRead(LEFT_JOYSTICK_BUTTON);
  right_joystick_button_pressed = digitalRead(RIGHT_JOYSTICK_BUTTON);

  pressButtons();
  releaseButtons();
}

void set256bits(int* result){
  result[0] = map(result[0], 0, MAX_JOYSTICK_VALUE, 0, JOYSTICK_TRANSFER_BITS);
  result[1] = map(result[1], 0, MAX_JOYSTICK_VALUE, 0, JOYSTICK_TRANSFER_BITS);
}

int* joyStickAssistance(int* result) {
  int x_centered = 0;
  int y_centered = 0;

  if (result[0] >= (JOYSTICK_MEDIUM_VALUE - ASSISTANCE_VALUE) && result[0] <= (JOYSTICK_MEDIUM_VALUE + ASSISTANCE_VALUE)){
    result[0] = JOYSTICK_MEDIUM_VALUE;
  }
  if (result[1] >= (JOYSTICK_MEDIUM_VALUE - ASSISTANCE_VALUE) && result[1] <= (JOYSTICK_MEDIUM_VALUE + ASSISTANCE_VALUE) ){
    result[1] = JOYSTICK_MEDIUM_VALUE;
  }
  return result;
}
