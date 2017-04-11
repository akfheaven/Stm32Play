#ifndef MYAPP_H
#define MYAPP_H
#include "../Application.h"
#include "MySPortListener.h"

class MyApp : private Application{
public:
  MyApp();

//user code
private :
  SerialPort* serialPortU2;
  SerialPort* serialPortUSB;
  MySPortListener* mySPortU2Listener;
  


//just implement and don't change
private:
  void OnSysStart();
  void onSysTick_IT(); 
  void onSysUpdate(uint32_t detalTimeInUs);
  void onUserBtnDown();
  void onUserBtnUp();
};

#endif  //MYAPP_H
