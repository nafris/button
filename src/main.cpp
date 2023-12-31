#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <button.h>
#include "esp_timer.h"
#include "driver/gpio.h"

//Button poga(GPIO_NUM_9);
Button poga((gpio_num_t)9);
extern "C"{
    void app_main();
}
void vButtonTaskCode(void * pVparameters)
{
    printf("Button task started \n");
    poga.buttonState = BUTTON_NOT_PRESSED;
    static uint8_t newState = 0, lastState = 0;
    if(poga.isButtonPressed()) {
        lastState = newState = PRESSED;
    }
    else {
        lastState = newState = RELEASED;
    }
    vTaskDelay((TickType_t)2);
    while(1) {
        if(poga.isButtonPressed()) {
            vTaskDelay((TickType_t)2);//debounce..change to task delay !
            if (poga.isButtonPressed() ) {
                if (lastState == RELEASED) {
                    lastState = PRESSED;
                    poga.setButtonStartPressed(esp_timer_get_time());
                    poga.setButtonState(BUTTON_JUST_PRESSED);
                }
                else {
                    poga.updateButtonState();
                }
            }
        }
        else {
            vTaskDelay((TickType_t)2);
            if(!(poga.isButtonPressed())) {
                if(lastState == PRESSED) {
                    lastState = RELEASED;
                    poga.setButtonEndPressed(esp_timer_get_time());
                    switch (poga.buttonState) {
                        case SHORT_PRESSED:
                            printf("Button short pressed \n");
                            break;
                        case MIDDLE_PRESSED:
                           printf("Button middle pressed \n");
                            break;
                        case LONG_PRESSED:
                           printf("Button long pressed \n");
                            break;
                        default:
                            break;
                    }
                }
                else if (poga.getButtonState() != BUTTON_NOT_PRESSED){
                    vTaskDelay((TickType_t)1);
                    poga.setButtonState(BUTTON_NOT_PRESSED);
                }
            }
        }
    }
}
void CreateButtonTask(void){
    static uint8_t ucParameterToPass;
    TaskHandle_t handle_ButtonTask = NULL;
    xTaskCreate(vButtonTaskCode, "ButtonTask", 2048, &ucParameterToPass, tskIDLE_PRIORITY, &handle_ButtonTask);
    configASSERT(handle_ButtonTask);
}


void app_main() {
    CreateButtonTask();
    while(1){
        vTaskDelay(100);
        //printf("New line \n");
    }
}