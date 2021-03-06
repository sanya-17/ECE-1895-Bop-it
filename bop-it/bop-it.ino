#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int timeInterval;
int timeIntervalDecrement;
int score;
bool gameStarted;

const int buzzer = 3;
const int startButton = 1;
const int buttonInput = 9;
const int switchInput = 2;
const int vert = 0;
const int horiz = 1;
const int sel = 7;
// TODO: Joystick input

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(startButton, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonInput, INPUT);
  pinMode(switchInput, INPUT);
  pinMode(sel, INPUT_PULLUP);
  timeInterval = 10300;
  timeIntervalDecrement = 100;
  score = 0;
  gameStarted = false;
}

void loop() {
  if (gameStarted == false) {
    lcd.setCursor(0, 0);
    lcd.print("     Bop-it       ");
    lcd.setCursor(0, 1);
    lcd.print("Push btn 2 start");
  }
  if (digitalRead(startButton) == HIGH) {
    gameStarted = true;
  }
  if (score == 99) {
    endGame();
  }

  if (gameStarted == true) {
    emitCommand();
  }
}

void endGame() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Game Over     ");
  lcd.setCursor(0, 1);
  String scoreString = String(score);
  lcd.print("    Score: " + scoreString);
  score = 0;
  timeInterval = 10000;
  gameStarted = false;
  delay(5000);
}

void emitCommand() {
  long command = random(1, 4);
  bool inputPressedWithinInterval = false;

  // button
  if (command == 1) {
    tone(buzzer, 250, 1000);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     Push it     ");
    unsigned long startTime = millis();
    while (millis() - startTime < timeInterval) {
      if (digitalRead(buttonInput) == HIGH) {
        inputPressedWithinInterval = true;
        break;
      }
    }
    if (inputPressedWithinInterval == true) {
      score++;
      timeInterval -= timeIntervalDecrement;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Success!      ");
      lcd.setCursor(0, 1);
      String scoreString = String(score);
      lcd.print("    Score: " + scoreString);
      delay(1000);
      lcd.clear();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Failure!      ");
      delay(1000);
      endGame();
    }
  }

  // switch
  if (command == 2) {
    tone(buzzer, 500, 1000);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Switch it     ");
    unsigned long startTime = millis();
    while (millis() - startTime < timeInterval) {
      if (digitalRead(switchInput) == HIGH) {
        inputPressedWithinInterval = true;
        break;
      }
    }
    if (inputPressedWithinInterval == true) {
      score++;
      timeInterval -= timeIntervalDecrement;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Success!      ");
      lcd.setCursor(0, 1);
      String scoreString = String(score);
      lcd.print("    Score: " + scoreString);
      delay(1000);
      lcd.clear();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Failure!      ");
      delay(1000);
      endGame();
    }
  }

  // joystick
  if (command == 3) {
    tone(buzzer, 1000, 1000);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Joystick it     ");
    unsigned long startTime = millis();  
    while (millis() - startTime < timeInterval) {
      if (analogRead(vert) > 900) {
        inputPressedWithinInterval = true;
        break;
      }
    }
    if (inputPressedWithinInterval == true) {
      score++;
      timeInterval -= timeIntervalDecrement;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Success!      ");
      lcd.setCursor(0, 1);
      String scoreString = String(score);
      lcd.print("    Score: " + scoreString);
      delay(1000);
      lcd.clear();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Failure!      ");
      delay(1000);
      endGame();
    }
  }
}
