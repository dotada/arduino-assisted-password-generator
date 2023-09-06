#include <SPI.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key = 0;
int adc_key_in = 0;
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
int finishedscreen = false;
unsigned long randomnum = 2;

// THIS IS FOR V1
int read_LCD_buttons() {
  adc_key_in = analogRead(0);
  if (adc_key_in < 50) return btnRIGHT;
  if (adc_key_in < 195) return btnUP;
  if (adc_key_in < 380) return btnDOWN;
  if (adc_key_in < 555) return btnLEFT;
  if (adc_key_in < 790) return btnSELECT;

  return btnNONE;  // when all others fail, return this...
}

/* THI IS FOR V2
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);
 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;

  return btnNONE;  // when all others fail, return this...
}
COMMENT OUT THE PREVIOUS ONE FIRST!!!!!!!!!!
*/ 

int randtempseed() {
  delay(500);
  int seed = analogRead(1);
  /*
  Serial.print("Seed: ");
  Serial.print(seed);
  Serial.println("");
  */
  return seed;
}

int32_t getrandnum1() {
  delay(1500);
  int32_t num1 = random(1, 255645565);
  /*
  Serial.print("Num1: ");
  Serial.print(num1);
  Serial.println("");
  */
  return num1;
}

int32_t randomscreennum() {
  while (true) {
    if (!finishedscreen) {
      int angread = analogRead(0);
      if (read_LCD_buttons() == btnSELECT) {
        lcd.clear();
        finishedscreen = true;
        return randomnum;
        break;
      }
      if (angread > 0 && angread < 800) {
        randomnum += angread;
        /*
        Serial.print("Randomnum: ");
        Serial.print(randomnum);
        Serial.println("");
        Serial.print("Angread: ");
        Serial.print(angread);
        Serial.println("");
        */
        delay(50);
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  lcd.begin(16, 2);
  int seed = randtempseed();
  randomSeed(seed);
  lcd.setCursor(0, 0);
  lcd.clear();
  delay(2000);
  int32_t num1 = getrandnum1();
  //Serial.print("Num1 (setup): ");
  //Serial.print(num1);
  //Serial.println("");
  lcd.write("Left,up,right &");
  delay(50);
  lcd.setCursor(0, 1);
  delay(50);
  lcd.write("down for rng");
  int32_t num2 = randomscreennum();
  //Serial.println("Final results below.");
  //Serial.println(num1);
  //Serial.println(num2);
  //Serial.print("Final number: ");
  int32_t finalnum = num1 + num2;
  //Serial.print(finalnum);
  //Serial.println("");
  randomSeed(finalnum);
  int32_t numtosend = finalnum * random(3, 25);
  /*
  Serial.print("Number to send: ");
  Serial.print(numtosend);
  Serial.println();
  delay(500);
  Serial.end();
  */
  Serial.begin(74880);
  Serial.println(numtosend);
  delay(500);
  Serial.end();
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Done. Press re-");
  lcd.setCursor(0, 1);
  lcd.write("set to retry.");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
