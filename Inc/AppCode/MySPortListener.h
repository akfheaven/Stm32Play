#ifndef MYSPORTLISTENER_H
#define MYSPORTLISTENER_H
#include "../SerialPort.h"

class MySPortListener : public SerialPortListener{
private:
  SerialPort* mu2;
  SerialPort* musb;
public:

  MySPortListener(SerialPort* u2, SerialPort* usb);
  
  void onDateRecive_IT(SerialPort * reciver, char* date , uint16_t len);

  void onDateSendCplt_IT();

  void onSeralPortError();
};
#endif  //MYSPORTLISTENER_H
