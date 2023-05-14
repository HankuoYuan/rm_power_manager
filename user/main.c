#include "main.h"

void initialize_task(void *parameters) {
    (void) parameters;
    taskENTER_CRITICAL();
    rtc_config();
    error_check();
    filter_config();
    gpio_config();
    dma_config();
    ramecc_config();
    usart1_config();
    usart2_config();
//    iwdg_config();
    adc_config();
    dac_config();
    spi3_config();
    calibrate_params_config();
    calibrate_referee_config();

    BaseType_t xReturned = xTaskCreate((TaskFunction_t) protect_task,
                                       (const char *) "ProtectTask",
                                       (configSTACK_DEPTH_TYPE) 1024,
                                       (void *) NULL,
                                       (UBaseType_t) 3,
                                       (TaskHandle_t *) NULL);
    if (xReturned != pdPASS)
        error_handler(__FILE__, __LINE__);

    xReturned = xTaskCreate((TaskFunction_t) fsm_task,
                            (const char *) "FSMTask",
                            (configSTACK_DEPTH_TYPE) 1024,
                            (void *) NULL,
                            (UBaseType_t) 2,
                            (TaskHandle_t *) &fsm_task_handler);
    if (xReturned != pdPASS)
        error_handler(__FILE__, __LINE__);

    xReturned = xTaskCreate((TaskFunction_t) interrupt_handle_task,
                            (const char *) "IntTask",
                            (configSTACK_DEPTH_TYPE) 1024,
                            (void *) NULL,
                            (UBaseType_t) 4,
                            (TaskHandle_t *) NULL);
    if (xReturned != pdPASS)
        error_handler(__FILE__, __LINE__);

    taskEXIT_CRITICAL();
    vTaskDelete(NULL);
}

int main(void) {
    system_config();

    BaseType_t xReturned = xTaskCreate((TaskFunction_t) initialize_task,
                                       (const char *) "InitTask",
                                       (configSTACK_DEPTH_TYPE) 2048,
                                       (void *) NULL,
                                       (UBaseType_t) 1,
                                       (TaskHandle_t *) NULL);
    if (xReturned != pdPASS)
        error_handler(__FILE__, __LINE__);

    freertos_is_running();
    vTaskStartScheduler();
    while (1);
}
