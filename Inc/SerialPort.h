#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <map>
#include <vector>

#include "main.h"
#include "SerialPortListener.h"
#include "usbd_def.h"


class SerialPort{
public :
    enum Type{TUSART1, TUSART2, TUSBVCP} mType;
    enum State{OK, FAIL, READY, BUSSY, ERROR};
    
protected:

  static map<Type, SerialPort*> *PortPool;
  
  static uint16_t maxDateLen;


  UART_HandleTypeDef mUartHandle;
  USBD_HandleTypeDef mUsbDeviceFS;
  uint8_t *mTxBuffer;
  uint8_t *mRxBuffer;
  uint16_t readLen; 
  
  vector<SerialPortListener*> *ListenerPool;
public:
  SerialPort();
  ~SerialPort();// not allow release directly by user

//device life sycle function
public:
  static void IRQHandle(uint8_t isDMA, uint8_t isTx);
  static void USBDateInHandle(char* date,  int len);
  
//user interface function  
public:
  static SerialPort* getSerialPort(Type PortType, uint32_t bauteRate);
      
  
  State setBauteRate(uint32_t rate);
  
  uint32_t getBauteTate();
  
  State sendDate(char* date, uint8_t len);
  
  void addListener(SerialPortListener *Listener);
  State removeListener(SerialPortListener *Listener);
  
  State rebootSerial(SerialPort* serial);


private:
    void OnInitError();

    
};

#endif  //SERIALPORT_H
