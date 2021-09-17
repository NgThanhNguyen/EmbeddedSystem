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
#include "freertos/FreeRTOSConfig.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BUTTON_GPIO 18
const TickType_t xDelay1000ms = pdMS_TO_TICKS (1000);
const TickType_t xDelay10000ms = pdMS_TO_TICKS (10000);
const TickType_t xDelay5000ms = pdMS_TO_TICKS (5000);
int count = 0;



/*void LED_Create(int gpio_array[]) {
  int Length = sizeof(gpio_array)/sizeof(int);
  for(int i = 0; i < Length; i++) {
    gpio_pad_select_gpio(gpio_array[i]);
    gpio_set_direction(gpio_array[i], GPIO_MODE_OUTPUT);
  }
  printf("Setting LED complete");
}

void Blinking_LED(int GPIO_SELECT) {
  gpio_set_level(GPIO_SELECT,1);
  vTaskDelay(xDelay1000ms);
  gpio_set_level(GPIO_SELECT,0);
}

bool OnClickButton(int button_gpio) {
  gpio_set_direction(button_gpio, GPIO_MODE_INPUT);
  if(gpio_get_level(button_gpio) == 0 && temp == true) {
    if(gpio_get_level(button_gpio) == 0) {
      temp = false;
      return true;
    }
  }
  else if(gpio_get_level(button_gpio) == 1 && temp == false) {
    if(gpio_get_level(button_gpio) == 1) { 
      temp = true;
      return false;
    }
  }
  return false;
}*/

void EventFunction(void *pvParameter)
{
  char* pcTaskName;
  pcTaskName = (char *) pvParameter;
  for(;;)
  {
    for(int i = 0; i < 30; i++) {
      printf("%d | %s",i,pcTaskName);
    }
    //printf("\n%lld\n",esp_timer_get_time());
    vTaskDelay(xDelay10000ms);
  }
  vTaskDelete (NULL);
}

void TaskFunction(void *pvParameter)
{
  char* pcTaskName;
  pcTaskName = (char *) pvParameter;
  for(;;)
  {
    for(int i = 0; i < 10; i++) {
      printf("%d | %s",i,pcTaskName);
    }
    vTaskDelay(xDelay5000ms);
  }
  vTaskDelete (NULL) ;
}

void IdleFunction(void *pvParameter)
{
  char* pcTaskName;
  pcTaskName = (char *) pvParameter;
  for(;;)
  {
    for(int i = 0; i < 10; i++) {
      printf("%d | %s",i,pcTaskName);
    }
    vTaskDelay(xDelay5000ms);
  }
  vTaskDelete (NULL) ;
}

static const char *pcTextforTask1 = "Event\r\n";
static const char *pcTextforTask2 = "Task1 is running\r\n";
static const char *pcTextforTask3 = "Task2 is running\r\n";

void app_main(void)
{ 
  printf("PREMEMTION: %d\n",configUSE_PREEMPTION);
  printf("TIME_SLICING: %d\n",configUSE_TIME_SLICING);

  xTaskCreatePinnedToCore(EventFunction,"Event",10000,(void*)pcTextforTask1,4,NULL,1);

  xTaskCreatePinnedToCore(TaskFunction,"Task 1",10000,(void*)pcTextforTask2,1,NULL,1);

  xTaskCreatePinnedToCore(TaskFunction,"Task 2",10000,(void*)pcTextforTask3,1,NULL,1);

  
}





