#ifndef BUTTON_H_
#define BUTTON_H_

#define PRESSED 0
#define RELEASED 1

enum ButtonState {
    BUTTON_PRESSED,
    SHORT_PRESSED,
    MIDDLE_PRESSED,
    LONG_PRESSED,
    BUTTON_NOT_PRESSED,
    BUTTON_JUST_PRESSED,
    BUTTON_JUST_RELEASED,
};

class Button {

    private: 
        #define SHORT_PRESS_TIME 1000
        #define MIDDLE_PRESS_TIME 2000
        #define LONG_PRESS_TIME 3000
        #define SHORT_PRESS_MIN 10
        #define SHORT_PRESS_MAX (SHORT_PRESS_MIN + SHORT_PRESS_TIME)
        #define MIDDLE_PRESS_MIN (SHORT_PRESS_MAX + 1)
        #define MIDDLE_PRESS_MAX (SHORT_PRESS_MAX + MIDDLE_PRESS_TIME)
        #define LONG_PRESS_MIN (MIDDLE_PRESS_MAX + 1)
        #define LONG_PRESS_MAX (LONG_PRESS_MIN + LONG_PRESS_TIME)

        uint8_t buttonGpio;
        ButtonState buttonState = BUTTON_NOT_PRESSED;     // current state of the button
        uint8_t lastButtonState = BUTTON_NOT_PRESSED; // previous state of the button
        unsigned long startPressed = 0;    // the moment the button was pressed
        unsigned long endPressed = 0;      // the moment the button was released
        unsigned long holdTime = 0;        // how long the button was hold
        unsigned long idleTime = 0;        // how long the button was idle

     public:
        Button(uint8_t);
        uint8_t getGpio(void);
        unsigned long getButtonEndPressed(void);
        void setButtonState(ButtonState);
        ButtonState getButtonState(void);
        unsigned long getButtonPresStart(void);
        uint8_t isButtonPressed(void);
        uint8_t getLastButtonState(void);
        void setButtonStartPressed(unsigned long);
        void setButtonEndPressed(unsigned long);
        unsigned long getButtonPressedTime(void);
        void updateButtonState(void);
        void updatePressTime(void);
};
#endif // BUTTON_H_
