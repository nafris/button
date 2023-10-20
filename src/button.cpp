//#include "sys.h"
#include "driver/gpio.h"
#include "button.h"
#include "esp_timer.h"


Button::Button(gpio_num_t gpio) {
  buttonGpio = gpio;
  gpio_set_direction(gpio, GPIO_MODE_INPUT);
}

gpio_num_t Button::getGpio(void) {
  return buttonGpio;
}

unsigned long long Button::getButtonEndPressed(void) {
  return endPressed;
}

void Button::setButtonState(ButtonState state) {
  buttonState = state;
}

ButtonState Button::getButtonState(void) {
  return buttonState;
}

unsigned long long Button::getButtonPresStart(void) {
  return startPressed;
}

uint8_t Button::isButtonPressed(void) {
  if(gpio_get_level(GPIO_NUM_9) == PRESSED) return 1;
  else return 0;
}

uint8_t Button::getLastButtonState(void) {
  return lastButtonState;
}

void Button::setButtonStartPressed(unsigned long startPr) {
  startPressed = startPr;
}

void Button::setButtonEndPressed(unsigned long endPr) {
  endPressed = endPr;
}

unsigned long long Button::getButtonPressedTime(void) {
  return (endPressed - startPressed);
}

void Button::updateButtonState(void) {
  unsigned long buttonPressedTime = esp_timer_get_time() - getButtonPresStart();
    if(buttonPressedTime <SHORT_PRESS_MIN ) {
    setButtonState(BUTTON_NOT_PRESSED);
  }
  else if(buttonPressedTime >= SHORT_PRESS_MIN && buttonPressedTime <= SHORT_PRESS_MAX) {
    setButtonState(SHORT_PRESSED);
  }
    else if(buttonPressedTime >= MIDDLE_PRESS_MIN && buttonPressedTime <= MIDDLE_PRESS_MAX) {
    setButtonState(MIDDLE_PRESSED);
  }
    else if(buttonPressedTime >= LONG_PRESS_MIN ) {
    setButtonState(LONG_PRESSED);
  }
  else setButtonState(BUTTON_NOT_PRESSED);
}

void Button::updatePressTime(void) {
  unsigned long buttonPressedTime = getButtonPressedTime();
    if(buttonPressedTime <SHORT_PRESS_MIN ) {
    setButtonState(BUTTON_NOT_PRESSED);
  }
  else if(buttonPressedTime >= SHORT_PRESS_MIN && buttonPressedTime <= SHORT_PRESS_MAX) {
    setButtonState(SHORT_PRESSED);
  }
    else if(buttonPressedTime >= MIDDLE_PRESS_MIN && buttonPressedTime <= MIDDLE_PRESS_MAX) {
    setButtonState(MIDDLE_PRESSED);
  }
    else if(buttonPressedTime >= LONG_PRESS_MIN ) {
    setButtonState(LONG_PRESSED);
  }
  else setButtonState(BUTTON_NOT_PRESSED);
}
