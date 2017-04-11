/**
  ******************************************************************************
  * @file    PoseApp/Src/main.c 
  * @author  AK
  * @version V1.0.0
  * @date    09-04-2017
  * @brief   1.USART2���Ӻ�ESP8266_01WIFIģ�飬���������������״̬   
  *          2.ʵ��USB���⴮��(VCP)��ָ��ַ����԰��ӽ������ߵ���
  *          3.������̬��ͨ��wifiģ���ϴ�����
  *          4.�ü򵥵�PID��������ƽ��
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





