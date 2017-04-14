#ifndef MYESPLISTENER_H
#define MYESPLISTENER_H

#include "ESPListener.h"
#include "SerialPort.h"

class MyESPListener : public ESPListener{
private:
    SerialPort* usbPort;

public:
    MyESPListener(SerialPort* usbLogPort):usbPort(usbLogPort){}
    
    void onDataReive_IT(int connectionID, char* data, uint8_t len);

    void onReady();

    void onWifiConnectOK();

    void onWifiDisConnection();

    void onServerOn();

    void onConnectionFail(uint8_t connectionID);
    
    void onConnectionOk(uint8_t connectionID);

    void onConnectonClosed(uint8_t connectionID);

    void onPreSendOk();

    void onPreSendFail();

    void onSendDataOk(uint8_t connectonID);

    void onESPMiss(){}//?

    void onEnableTTModeOk();

};

#endif  //MYESPLISTENER_H
