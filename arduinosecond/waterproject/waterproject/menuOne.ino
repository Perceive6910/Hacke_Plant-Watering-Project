void menuOne(bool button, int pumpPin, int time) {
  // put your setup code here, to run once:
  // 164 by 120 (x,y)
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(1,2);
      display.println("Would you like to");
      display.setCursor(1,20);
      display.println("Water the Plant?");


      /// get pump
      if(button){
      digitalWrite(pumpPin, HIGH);
      delay(time);
      digitalWrite(pumpPin, LOW);
}
