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
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/queue.h"

const TickType_t xDelay1000ms = pdMS_TO_TICKS (1000);
const TickType_t xDelay500ms = pdMS_TO_TICKS (500);
QueueHandle_t q;

struct Data {
  int DataID;
  int DataValue;
};

void ReceptionTask(void *pvParameter)
{
  struct Data* Request;
  Request = (struct Data*) pvParameter;
  if(q == NULL) {
    printf("Queue is not created yet");
    return;
  }
  else {
    while(1)
    {
      printf("Value sent to queue:\n");
      printf("DataID: %d",Request->DataID);
      printf("DataValue: %d",Request->DataValue);
      xQueueSend(q, (struct Data*)&Request,(TickType_t) 10);
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }
  vTaskDelete (NULL) ;
}

void FunctionTask(void *pvParameter) {
  struct Data* Receive;
  while (1)
  {
    if(q != NULL) {
      if(uxQueueMessagesWaiting(q)) {
        if(xQueueReceive(q,&Receive,(TickType_t) 10)) {
          printf("DataID: %d",Receive->DataID);
          printf("DataValue: %d",Receive->DataValue);
        }
      }
    }
    else {
      printf("Queue is empty");
      return;
    }
  }
}

struct Data* a = {2,10000};
struct Data* b = {2,20000};
struct Data* c = {3,30000}; 

void app_main(void)
{
  q = xQueueCreate(20,sizeof(struct Data));
  if(q != NULL) {
    printf("Queue is created\n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    printf("Receive request: \n");
    xTaskCreate(ReceptionTask,"Request 1",10000,(void*)a,0,NULL);
    xTaskCreate(ReceptionTask,"Request 2",10000,(void*)b,0,NULL);
    xTaskCreate(ReceptionTask,"Request 3",10000,(void*)c,0,NULL);
    xTaskCreate(FunctionTask,"Function task",10000,NULL,0,NULL);
  } 
}





