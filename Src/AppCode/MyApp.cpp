#include "MyApp.h"

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
    char* date = "BtnDown";
    serialPortUSB->sendDate(date, strlen(date));
    HAL_Delay(20);
}
void MyApp::onUserBtnUp(){
    char* date = "BtnUp";
    serialPortU2->sendDate(date, strlen(date));
    HAL_Delay(20);
}
