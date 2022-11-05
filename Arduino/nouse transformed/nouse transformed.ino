#include <Mouse.h>



const int xanalogPin = A3;  // potentiometer wiper (middle terminal) connected to analog pin 3
const int yanalogPin = A2;  // potentiometer wiper (middle terminal) connected to analog pin 3
const int buttonPush = A0;  // for buttone pres
const int analogMin = 520;// both used for determining "dead zone"
const int analogMax = 520;
const float speed = 4; // controll speed of mouse
const int stop = 2;         // stop program if on
const int mouseSpeed = 2; // delay in miliseconds 
// outside leads to ground and +5V
int inpin =0; /// stores value if stoppin
int xval = 0;     // variable to store the value read
int yval = 0;     //store y vall
int push = 0;     // stores pushbutton value
int pressed = 0;  //prevent over doing it
int mouseX = 0; /// track mouse movement
int mouseY = 0;// track mouse movement

void setup() {
  Serial.begin(9600);  //  setup serial
  Mouse.begin();
  pinMode(stop, INPUT);  // uses pin 2 to canel
}


void loop() {


  inpin = digitalRead(stop);

  if (inpin != 1) {

    xval = analogRead(xanalogPin);  // read the input pin
    yval = analogRead(yanalogPin);  // read the input pin
    push = analogRead(buttonPush);  // store button press


// get mouse click information
  /*  if (push == 0) {
      Mouse.click();
      delay(1000);
    }
*/     
  Mouse.move(Direction(yval), Direction(xval)*-1);            
  

    
    //Serial.println(push);
   // Serial.println( xval);
    Serial.println(yval);
  }
if(yval >= 20){
 if (push == 0) {
      Mouse.click();
      delay(200);
    }  
}  
delay(mouseSpeed);
}
char Direction(int val){
  char move = 0;
  
  if (val < analogMin){
    move = ((100.00*(analogMin - val))/(analogMin*100.00))*speed; 
                 
    move = move*(-1);
  }
    if (val > analogMax){
                    
    move = ((100.00*(val - analogMax))/(analogMax*100.00))*speed; 
    
  }
  return move;
}
