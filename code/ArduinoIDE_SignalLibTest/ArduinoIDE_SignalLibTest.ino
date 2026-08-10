#include "../thesisCode/main/core/signal/singal.h"

Signal<int> lightSignal;
Signal<int> potiSignal;

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}
int print(int sample, void * param) {
  const char * variableName = (const char*) param;
  Serial.print(sprintf("%s: %d ", variableName, sample));
}

void setLight

void loop() {

  potiSignal.fromValue(analogRead(A7))
            .applyFunction(print, "poti")
            .multiply(-1);
  
  lightSignal.fromValue(analogRead(A6))
             .applyFunction(print, "lightLevel")
             .add(potiSignal)
             .applyFunction(print, "calibrated")
             .toFunction();
  
  int calibrated = lightLevel - poti;
 
  Serial.print(" calibrated:");
  Serial.println(calibrated);

  if(calibrated < 0) {
    digitalWrite(2,HIGH);
  } else {
    digitalWrite(2,LOW);
  }
  
  
  delay(1);                       // wait for a second
}







/**
 * NO signal Lib example 
 * 
 * void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(A6);
  int poti = analogRead(A7);
  int calibrated = lightLevel - poti;
  
  Serial.print("lightLevel:");
  Serial.print(lightLevel);
  Serial.print(" poti:");
  Serial.print(poti);
  Serial.print(" calibrated:");
  Serial.println(calibrated);

  if(calibrated < 0) {
    digitalWrite(2,HIGH);
  } else {
    digitalWrite(2,LOW);
  }
  
  
  delay(1);                       // wait for a second
}
 */



/**
 * Filter Version
 * 
 * void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i = NUMBER_OF_VALUES-1; i > 0; i--) {
    lastValues[i] = lastValues[i-1];
  }
  lastValues[0] = analogRead(A6);
  long sum = 0;
  for(int i = 0; i < NUMBER_OF_VALUES; i++) {
    sum = sum + lastValues[i];
  }
  int filtered = sum/NUMBER_OF_VALUES;
  Serial.print("raw:");
  Serial.print(lastValues[0]);
  Serial.print(" filtered:");
  Serial.print(filtered);
  int poti = analogRead(A7);
  Serial.print(" poti:");
  Serial.print(poti);
  
  int calibrated = filtered - poti;
  
  
  Serial.print(" calibrated:");
  Serial.println(calibrated);

  if(calibrated < 0) {
    digitalWrite(2,HIGH);
  } else {
    digitalWrite(2,LOW);
  }
  
  
  delay(1);                       // wait for a second
}
 * 
 */
