#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int timeInterval;
int score;
bool gameStarted;

// TODO: timeInterval and timeInterval decrement have to allow for 99 succesful attempts

void setup() {
  // put your setup code here, to run once:
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  pinMode(0, INPUT); //on/off switch
  pinMode(1, INPUT); //start game button
  timeInterval = 3000;
  score = 0;
  gameStarted = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  //maybe not necessary, should connect/disconnect from power
  if(digitalRead(0) == HIGH) {
    lcd.setCursor ( 0, 0 );            
    lcd.print("       Bop-it       "); 
    lcd.setCursor ( 0, 1 );           
    lcd.print("Press btn to start"); 
    if(digitalRead(1) == HIGH) {
      gameStarted = true;
    }
    if(score == 99) {
      endGame();
    }

    if(gameStarted == true) {
      emitCommand();
    }
  }
}

void endGame() {
  lcd.clear();
  lcd.setCursor ( 0, 0 );            
  lcd.print("     Game Over      "); 
  // TODO: Center score, will be between 0 and 99
  lcd.setCursor ( 0, 1 );
  String scoreString = String(score);            
  lcd.print(scoreString); 
  score = 0;
  timeInterval = 3000;
  gameStarted = false;
}

void emitCommand() {
  long command = random(1,3);
  bool inputPressedWithinInterval = false;
  if(command == 1) {
    // TODO: announce command
    unsigned long startTime = millis();
    while(millis() - startTime < timeInterval) {
      if(/*TODO: check for input pressed*/1) {
        inputPressedWithinInterval = true;
        break;
      }
    }
    if(inputPressedWithinInterval == true) {
      score++;
      timeInterval-= 250;
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("      Success!      "); 
    } else {
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("      Failure!      ");
      delay(1000);
      endGame();
    }
    
  }
  if(command == 2) {
    // TODO: announce command
    unsigned long startTime = millis();
    while(millis() - startTime < timeInterval) {
      if(/*TODO: check for input pressed*/1) {
        inputPressedWithinInterval = true;
        break;
      }
    }
    if(inputPressedWithinInterval == true) {
      score++;
      timeInterval-= 250;
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("      Success!      "); 
    } else {
        lcd.clear();
        lcd.setCursor ( 0, 0 );            
        lcd.print("      Failure!      ");
        delay(1000);
        endGame();
    }
  }
  if(command == 3) {
    // TODO: announce command
    unsigned long startTime = millis();
    while(millis() - startTime < timeInterval) {
      if(/*TODO: check for input pressed*/1) {
        inputPressedWithinInterval = true;
        break;
      }
    }
    if(inputPressedWithinInterval == true) {
      score++;
      timeInterval-= 250;
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("      Success!      "); 
    } else {
      lcd.clear();
      lcd.setCursor ( 0, 0 );            
      lcd.print("      Failure!      ");
      delay(1000);
      endGame();
    }
  }
}
