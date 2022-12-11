/// 3,2,1 for countdown
/// 4 game in progress
/// 5 for game over/won

#include <LiquidCrystal.h>

byte b = 0;

const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

bool hasWon = false;
bool inProgress = false;

void setup() {
  Serial.begin(9600);  // Initialize serial monitor
  while (!Serial);     // Wait for serial monitor to start (need this for USB serial)
  Serial1.begin(9600); 

  lcd.begin(16, 2);
  // lcd.print("hello, world!");
}

void loop() {
  //put your main code here, to run repeatedly:
  if (Serial1.available() > 0) {
    b = Serial1.read();
    Serial.println(b);
    if (b == 5 && !hasWon) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Congrats!");
      lcd.setCursor(0,1);
      lcd.print("You won!");
      hasWon = true;
    } 
    else if (b == 3 || b == 2 || b == 1) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Countdown: ");
      lcd.setCursor(0,1);
      lcd.print(b);
      hasWon = false;
      inProgress = false;
    } 
    else if (b == 4 && !inProgress) {
      lcd.clear();
      lcd.print("Game in progress");
      inProgress = true;
    }
  }
}
