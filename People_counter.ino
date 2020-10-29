#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <TM1638lite.h>
LiquidCrystal_I2C lcd(0x27,16,2);
TM1638lite tm(4, 7, 8);
const int trigSensorIn = 9;
const int echoSensorIn = 10;
const int trigSensorOut = 11;
const int echoSensorOut = 12;
int countPeople = 0;
float noPerson = 70;
float detectedPerson = 50;
const long interval = 1000; 
unsigned long time1 = 0;
int flag = 0;
unsigned long previousMillis = 0; 
int builtInLed = 13;

void setup() {
  pinMode(builtInLed, OUTPUT);
  pinMode(trigSensorIn, OUTPUT);
  pinMode(echoSensorIn, INPUT);
  pinMode(trigSensorOut, OUTPUT);
  pinMode(echoSensorOut, INPUT);
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("People in room =");
  digitalWrite(builtInLed, HIGH);
  tm.reset();
}
float readUltrasonic(int trigPin, int echoPin){
    
  float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  return distance;
}

void loop() {
  while(1){
  float readingSensorIn = readUltrasonic(trigSensorIn, echoSensorIn);
  float readingSensorOut = readUltrasonic(trigSensorOut, echoSensorOut);
  Serial.println(String(readingSensorOut) + " Out");
  Serial.println(String(readingSensorIn) + " In");
  
  if (readingSensorIn < (noPerson - 10)){ // detected person going in
    countPeople++;
    Serial.println("Person walked in");
    Serial.print("people count = ");
    Serial.println(countPeople);
    lcd.setCursor(0,1);
    lcd.print("      ");
    lcd.setCursor(0,1);
    lcd.print(countPeople);
    String counter = String(countPeople);
    tm.displayText("count" + counter);
    digitalWrite(builtInLed, LOW);
    delay(1500);
    digitalWrite(builtInLed, HIGH);
    continue;
  }
  if (readingSensorOut < (noPerson - 10)){ // a person on the second sensor
    countPeople--;
    if(countPeople < 0)countPeople = 0;
    Serial.println("Person walked out.");
    Serial.print("people count = ");
    Serial.println(countPeople);
    lcd.setCursor(0,1);
    lcd.print("      ");
    lcd.setCursor(0,1);
    lcd.print(countPeople);
    String counter = String(countPeople);
    tm.displayText("count" + counter);
    digitalWrite(builtInLed, LOW);
    delay(1500);
    digitalWrite(builtInLed, HIGH);
    continue;
      }
  
      
      
    
  

//  if (readingSensorOut < (noPerson + 10)){ // detected person getting out
//    delay(50);
//    if (readingSensorIn < (noPerson + 10)){ // a person on the second sensor
//      countPeople--;
//    } 
//  }
  
  
//  Serial.print("countPeople: ");
//  Serial.println(countPeople);
  
  delay(100);
  }
}
