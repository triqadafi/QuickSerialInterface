//
// QuickSerialInterface Library by @triqadafi
// TQDF is a shorthand of triqadafi
// 2022 (C) www.triqada.fi
//


#include <Arduino.h>

#ifndef TQDF_QuickSerialInterface_h
#define TQDF_QuickSerialInterface_h
#include <stdint.h>

typedef std::function<void(void)> QSI_function_t;

#define QSI_PARAMETERS_TOTAL 5
#define QSI_LOCK_BYTES "TQ#"

#define QSI_Serial QSI_USBSerial
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
     * @param _keypad keypad instance
     * @param _lcd_i2c LCD i2c instance
     * @param _main_menu main menu variable
     */
    QuickSerialInterface(void(*callback)(void));
    // QuickSerialInterface();

    /**
     * @brief Menu idle state
     * 
     */
    void begin(unsigned long baudrate, bool wait_connect);
    void loop();
    void onRead(void(*callback)(void));
    uint8_t readAction();
    unsigned long  readParameter(int parameter_number);

  private:
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