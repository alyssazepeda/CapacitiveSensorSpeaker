#include <CapacitiveSensor.h>
#include "pitches.h"

#define speaker 13
#define LED A1
#define button A0

//initialize touch sensors
CapacitiveSensor SensorE4 = CapacitiveSensor(2,12);
CapacitiveSensor SensorF4 = CapacitiveSensor(2,10);
CapacitiveSensor SensorG4 = CapacitiveSensor(2,9);
CapacitiveSensor SensorA4 = CapacitiveSensor(2,8);
CapacitiveSensor SensorB4 = CapacitiveSensor(2,7);
CapacitiveSensor SensorC5 = CapacitiveSensor(2,6);
CapacitiveSensor SensorCS5 = CapacitiveSensor(2,5);
CapacitiveSensor SensorD5 = CapacitiveSensor(2,4);


void setup() {
  // put your setup code here, to run once:
   // turn off autocalibrate to ensure speaker is silent
  SensorE4.set_CS_AutocaL_Millis(0xFFFFFFFF);    
  SensorF4.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  SensorG4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  SensorA4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  SensorB4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  SensorC5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  SensorCS5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  SensorD5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);
} 

enum ButtonStates {B_Start, OFF_R, ON_P, ON_R, OFF_P} ButtonState;

//This function ensures the LED is set to on once the user presses the button
//and will stay on until the user presses the button again
void TickFct_Button() {
  switch(ButtonState) {
    case B_Start: ButtonState = OFF_R; break;
    case OFF_R: ButtonState = (digitalRead(button)==HIGH) ? ON_P : OFF_R; break;
    case ON_P: ButtonState = (digitalRead(button)==HIGH) ? ON_P : ON_R; break;
    case ON_R: ButtonState = (digitalRead(button)==HIGH) ? OFF_P : ON_R; break;
    case OFF_P: ButtonState = (digitalRead(button)==HIGH) ? OFF_P : OFF_R; break;
    default: ButtonState = B_Start; break;
  }
  switch(ButtonState) {
    case B_Start: digitalWrite(LED, LOW); break;
    case OFF_R:  digitalWrite(LED, LOW); break;
    case ON_P:  digitalWrite(LED, HIGH); break;
    case ON_R:  digitalWrite(LED, HIGH); break;
    case OFF_P:  digitalWrite(LED, LOW); break;
    default: break;
  }
}

void playMusic() {
  long sE4 = SensorE4.capacitiveSensorRaw(30);
  long sF4 = SensorF4.capacitiveSensorRaw(30);
  long sG4 = SensorG4.capacitiveSensorRaw(30);
  long sA4 = SensorA4.capacitiveSensorRaw(30);
  long sB4 = SensorB4.capacitiveSensorRaw(30);
  long sC5 = SensorC5.capacitiveSensorRaw(30);
  long sCS5 = SensorCS5.capacitiveSensorRaw(30);
  long sD5 = SensorD5.capacitiveSensorRaw(30);

  //Here we are printing the sensor reading for each sensor
  //they stay under 300 but will go above 400 when touched
  Serial.print(sE4);
  Serial.print('\t');
  Serial.print(sF4);
  Serial.print('\t');
  Serial.print(sG4);
  Serial.print('\t');
  Serial.print(sA4);
  Serial.print('\t');
  Serial.print(sB4);
  Serial.print('\t');
  Serial.print(sC5);
  Serial.print('\t');
  Serial.print(sCS5);
  Serial.print('\t');
  Serial.print(sD5);
  Serial.print('\n');

  //play the tones when the music note is touched
  if(sE4 > 400){
    tone(speaker, NOTE_E4, 2000);
    delay(2450);
  }
  if(sF4 > 400) {
    tone(speaker, NOTE_F4, 1000);
    delay(1450);
  }
  if(sG4 > 400){
    tone(speaker, NOTE_G4, 500);
    delay(950);
  }
  if(sA4 > 400) {
    tone(speaker, NOTE_A4, 250);
    delay(700);
  }
  if(sB4 > 400){
    tone(speaker, NOTE_B4, 125);
    delay(125);
    tone(speaker, NOTE_C5, 125);
    delay(700);
  }
  if(sC5 > 400) {
    tone(speaker, NOTE_C5, 125);
    delay(125);
    tone(speaker, NOTE_D5, 125);
    delay(125);
    tone(speaker, NOTE_E5, 125);
    delay(125);
    tone(speaker, NOTE_F5, 125);
    delay(950);
  }
  if(sCS5 > 400){
    tone(speaker, NOTE_C5, 250);
    delay(250);
    tone(speaker, NOTE_CS5, 250);
    delay(950);
  }
  if(sD5 > 400) {
    tone(speaker, NOTE_D5, 1000);
    delay(1450);
  }
  else {noTone(speaker);}
  delay(50);
}

void loop() {
  //initialize the start state
  ButtonState = B_Start;
  while(1) {
    TickFct_Button();
    if(digitalRead(LED) == HIGH) {
      playMusic();
    }
  }
}
