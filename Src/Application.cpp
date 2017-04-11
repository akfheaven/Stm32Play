#include "Application.h"

extern UART_HandleTypeDef UartHandle;
//----- object life cycle functions ------------------------------------------//

Application* Application::instance = NULL;

Application::Application(){
    if(instance == NULL){
        instance = this;
        loopFlag = 1;
        tickTime = 0;
        btnState = BTN_UP;
    }//else error?
}

void Application::run(){

    if(instance == NULL){
        loopFlag = 0;
        return ;
    }

    
    initHardWare();

    instance->OnSysStart();
    
    

    while(loopFlag){
        
        uint32_t temp = tickTime;
        tickTime = 0;
        instance->onSysUpdate(temp);
        
        if(btnState == BTN_UP && BSP_PB_GetState(BUTTON_KEY) == SET){
            onUserBtnDown();
            btnState = BTN_DOWN;
        }else if(btnState == BTN_DOWN && BSP_PB_GetState(BUTTON_KEY) == RESET){
            onUserBtnUp();
            btnState = BTN_UP;
        }
    }
}

void Application::SysTickHandle(){
    onSysTick_IT();
    tickTime += curTimeIntv;
}


//----- user interface functions ---------------------------------------------//
Application* Application::getInstance(){
    return instance;
}

void Application::configSystick(uint32_t frequency){
    if(frequency < 1 || frequency > 1000000)return ;
    SystemCoreClock = HAL_RCC_GetHCLKFreq();
    SysTick_Config(SystemCoreClock / frequency); 
    curTimeIntv = 1000000 / frequency;
}


EBOOL Application::isUserBtnDown(){
    return (BSP_PB_GetState(BUTTON_KEY) == SET ? TRUE: FALSE);
}

EBOOL Application::isUserBtnUp(){
    return (BSP_PB_GetState(BUTTON_KEY) == RESET ? TRUE: FALSE);
}



//----- priavete helper functions --------------------------------------------//
void Application::initHardWare(){
    /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();
  
  /* Configure LED3, LED4, LED5 and LED6 */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);

  /* Configure the system clock to 168 MHz */
  SystemClock_Config();
    

  /* Configure USER Button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
}


void Application::SystemClock_Config(){
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    //Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    //Error_Handler();
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

