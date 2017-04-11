/**
  ******************************************************************************
  * @file    PoseApp/Src/main.c 
  * @author  AK
  * @version V1.0.0
  * @date    09-04-2017
  * @brief   1.USART2连接好ESP8266_01WIFI模块，进入待机接受命令状态   
  *          2.实现USB虚拟串口(VCP)的指令分发，对板子进行在线调试
  *          3.计算姿态，通过wifi模块上传数据
  *          4.用简单的PID控制四轴平衡
  */
    
/* Includes ------------------------------------------------------------------*/
#include "AppCode/MyApp.h"
#include "main.h"

/* private var ------------------------------------------------------------------*/
Application* thisApp;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  
    
  /* main logic *********/
  MyApp app;
  thisApp = Application::getInstance();
  if(thisApp != NULL){
    thisApp->run();
  }
  
}





