#include <LiquidCrystal.h>

const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

void setup() {
  Serial.begin(9600);  // Initialize serial monitor
  while (!Serial);
  lcd.begin(16, 2);
}

void display_win() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Congrats!");
  lcd.setCursor(0, 1);
  lcd.print("You won!");
}

void display_in_progress() {
  lcd.clear();
  lcd.print("Game in progress");
}

void display_countdown(int n) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Countdown: ");
  lcd.setCursor(0, 1);
  lcd.print(n);
}

void loop() {
  Serial.println("standard game seq");
  test_normal_seq();
  Serial.println("seq 1");
  test_seq1();
  Serial.println("seq 2");
  test_seq2();
}
void test_normal_seq() {
  display_countdown(3);
  delay(500);
  display_countdown(2);
  delay(500);
  display_countdown(1);
  delay(500);
  display_in_progress();
  delay(500);
  display_win();
  delay(500);
}

void test_seq1() {
  display_in_progress();
  delay(500);
  display_countdown(3);
  delay(500);
  display_countdown(2);
  delay(500);
  display_countdown(1);
  delay(500);
  display_in_progress();
  delay(500);
  display_win();
}

void test_seq2() {
  display_win();
  delay(500);
  display_countdown(3);
  delay(500);
}
