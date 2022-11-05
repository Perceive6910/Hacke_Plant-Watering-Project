#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void Welcome();
//Code for joy axis
const int xanalogPin = A3;  // potentiometer wiper (middle terminal) connected to analog pin 3
const int yanalogPin = A2;  // potentiometer wiper (middle terminal) connected to analog pin 3
const int buttonPush = A0;  // for buttone pres
const int analogMin = 490;// both used for determining "dead zone"
const int analogMax = 525;
const int buzzer = 9; //buzzer to arduino pin 9

// constants for graphics
const uint16_t paddleSize = 10;// size of paddle
uint16_t border = 1;// color seting
const int moveConstant = 6;// movement speed of paddle
const int ballSize = 4;// size of ball
const int paddleStart = display.height()/2;/// stores location of paddle

int xval = 0;     // variable to store the value read
int yval = 0;     //store y vall
int push = 0;     // stores pushbutton value
int pressed = 0;  //prevent over doing it
int sleep;// delay/sleep
int paddle;
int xStart;// x start location of circle
int yStart;// y start location of circle
int xVelocity;//
int yVelocity;//

int ballFloor = display.height() - 3;//floor for ball
int ballCeiling = 1;// roof for ball
int ballWall = display.width()-7;// wall location to bounce off
int ballSpeed = 1;/// holds ballspeed for movement per frame
bool loss;
int score;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  Welcome();
  delay(2000);
    
    /*  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);
*/
  
}




void loop() {

//set up program variables
loss = false;
score = 0;
sleep = 20;//reset sleep
paddle = paddleStart;
xStart = 3;// x start location of circle
yStart = random(2,63);// y start location of circle
xVelocity = ballSpeed;//
yVelocity = ballSpeed *UpDown();//
  

  
do{
  

  display.clearDisplay();

// get analoge input   
xval = analogRead(xanalogPin);  // read the input pin
yval = analogRead(yanalogPin);  // read the input pin
push = analogRead(buttonPush);  // store button press


    // draw border
DrawBorder();

xStart += (xStart <5 ? (xStart < 3? xVelocity:  xVelocity*2) : xVelocity*DiffMod());
yStart += (xStart <25 ? (xStart < 3? xVelocity:  yVelocity*2) : yVelocity*DiffMod());
//draw paddle
paddle += Direction(xval);
paddle = DrawPaddle(paddle); 

//flip paddle
if (xStart >= ballWall){
    xVelocity *= -1;
    xStart = ballWall;
    
    if(score >= 5){
    yStart = random(3,62);      
    }    
    }
if (yStart >= ballFloor || yStart <= ballCeiling){
    yVelocity *= -1;
  yStart = (yStart >= ballFloor ? ballFloor-1 : ballCeiling+1);       
    }
if (xStart <= 1){
  if(yStart == 0 || yStart == 1 || yStart == 2 || yStart ==3|| yStart == 4 || yStart == 5 ){
     
     BallHit();                 
  }
///// game over area !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  else if (yStart >= paddle + paddleSize/2+3 || yStart <= (paddle - (paddleSize/2))-5)
      {
      loss = true;
      sleep--;
      }
    else{//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         BallHit();// used to define hiiting the ball  
    }
        }


DrawBall(xStart,yStart);
DrawScore();



//print serial for testing
/*
Serial.println(Direction(xval));  
Serial.println(paddle);
Serial.println(xval);
*/
// update display and loop

display.display() ;
 delay(sleep);

}while(!loss);



display.clearDisplay();
display.setCursor(24, 2); 
display.println("high score : ");
display.setCursor(96, 2);
display.println(score);
display.setCursor(20, display.height()/2); 
display.println("Press joystick");
display.setCursor(display.width()/2-40, display.height()/2+10); 
display.println("to Continue");
display.display();

LossTone();
while(true){
  if (click()){
    break;
  }  
}
}



/// get mouse direction
int Direction(int val){
  int move = moveConstant;
  
  if (val < analogMin){                 
    move *= -1;
    }
  else if (val > analogMax){
                    
    move *= 1; 
    }
  else{
  move *= 0;    
  }
  return move;
  
}

// detect click
bool click(){
push = analogRead(buttonPush);  // store button press
Serial.println(push);
if(yval >= 20){
 if (push == 0) {
      return true;
      delay(200);
    }  
}
return false;     
}


// displays welcome
void Welcome() {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(display.width()/2-12, 2);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.write("Pong");
  
display.setCursor(display.width()/2-25, display.height()/2-4);  
display.println("training");
  
  display.setCursor(15, display.height()-10);
  display.println("Brandon Carpenter");
  display.display();
  delay(40);
tone(buzzer, 330); // Send 1KHz sound signal...
          delay(500);        // ...for 1 sec
          noTone(buzzer);     // Stop sound...
          tone(buzzer, 500); // Send 1KHz sound signal...
          delay(500);        // ...for 1 sec
          noTone(buzzer);     // Stop sound...
          tone(buzzer,660);
          delay(500);        // ...for 1 sec
          noTone(buzzer);     // Stop sound...     
}

// this draws the border
void DrawBorder(){
for (int i = 0; i < display.width() ; i++) /// make top line
            {
                display.drawPixel(i, 0, border);
            }
            for (int i = 0; i < display.width() ; i++)// make bottom line
            {
                display.drawPixel(i, display.height() - 1, border);
            }
            for (int i = 0; i < display.height(); i++)// make back wall
            {
                display.drawPixel(display.width() - 1, i, border);
            }  

}
// draw ball 
int DrawBall(int x,int  y){
  display.fillRect(x, y, ballSize, ballSize, border);
}

// this code draws paddle
uint16_t DrawPaddle(int y){
uint16_t h = display.height();
y = (y <= 1+paddleSize/2 ? 1+paddleSize/2 : y);
y = (y >= (h-(paddleSize/2)) ? h-(1+(paddleSize/2)) :y );
  for (int i = 0; i < paddleSize ; i++){
  display.drawPixel(0, y-(paddleSize/2)+i, border);
  }

return y;
}

int DrawScore(){
display.setCursor(display.width()/2, display.height()/2-4);  
display.println(score); 
}

int UpDown(){
  int rand = random(2);
  if(rand == 1){
return 1;    
  }
else{
  return -1;
}  
}
void LossTone(){
  tone(buzzer, 450); // Send 1KHz sound signal...
        delay(400);        // ...for 1 sec
        noTone(buzzer);     // Stop sound...
        tone(buzzer, 225); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        noTone(buzzer);     // Stop sound...
}
void BallHit(){
      // filp velocity, incease speed and score
        xVelocity *= -1;
        score++;
        sleep = (sleep <= 5 ? 5 :sleep-1);
        xStart = 3;          
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(10);        // ...for 1 sec
        noTone(buzzer);     // Stop sound...
        if (score == 5){
          tone(buzzer, 330); // Send 1KHz sound signal...
          delay(20);        // ...for 1 sec
          noTone(buzzer);     // Stop sound...
          tone(buzzer, 500); // Send 1KHz sound signal...
          delay(20);        // ...for 1 sec
          noTone(buzzer);     // Stop sound...
          tone(buzzer,660);
          delay(20);        // ...for 1 sec
          noTone(buzzer);     // Stop sound...  
        }          

}

int DiffMod(){
  if(score >= 3){
 return random(2,5);    
  }
  else return 2;
}