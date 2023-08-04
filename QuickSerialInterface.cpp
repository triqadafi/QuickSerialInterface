
#include "QuickSerialInterface.h"

QuickSerialInterface::QuickSerialInterface(){

}

void QuickSerialInterface::begin(Stream* serial, void(*callback)(void)){
  QSI_Stream = serial;
  QSI_Callback = callback;

}
uint8_t QuickSerialInterface::readAction(){
  return QSI_Action;
}

unsigned long QuickSerialInterface::readParameter(int parameter_number){
  return QSI_Parameters[parameter_number];
}


void QuickSerialInterface::loop(){
  while(QSI_Stream->available()){
    char _char = QSI_Stream->read();
    // QSI_Stream->print("[");
    // QSI_Stream->print(_char);
    // QSI_Stream->print("]");
    QSI_USART_buffer[QSI_USART_index++] = _char;
    if(_char == '\n') {
      QSI_USART_buffer[QSI_USART_index] = '\0';
      QSI_USART_index = 0;
      if(strstr(QSI_USART_buffer, QSI_LOCK_BYTES) != NULL){
        // QSI_Stream->print("[+++]");
        QSI_USART_flag = true;
      }
      break;
    }
  }

  if(QSI_USART_flag){
    // Clean Buffer
    char *_buffer;
    char *_token = multi_tok(QSI_USART_buffer, QSI_LOCK_BYTES);

    while (_token != NULL) {
      _buffer = _token;
      _token = multi_tok(NULL, QSI_LOCK_BYTES);
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
      // QSI_Stream->print("Token index. ");
      // QSI_Stream->print(parameter_index);
      // QSI_Stream->print(" : ");
      // QSI_Stream->print(token3);
      // QSI_Stream->print(atol(token3));
      // QSI_Stream->println();
      QSI_Parameters[parameter_index] = atof(token3);

      token3 = multi_tok(NULL,";");
      parameter_index++;
      if(parameter_index == QSI_PARAMETERS_TOTAL) break;
    }

    QSI_Callback();


    QSI_USART_flag = false;
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