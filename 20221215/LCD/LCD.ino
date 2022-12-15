#include<LiquidCrystal_I2C_Hangul.h>
#include<Wire.h>
LiquidCrystal_I2C_Hangul lcd1(0x3F,16,2);
LiquidCrystal_I2C_Hangul lcd2(0x27,16,2); 
LiquidCrystal_I2C_Hangul lcd3(0x30,16,2); 
void setup() {
  Serial.begin(115200);
  lcd1.init();
  lcd1.backlight();
  lcd1.print("1Hello World!");
  lcd1.setCursor(0,1);
  lcd1.print("Peter, Wu");
  lcd2.init();
  lcd2.backlight();
  lcd2.print("2Hello World!");
  lcd2.setCursor(0,1);
  lcd2.print("Peter, Wu");
  lcd3.init();
  lcd3.backlight();
  lcd3.print("3Hello World!");
  lcd3.setCursor(0,1);
  lcd3.print("Peter, Wu");
}
void loop() {
}
