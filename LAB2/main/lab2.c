/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BLINK_GPIO 17
#define BUTTON_GPIO 18
const TickType_t xDelay1000ms = pdMS_TO_TICKS (1000) ;
bool temp = false;

void ATaskFunction(void *pvParameter)
{
  for(;;)
  {
    printf("Name: Nguyen Thanh Nguyen\n");
    printf("Student ID: 1852618\n");
    //vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelay(xDelay1000ms);
    // ...
  }
  vTaskDelete (NULL) ;
}

void ATaskblink(void *pvParameter)
{
  {
         /*gpio_set_level(BLINK_GPIO, 1);
     vTaskDelay(1000 / portTICK_PERIOD_MS);
          gpio_set_level(BLINK_GPIO, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);*/
    //vTaskDelay(1000 / portTICK_PERIOD_MS);
    // ...
  }
  vTaskDelete (NULL) ;
}


void ATaskbutton(void *pvParameter)
{
  for(;;)
  {
    if(gpio_get_level(BUTTON_GPIO) == 0 && temp == true) {
      if(gpio_get_level(BUTTON_GPIO) == 0){
        gpio_set_level(BLINK_GPIO, 1);
        printf("\n\nespppppppp\n\n");
        temp = false;
      }
    }
    else if(gpio_get_level(BUTTON_GPIO) == 1 && temp == false){
      if(gpio_get_level(BUTTON_GPIO) == 1) {
        gpio_set_level(BLINK_GPIO, 0);
        temp = true;
      }
    }
      //vTaskDelay(100 / portTICK_PERIOD_MS);
      vTaskDelay(xDelay1000ms);
    // ...
  }
  vTaskDelete (NULL);
  
}


void app_main(void)
{
    static const char * pcTextForTask1 = " Task 1 is running \r\n";
    static const char * pcTextForTask2 = " Task 2 is running \r\n";
    
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_pad_select_gpio(BUTTON_GPIO);

    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);

    gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLUP_ONLY);



    xTaskCreate(ATaskFunction,"name_task",1024,NULL,1,NULL);

    xTaskCreate(ATaskblink,"blink_task",1024,NULL,1,NULL);

    xTaskCreate(ATaskbutton,"button_task",1024,NULL,1,NULL);

    
}





