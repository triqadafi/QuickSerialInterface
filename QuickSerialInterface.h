//
// QuickSerialInterface Library by @triqadafi
// TRQDF is a shorthand of triqadafi
// 2022 (C) www.triqada.fi
//
//
// Big thanks to the source of inspiration: 
//    https://www.semesin.com/project/2018/04/13/dinamik-menu-dan-submenu-dengan-keypad-dan-lcd-16x2-menggunakan-arduino/
//

#include <Arduino.h>

#ifndef TRQDF_QuickSerialInterface_h
#define TRQDF_QuickSerialInterface_h
#include <stdint.h>

typedef std::function<void(void)> QSI_function_t;

#define QSI_PARAMETERS_TOTAL 5
#define UB_LOCK_BYTES "FI#"

#define QSI_Serial QSI_USBSerial
void TRQDF_onRead();

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
     * @brief Construct a new TRQDF_QuickSerialInterface object
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

    char UB_USART_buffer[72] = {0};  // a string to hold incoming data
    bool UB_USART_flag = false;        // whether the string is complete
    uint8_t UB_USART_index = 0;

    uint8_t QSI_Action = 0;  // a string to hold incoming data
    unsigned long QSI_Parameters[QSI_PARAMETERS_TOTAL] = {0};  // a string to hold incoming data
    char *multi_tok(char *input, char *delimiter);
};
#endif