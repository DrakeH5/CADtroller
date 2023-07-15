#include <ezButton.h>
#include <Mouse.h>
#include <Keyboard.h>

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define SW_PIN   2  // Arduino pin connected to SW  pin

ezButton button(SW_PIN);

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int bValue = 0; // To store value of the button

int sensitivityX = 400; //sensitivity for joystick controlling mouse
int sensitivityY = 500;

bool shiftClicked = false;
bool midMouseClicked = false;

void setup() {
  Serial.begin(9600) ;
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  button.loop(); // MUST call the loop() function first

  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
 
  // Read the button value
  bValue = button.getState();

  if (button.isPressed()) {
    Serial.println("The button is pressed");
    // TODO do something here
  }

  if (button.isReleased()) {
    Serial.println("The button is released");
    // TODO do something here
  }

  if(xValue != 530 || yValue != 518){
    if(shiftClicked == false  && bValue == 1){
      Keyboard.press(KEY_LEFT_SHIFT);
      shiftClicked = true;
    } else if(shiftClicked == true  && bValue == 0){
      Keyboard.releaseAll();
      shiftClicked = false;
    }
    if(midMouseClicked == false){
      Mouse.press(MOUSE_MIDDLE);
      midMouseClicked = true;
    }
  } else {
    Keyboard.releaseAll();
    Mouse.release(MOUSE_MIDDLE);
    shiftClicked = false;
    midMouseClicked = false;
  }

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.print(yValue);
  Serial.print(" : button = ");
  Serial.println(bValue);
  
  Mouse.move(-(yValue-518)/sensitivityY, (xValue-530)/sensitivityX, 0); //swapped x and y because of orientation of joystick
  
}
