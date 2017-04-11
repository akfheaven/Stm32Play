#ifndef MYSPORTLISTENER_H
#define MYSPORTLISTENER_H
#include "../SerialPort.h"

class MySPortListener : public SerialPortListener{
public:
  MySPortListener();
  void onDateRecive_IT(SerialPort * reciver, char* date , uint16_t len);

  void onDateSendCplt_IT();

  void onSeralPortError();
};
#endif  //MYSPORTLISTENER_H
