//
// QuickSerialInterface Library by @triqadafi
// TQDF is a shorthand of triqadafi
// 2022 (C) www.triqada.fi
//


#include <Arduino.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>

#ifndef TQDF_QuickSerialInterface_h
#define TQDF_QuickSerialInterface_h
#include <stdint.h>

typedef std::function<void(void)> QSI_function_t;

#define QSI_PARAMETERS_TOTAL 5
#define QSI_LOCK_BYTES "TQ#"

void TQDF_onRead();

/**
 * @brief test coba coba tentang brief
 * 
 * dibawahnya ini harusnya comment
 * 
 */
class QuickSerialInterface
{
  public:
    /**
     * @brief Construct a new TQDF_QuickSerialInterface object
     * 
     */
    QuickSerialInterface();
    // QuickSerialInterface();

    /**
     * @brief Menu idle state
     * 
     */
    void begin(Stream* serial, void(*callback)(void));
    void loop();
    void onRead(void(*callback)(void));
    uint8_t readAction();
    unsigned long  readParameter(int parameter_number);

  private:
    Stream* QSI_Stream; 
    void(*QSI_Callback)(void);
    void* displayText();

    int SYS_State;

    char QSI_USART_buffer[72] = {0};  // a string to hold incoming data
    bool QSI_USART_flag = false;        // whether the string is complete
    uint8_t QSI_USART_index = 0;

    uint8_t QSI_Action = 0;  // a string to hold incoming data
    unsigned long QSI_Parameters[QSI_PARAMETERS_TOTAL] = {0};  // a string to hold incoming data
    char *multi_tok(char *input, char *delimiter);
};
#endif