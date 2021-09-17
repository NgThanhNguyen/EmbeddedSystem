#include <stdio.h>
#include <time.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/timers.h"

void callback (xTimerHandle pxTimer);

int PERIOD_1 = 200;
int PERIOD_2 = 300;
int repeat1 = 10;
int repeat2 = 5;
xTimerHandle ahihi = NULL;
xTimerHandle ahaha = NULL;

void callback (xTimerHandle pxTimer){
    int timer_ID = (int)pvTimerGetTimerID(pxTimer);
    if(timer_ID == 1){
        static int count1 = 0;
        if(count1 < repeat1){
            printf("Timer 1: Ahihi at %d s\n", (int) clock()/1000);
            xTimerReset(ahihi,0);
            count1++;
        }
    }
    else{
        static int count1 = 0;
        if(count1 < repeat2){
            printf("Timer 2: Ahaha at %d s\n", (int) clock()/1000);
            xTimerReset(ahaha,0);
            count1++;
        }
    }
}

void app_main(void){
    ahihi = xTimerCreate("Timer1", PERIOD_1, pdFALSE, (void*)1, callback);
    ahaha = xTimerCreate("Timer2", PERIOD_2, pdFALSE, (void*)2, callback);
    xTimerStart(ahihi,0);
    xTimerStart(ahaha,0);
}
