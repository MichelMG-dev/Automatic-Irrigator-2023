#include <LiquidCrystal.h>
#include <virtuabotixRTC.h>

#define clk 6
#define dat 7
#define rst 8

#define segL 10
#define minL 3
#define horL 18
#define d_semL 7
#define d_mesL 2
#define mesL 9
#define anoL 2023

virtuabotixRTC myRTC(clk, dat, rst);

int solo1 = 0;
int solo2 = 0;
int solo3 = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.begin(9600);

  //myRTC.setDS1302Time(segL, minL, horL, d_semL, d_mesL, mesL, anoL);  

  lcd.begin(16, 2);
  lcd.clear();

  
}

void loop() {
  solo1 = analogRead(A0);
  solo2 = analogRead(A1);
  solo3 = analogRead(A2);

  myRTC.updateTime(); // Atualize a hora e a data no RTC

  lcd.setCursor(0, 0);
  lcd.print("Hora: ");
  printTwoDigits(myRTC.hours);
  lcd.print(":");
  printTwoDigits(myRTC.minutes);
  lcd.print(":");
  printTwoDigits(myRTC.seconds);

  lcd.setCursor(0, 1);
  lcd.print("Data: ");
  printTwoDigits(myRTC.dayofmonth);
  lcd.print("/");
  printTwoDigits(myRTC.month);
  lcd.print("/");
  printTwoDigits(myRTC.year);

  Serial.print(" -> ");
  printTwoDigits(myRTC.hours);
  Serial.print(":");
  printTwoDigits(myRTC.minutes);
  Serial.print(":");
  printTwoDigits(myRTC.seconds);
  Serial.print(" | Data -> ");
  printTwoDigits(myRTC.dayofmonth);
  Serial.print("/");
  printTwoDigits(myRTC.month);
  Serial.print("/");
  Serial.println(myRTC.year);

  Serial.print("Solo1: ");
  Serial.println(solo1);
  Serial.print("Solo2: ");
  Serial.println(solo2);
  Serial.print("Solo3: ");
  Serial.println(solo3);

  digitalWrite(13, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);

  if (solo1 < 100 && myRTC.hours == 13) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  if (solo2 < 100 && myRTC.hours == 13) {
    digitalWrite(10, HIGH);
  } else {
    digitalWrite(10, LOW);
  }

  if (solo3 < 100 && myRTC.hours == 13) {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }

  delay(1000);
}

void printTwoDigits(int number) {
  if (number < 10) {
    lcd.print("0");
    Serial.print("0");
  }
  lcd.print(number);
  Serial.print(number);
}
