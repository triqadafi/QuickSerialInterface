// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
// [QuickSerialInterface]
// Format data yang dikirim agar bisa diproses
//
// TQ#[ACTION]=[PARAMETER_0];[PARAMETER_1];[PARAMETER_...N];
// contoh:  - TQ#0=100;123;
//          - TQ#99=0;0;
//
// !!! janga lupa kirim pakai newline \n
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

#include <QuickSerialInterface.h>
// #include "src/QuickSerialInterface/QuickSerialInterface.h"

#define MAIN_PERIOD 1000

QuickSerialInterface SerialInterface;

unsigned long TQDF_MAIN_millis = 0;

void setup() {
  SerialInterface.begin(Serial, &SerialInterface_onRead);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  SerialInterface.loop();
  
  if(millis() - TQDF_MAIN_millis > MAIN_PERIOD){
    TQDF_MAIN_millis = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    Serial.print("Waiting Action... ex: TQ#99=10;0;12;");

  }
}

void SerialInterface_onRead(){
  switch (SerialInterface.readAction()){
    case 0:
      // do other stuff
      Serial.print("Execute Action 0");
      Serial.println();
      delay(1);
      Serial.print("Parameter 0: ");
      Serial.print(SerialInterface.readParameter(0));
      Serial.println();
      delay(1);
      Serial.print("Parameter 1: ");
      Serial.print(SerialInterface.readParameter(1));
      Serial.println();
      delay(1);
      Serial.print("Parameter 2: ");
      Serial.print(SerialInterface.readParameter(2));
      Serial.println();
      delay(1);
      Serial.print("Parameter 3: ");
      Serial.print(SerialInterface.readParameter(3));
      Serial.println();
      delay(1);
      Serial.print("Parameter 4: ");
      Serial.print(SerialInterface.readParameter(4));
      Serial.println();
      delay(1);

      break;
    case 99:
      Serial.print("Execute Action 99");
      Serial.println();
      delay(1);
      Serial.print("Parameter 0: ");
      Serial.print(SerialInterface.readParameter(0));
      Serial.println();
      delay(1);
      Serial.print("Parameter 1: ");
      Serial.print(SerialInterface.readParameter(1));
      Serial.println();
      delay(1);
      Serial.print("Parameter 2: ");
      Serial.print(SerialInterface.readParameter(2));
      Serial.println();
      delay(1);
      Serial.print("Parameter 3: ");
      Serial.print(SerialInterface.readParameter(3));
      Serial.println();
      delay(1);
      Serial.print("Parameter 4: ");
      Serial.print(SerialInterface.readParameter(4));
      Serial.println();
      delay(1);
      break;

  }
}