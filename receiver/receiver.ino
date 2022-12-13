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
  // while (!Serial);     // Wait for serial monitor to start (need this for USB serial)
  Serial1.begin(9600);

  lcd.begin(16, 2);
  // lcd.print("hello, world!");

  // Clear and enable WDT
  NVIC_DisableIRQ(WDT_IRQn);
  NVIC_ClearPendingIRQ(WDT_IRQn);
  NVIC_SetPriority(WDT_IRQn, 0);
  NVIC_EnableIRQ(WDT_IRQn);

  //Configure and enable WDT GCLK:
  GCLK->GENDIV.reg = GCLK_GENDIV_DIV(4) | GCLK_GENDIV_ID(5);
  while (GCLK->STATUS.bit.SYNCBUSY);
  GCLK->GENCTRL.reg = GCLK_GENCTRL_DIVSEL | GCLK_GENCTRL_ID(5) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_OSCULP32K;
  while (GCLK->STATUS.bit.SYNCBUSY);
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(5) | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID(3);

  // Configure and enable WDT:
  // use WDT->CONFIG.reg, WDT->EWCTRL.reg, WDT->CTRL.reg
  // sync CTRL and CLEAR
  WDT->CONFIG.reg = 0x9; // 2048
  WDT->EWCTRL.reg = 0x8; // 2048
  WDT->CTRL.reg = WDT_CTRL_ENABLE;
  while (WDT->STATUS.bit.SYNCBUSY);

  // Enable early warning interrupts on WDT:
  // reference WDT registers with WDT->register_name.reg
  WDT->INTENSET.bit.EW = 1;
}


/*
 * Des: A display function for the game over state. 
 * Input: n/a
 * Output: n/a
 * Effect: Displays 'Congrats! You won!' to the LCD screen. 
 * 
 */
void display_win() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Congrats!");
  lcd.setCursor(0, 1);
  lcd.print("You won!");
}

/*
 * Des: A display function for the in game state. 
 * Input: n/a
 * Output: n/a
 * Effect: Displays 'Congrats! You won!' to the LCD screen. 
 * 
 */
void display_in_progress() {
  lcd.clear();
  lcd.print("Game in progress");
}

/*
 * Des: A display function for the in display countdown state. 
 * Input: an int (3, 2, or 1) representing the number at which the countdown is at currently. 
 * Output: n/a
 * Effect: Displays 'Countdown: 3', 'Countdown: 2' or 'Countdown: 1' depending on the int input.  
 * 
 */
void display_countdown(int n) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Countdown: ");
  lcd.setCursor(0, 1);
  lcd.print(n);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available() > 0) {
    b = Serial1.read();
    Serial.println(b);
    if (b == 5 && !hasWon) {
      display_win();
      hasWon = true;
    }
    else if (b == 3 || b == 2 || b == 1) {
      display_countdown(b);
      hasWon = false;
      inProgress = false;
    }
    else if (b == 4 && !inProgress) {
      display_in_progress();
      inProgress = true;
    }
    // pet the watchdog
    WDT->CLEAR.reg = 0xA5;

  }
}

/*
 * Des: a watchdog timer handler function that clears interrupt register flag and alerts user that connection has been lost between the two microcontrollers 
 * Input: n/a 
 * Output: n/a
 * Effect: Displays "Connection lost?" to LCD screen
 * 
 */
void WDT_Handler() {
  // Clear interrupt register flag
  // (reference register with WDT->register_name.reg)
  WDT->INTFLAG.reg = 1;

  // Warn user that a  reset may happen
  lcd.clear();
  lcd.print("Connection lost?");
  Serial.println("watch dog reset may happen");
}
