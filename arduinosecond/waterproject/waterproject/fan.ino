void menuOne(bool button, int pumpPin) {
  // put your setup code here, to run once:
  // 164 by 120 (x,y)
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(1,2);
      display.println("Would you like to");
      display.setCursor(1,20);
      display.println("Water the Plant?");
}

void FanToggle(bool buttonClick, int fanPin){
int time = 10000
      if(button){
      digitalWrite(fanPin, HIGH);
      delay(time);
      digitalWrite(fanPin, LOW);
      }

}