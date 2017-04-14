#include "MySPortListener.h"

MySPortListener::MySPortListener(SerialPort* u2, SerialPort* usb){
  mu2 = u2;
  musb = usb;
}

void MySPortListener::onDateRecive_IT(SerialPort* reciver, char* date , uint16_t len){
  SerialPort::Type type = reciver->mType; 
  if(type == SerialPort::TUSBVCP){//usb ½ÓÊÕµ½
    if(mu2 == NULL)return ;
    mu2->sendDate(date, len);
  }else if(type == SerialPort::TUSART2){
    if(musb == NULL)return ;
    //char tex[300];
    //sprintf(tex, "%s *** %d\r\n\0", date, len);
    musb->sendDate(date, len);
    //musb->sendDate(tex, strlen(tex));
  }
}

void MySPortListener::onDateSendCplt_IT(){
    
}

void MySPortListener::onSeralPortError(){}