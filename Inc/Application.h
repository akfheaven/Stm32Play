#ifndef APPLICATION_H
#define APPLICATION_H
#include "main.h"

enum EBOOL{FALSE, TRUE};
enum BtnState{BTN_DOWN, BTN_UP};

class Application{
public:

private :
   uint32_t tickTime;
   uint32_t curTimeIntv;
   static Application *instance;
   uint8_t loopFlag;

   BtnState btnState;
   
   
   void initHardWare();
   void SystemClock_Config();
    
public :
    
  Application();
    
  static Application *getInstance();

  void configSystick(uint32_t frequency);


  EBOOL isUserBtnDown();

  EBOOL isUserBtnUp();
    
  // not for user call
  

public:
  void run();
  void SysTickHandle();

protected:
  virtual void onSysTick_IT() = 0; 
  virtual void OnSysStart() = 0;
  virtual void onSysUpdate(uint32_t detalTimeInUs) = 0;
  virtual void onUserBtnDown() = 0;
  virtual void onUserBtnUp() = 0;
};

#endif  //APPLICATION_H
