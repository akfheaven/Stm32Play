#include "MyApp.h"
#include "ESP8266.h"
#include "MyESPListener.h"
uint8_t isFirst =1;
MyApp::MyApp()
:serialPortU2(NULL)
,mySPortU2Listener(NULL)
{
}

 
void MyApp::OnSysStart(){
    
    configSystick(1000);
    
    serialPortUSB  = SerialPort::getSerialPort(SerialPort::TUSBVCP, 115200);
   

    serialPortU2  = SerialPort::getSerialPort(SerialPort::TUSART2, 115200);
  
    mySPortU2Listener = new MySPortListener(serialPortU2, serialPortUSB);
    mySPortUsbListener = new MySPortListener(serialPortU2, serialPortUSB);
     
    serialPortU2->addListener(mySPortU2Listener);
    serialPortUSB->addListener(mySPortUsbListener);

    MyESPListener* espListener = new MyESPListener(serialPortUSB);
    ESP8266* esp8266 = new ESP8266(SerialPort::TUSART2, espListener);
    esp8266->start();
}


void MyApp::onSysUpdate(uint32_t detalTimeInUs){
    
    /*char* date = new char[100];
    //detalTimeInUs = 100;
    sprintf(date, "%d\n\0", detalTimeInUs);
    serialPortU2->sendDate(date, strlen(date));
    delete[] date;
    HAL_Delay(1000);*/
}


void MyApp::onSysTick_IT(){
    
}


void MyApp::onUserBtnDown(){
    
    char* cmd = "AT+CIPSTART=\"TCP\",\"192.168.1.104\",8888\r\n\0";
    if(isFirst == 1){
      isFirst = 0;
      serialPortU2->sendDate(cmd,strlen(cmd));
      return ;
    }
    sprintf(cmdTemp, "AT+CIPSEND=%d\r\n\0", 5);
    serialPortU2->sendDate(cmdTemp,strlen(cmdTemp));
    //char* date = "BtnDown";
    //serialPortUSB->sendDate(date, strlen(date));
    //HAL_Delay(20);
}
void MyApp::onUserBtnUp(){
    char* date = "BtnUp";
    //serialPortU2->sendDate(date, strlen(date));
    //HAL_Delay(20);
}
