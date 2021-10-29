#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int timeInterval;
int timeIntervalDecrement;
int score;
bool gameStarted;

const int buzzer = 3; 
const int testLed= 0;
const int startButton = 1;
const int buttonInput = 9;
const int switchInput = 2;

void setup() {
  lcd.init();
  lcd.backlight();   
  pinMode(testLed, INPUT);
  pinMode(startButton, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonInput, INPUT);
  pinMode(switchInput, INPUT);
  timeInterval = 10000;
  timeIntervalDecrement = 100;
  score = 0;
  gameStarted = false;
}


void loop() {
    if(gameStarted==false) {
    lcd.setCursor ( 0, 0 );            
    lcd.print("     Bop-it       "); 
    lcd.setCursor ( 0, 1 );           
    lcd.print("Push btn 2 start"); 
    }
    if(digitalRead(startButton) == HIGH) {
      gameStarted = true;
    }
    if(score == 99) {
      endGame();
    }

    if(gameStarted == true) {
      emitCommand();
    }
}

void endGame() {
  digitalWrite(testLed, HIGH);
  delay(1000);
  digitalWrite(testLed, LOW);
  lcd.clear();
  lcd.setCursor ( 0, 0 );            
  lcd.print("   Game Over      "); 
  lcd.setCursor ( 0, 1 );
  String scoreString = String(score);            
  lcd.print("    Score: " + scoreString); 
  score = 0;
  timeInterval = 10000;
  gameStarted = false;
  delay(5000);
}

void emitCommand() {  
  // TODO: inlcude joystick input i.e. random(1,4)
  long command = random(1,3);
  bool inputPressedWithinInterval = false;

  // button
  if(command == 1) {
    tone(buzzer, 250,1000);
    delay(1000);
    unsigned long startTime = millis();
    while(millis() - startTime < timeInterval) {
      if(digitalRead(buttonInput)==HIGH) {
        inputPressedWithinInterval = true;
        break;
      }
    }
    if(inputPressedWithinInterval == true) {
      score++;
      timeInterval-= timeIntervalDecrement;
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("    Success!      ");
      delay(1000);
      lcd.clear(); 
    } else {
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("    Failure!      ");
      delay(1000);
      endGame();
    }
    
  }
  
  // switch
  if(command == 2) {
    tone(buzzer, 500,1000);
    delay(1000);
    unsigned long startTime = millis();
    while(millis() - startTime < timeInterval) {
      if(digitalRead(switchInput)==HIGH) {
        inputPressedWithinInterval = true;
        break;
      }
    }
    if(inputPressedWithinInterval == true) {
      score++;
      timeInterval-= timeIntervalDecrement;
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("    Success!      "); 
      delay(1000);
      lcd.clear(); 
    } else {
        lcd.clear();
        lcd.setCursor ( 0, 0 );            
        lcd.print("    Failure!      ");
        delay(1000);
        endGame();
    }
  }

  // joystick
  if(command == 3) {
    // TODO: announce command
    tone(buzzer, 5000);
    unsigned long startTime = millis();
    while(millis() - startTime < timeInterval) {
      if(/*TODO: read joystick input*/1) {
        inputPressedWithinInterval = true;
        break;
      }
    }
    if(inputPressedWithinInterval == true) {
      score++;
      timeInterval-= timeIntervalDecrement;
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("      Success!      ");
      delay(1000);
      lcd.clear(); 
    } else {
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("      Failure!      ");
      delay(1000);
      endGame();
    }
  }
  
}
