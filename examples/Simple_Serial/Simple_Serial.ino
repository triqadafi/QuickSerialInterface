// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
// [QuickSerialInterface]
// Format data yang dikirim agar bisa diproses
//
// FI#[ACTION]=[PARAMETER_0];[PARAMETER_1];[PARAMETER_...N];
// contoh:  - FI#0=100;123;
//          - FI#99=0;0;
//
// !!! janga lupa kirim pakai newline \n
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

#include <Arduino.h>
#include <QuickSerialInterface.h>

#define MAIN_PERIOD 100

QuickSerialInterface trqdf_interface(&TRQDF_onRead);

unsigned long FI_MAIN_millis = 0;

void setup() {
  trqdf_interface.begin(115200, true);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  trqdf_interface.loop();
  
  if(millis() - FI_MAIN_millis > MAIN_PERIOD){
    FI_MAIN_millis = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    
  }
}

void TRQDF_onRead(){
  switch (trqdf_interface.readAction()){
    case 0:
      // do other stuff
      Serial.print("Execute Action 0");
      Serial.println();
      delay(1);
      Serial.print("Parameter 0: ");
      Serial.print(trqdf_interface.readParameter(0));
      Serial.println();
      delay(1);
      Serial.print("Parameter 1: ");
      Serial.print(trqdf_interface.readParameter(1));
      Serial.println();
      delay(1);
      Serial.print("Parameter 2: ");
      Serial.print(trqdf_interface.readParameter(2));
      Serial.println();
      delay(1);
      Serial.print("Parameter 3: ");
      Serial.print(trqdf_interface.readParameter(3));
      Serial.println();
      delay(1);
      Serial.print("Parameter 4: ");
      Serial.print(trqdf_interface.readParameter(4));
      Serial.println();
      delay(1);

      break;
    case 99:
      Serial.print("Execute Action 99");
      Serial.println();
      delay(1);
      Serial.print("Parameter 0: ");
      Serial.print(trqdf_interface.readParameter(0));
      Serial.println();
      delay(1);
      Serial.print("Parameter 1: ");
      Serial.print(trqdf_interface.readParameter(1));
      Serial.println();
      delay(1);
      Serial.print("Parameter 2: ");
      Serial.print(trqdf_interface.readParameter(2));
      Serial.println();
      delay(1);
      Serial.print("Parameter 3: ");
      Serial.print(trqdf_interface.readParameter(3));
      Serial.println();
      delay(1);
      Serial.print("Parameter 4: ");
      Serial.print(trqdf_interface.readParameter(4));
      Serial.println();
      delay(1);
      break;

  }
}