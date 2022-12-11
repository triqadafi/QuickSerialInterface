
#include "QuickSerialInterface.h"



QuickSerialInterface::QuickSerialInterface(void(*callback)(void)){
  QSI_Callback = callback;
  // Serial.printf("%p", callback);
  // Serial.printf("%p", QSI_Callback);
}

void QuickSerialInterface::begin(unsigned long baudrate, bool wait_connect){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  while (!Serial && wait_connect) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(700);
  }
  digitalWrite(LED_BUILTIN, HIGH);
}
uint8_t QuickSerialInterface::readAction(){
  return QSI_Action;
}

unsigned long QuickSerialInterface::readParameter(int parameter_number){
  return QSI_Parameters[parameter_number];
}


void QuickSerialInterface::loop(){
  while(Serial.available()){
    char _char = Serial.read();
    // Serial.print("[");
    // Serial.print(_char);
    // Serial.print("]");
    UB_USART_buffer[UB_USART_index++] = _char;
    if(_char == '\n') {
      UB_USART_buffer[UB_USART_index] = '\0';
      UB_USART_index = 0;
      if(strstr(UB_USART_buffer, UB_LOCK_BYTES) != NULL){
        // Serial.print("[+++]");
        UB_USART_flag = true;
      }
      break;
    }
  }

  if(UB_USART_flag){
    // Clean Buffer
    char *_buffer;
    char *_token = multi_tok(UB_USART_buffer, UB_LOCK_BYTES);

    while (_token != NULL) {
      _buffer = _token;
      _token = multi_tok(NULL, UB_LOCK_BYTES);
    }

    // Process Buffer
    unsigned parameter_index = 0;
    char *_buffer2;
    char *token2 = multi_tok(_buffer, "=");
    if (token2 != NULL) {
      QSI_Action = atol(token2);
    }

    char *token3 = multi_tok(_buffer2, ";");
    while(token3 != NULL)
    {
      // Serial.print("Token index. ");
      // Serial.print(parameter_index);
      // Serial.print(" : ");
      // Serial.print(token3);
      // Serial.print(atol(token3));
      // Serial.println();
      QSI_Parameters[parameter_index] = atol(token3);

      token3 = multi_tok(NULL,";");
      parameter_index++;
      if(parameter_index == QSI_PARAMETERS_TOTAL) break;
    }

    QSI_Callback();


    UB_USART_flag = false;
  }
}


char *QuickSerialInterface::multi_tok(char *input, char *delimiter) {
    static char *string;
    if (input != NULL)
        string = input;

    if (string == NULL)
        return string;

    char *end = strstr(string, delimiter);
    if (end == NULL) {
        char *temp = string;
        string = NULL;
        return temp;
    }

    char *temp = string;

    *end = '\0';
    string = end + strlen(delimiter);
    return temp;
}