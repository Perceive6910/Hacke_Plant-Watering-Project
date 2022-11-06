int pinMoisture  = A0;
int pinUp = A1;
int pinDown = A2;
int pinMiddle = A3;
bool up;
bool down;
bool middle;
int moisture;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
up = ButtonPress(pinUp);
middle = ButtonPress(pinMiddle);
down = ButtonPress(pinDown);
moisture = analogRead(pinMoisture);
moisture = (100-((pinMoisture / 1023)*100));
Serial.println(moisture);
Serial.println(up);
delay(50);

void loop() {
  // put your main code here, to run repeatedly:
moisture = analogRead(pinMoisture);
//moisture = 100-((pinMoisture / 1023)*100);
Serial.println(moisture);
delay(50);
}


  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0,0);
  display.println("Plant Status");
  display.setTextSize(1);             
  display.setTextColor(1);
  display.setCursor(0,10);
  display.println("Moisture Percentage");
  display.setTextSize(1);             
  display.setTextColor(1);
  display.setCursor(0,20);
  display.println("Clock Cycle");
  display.display();
  delay(1000);


}

// converts pin to a bool
bool ButtonPress(int pin){
  int val = analogRead(pin);
  if (val == 100){
    return true;
  }
  else{
    return false;
  }
}
// set pins in bool
