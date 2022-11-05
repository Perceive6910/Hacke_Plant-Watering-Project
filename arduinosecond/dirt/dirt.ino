const int pinTemp  = A0;
const int pinUp = A1;
const int pinDown = A2;
const int pinMiddle = A3;
bool up;
bool down;
bool middle;
int temp;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
up = ButtonPress(pinUp);
middle = ButtonPress(pinMiddle);
down = ButtonPress(pinDown);

  
Serial.println(up);
delay(50);



}

// converts pin to a bool
bool ButtonPress(int pin){
  int val = analogRead(pin);
  if (val == 1023){
    return true;
  }
  else{
    return false;
  }
}
// set pins in bool
