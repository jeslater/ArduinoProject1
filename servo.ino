//www.elegoo.com
//2016.12.09
#include <Servo.h>
#include "pitches.h"
#include "LedControl.h"

Servo myservo;
LedControl lc=LedControl(12,10,11,1);


// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
const int TurnX_pin = 9;
#define BLUE 3
#define GREEN 5
#define RED 6

unsigned long delaytime1=2;
unsigned long delaytime2=2;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

   //we have to do a wakeup call
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,6);
  /* and clear the display */
  lc.clearDisplay(0);
  
  myservo.attach(9);
  myservo.write(90);// move servos to center position -> 90°
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  
  Serial.begin(9600);
}

int redValue;
int greenValue;
int blueValue;
int poggers = 0;


void loop() {
  //debugging tools
  //Serial.print("Switch:  ");
  //Serial.print(digitalRead(SW_pin));
  //Serial.print("\n");
  //Serial.print("X-axis: ");
  //Serial.print(analogRead(X_pin));
  //Serial.print("\n");
  //Serial.print("Y-axis: ");
  //Serial.println(analogRead(Y_pin));
  //Serial.print("\n\n");
  
  if(analogRead(Y_pin) > 510)
  {
    double temper = (((double)(analogRead(Y_pin))-510)/ 514.00);
    double amount = 90 + (90 * temper);
    int temp1 = ((int)amount);
    Serial.print(temper);Serial.print("  \n");Serial.print(amount);Serial.print("  \n");
    Serial.print(temp1);Serial.print("  \n\n");
    if(temp1 > 89)
    {
      myservo.write(89);
    }
    else
    {
      myservo.write(temp1);
    }
    
    myservo.write(temp1);
    //myservo.write(180);
  }
  else if(analogRead(Y_pin) < 470)
  {
    double amount2 = 90 * ((double)(analogRead(Y_pin))/ 470.00);
    int temp2 = ((int)amount2);
    //Serial.print(temp2);Serial.print(" boop ");
    if(temp2 < 1)
    {
      myservo.write(1);
    }
    else
    {
      myservo.write(temp2);
    //myservo.write(0);
    }
    
  }
  else if(analogRead(Y_pin) > 470 || analogRead(Y_pin) < 510)
  {
    myservo.write(90);// move servos to center position -> 90°
  }

redValue = 0;
greenValue = 0;
blueValue = 255;
analogWrite(RED, redValue);
analogWrite(GREEN, greenValue);
analogWrite(BLUE, blueValue);

if(digitalRead(SW_pin) == 0)
{
  int duration = 320;
  redValue = 255;
  greenValue = 255;
  blueValue = 0;
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
  //siren for loop
  for(int s = 750; s < 1500; s++)
  {
    tone(8, s, duration);
    delay(1);
    if(s > 750 && s < 1000)
    {
      redValue = 255;
      greenValue = 255;
      blueValue = 0;
      analogWrite(RED, redValue);
      analogWrite(GREEN, greenValue);
      analogWrite(BLUE, blueValue);
    }
    else if(s > 1000 && s < 1250)
    {
      redValue = 255;
      greenValue = 100;
      blueValue = 0;
      analogWrite(RED, redValue);
      analogWrite(GREEN, greenValue);
      analogWrite(BLUE, blueValue);
    }
    if(s > 1250 && s < 1500)
    {
      redValue = 255;
      greenValue = 0;
      blueValue = 0;
      analogWrite(RED, redValue);
      analogWrite(GREEN, greenValue);
      analogWrite(BLUE, blueValue);
    }
  }
  //end siren for loop
  
  //tone(8, NOTE_A5, duration);
  //delay(320);
  //tone(8, NOTE_F5, duration);
  
}

if(analogRead(X_pin) < 400)
{
  int duration = 250;
  redValue = 255;
  greenValue = 0;
  blueValue = 0;

  //was NOTE_G5, now is 1500
  tone(8, 1200, duration);
  tone(8, 1200, duration);
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
  for(int row=0;row<8;row++) {
        for(int col=0;col<8;col++) {
          lc.setLed(0,row,col,true);
        }
    }
  delay(250);
}

else if(analogRead(X_pin) > 950)
{
  int duration = 500;
  redValue = 0;
  greenValue = 255;
  blueValue = 0;
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
   lc.setRow(0,2,B00111100);
   lc.setRow(0,3,B00111100);
   lc.setRow(0,4,B00111100);
   lc.setRow(0,5,B00111100);
   tone(8, NOTE_C5, duration);
   //delay(500);  
    /*
   //EEEE C D E DE
   tone(8, NOTE_E5, 180);
       delay(180);  
   tone(8, NOTE_E5, 180);
       delay(180);
   tone(8, NOTE_E5, 180);
       delay(180);
   tone(8, NOTE_E5, 400);//300
       delay(400);
   tone(8, NOTE_C5, 360);//390
       delay(360);
   tone(8, NOTE_D5, 450);
       delay(450);
   tone(8, NOTE_E5, 350);
       delay(360);
   tone(8, NOTE_D5, 180);
       delay(180);
   tone(8, NOTE_E5, 450);
       delay(450);  */
       
       
}
/*if((poggers % 2) == 1)
{
  redValue = 0;
  greenValue = 0;
  blueValue = 255;
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
}*/

poggers++;
int theDelay = 20; // 15 for middle, 4 for  servo, 25 for lights
int modular = 4;
  if(poggers%modular == 0)
  {
    for(int row=0;row<8;row++) {
      for(int col=0;col<8;col++) {
        lc.setLed(0,row,col,true);
        lc.setLed(0,row-1,col,false);
      }
              delay(theDelay);
    }
  }
  else if(poggers%modular == 1)
  {
    for(int row=8;row>=0;row--) {
      for(int col=8;col>=0;col--) {
        lc.setLed(0,row,col,false);
        lc.setLed(0,row-1,col,true);
      }
              delay(theDelay);
    }
  }

  else if(poggers%modular == 2)
  {
    for(int row=0;row<8;row++) {
      for(int col=0;col<8;col++) {
        lc.setLed(0,col,row,true);
        lc.setLed(0,col,row-1,false);
      }
              delay(theDelay);
    }
  }

  else if(poggers%modular == 3)
  {
    for(int row=8;row>=0;row--) {
      for(int col=8;col>=0;col--) {
        lc.setLed(0,col,row,false);
        lc.setLed(0,col,row-1,true);
      }
              delay(theDelay);
    }
  }

//delay(69);  //delay 69 ms till next input
}
