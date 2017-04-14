#ifndef ESPLISTENER_H
#define ESPLISTENER_H

#include "Application.h"
#include "SerialPort.h"

class ESP8266;
class ESPListener : public SerialPortListener{
public:
    enum LSITENSTATE{LNONE,LWIFIOK,LDISWIFI,LSERVERON,LCONNOK, LCONNCLOSE, LPRESEND, LSENDOK};
protected:
    ESP8266* mESP8266;

private:
    LSITENSTATE  mCurListenState;

    
private:
EBOOL isFindStr(char* str, uint8_t strLen, char* data, uint8_t dataLen);



public:
    //to be impelemnted
    virtual void onDataReive_IT(int connectionID, char* data, uint8_t len) = 0;

    virtual void onReady() = 0;

    virtual void onWifiConnectOK() = 0;

    virtual void onWifiDisConnection() = 0;

    virtual void onServerOn() = 0;
        
    virtual void onConnectionOk(uint8_t connectionID) = 0;
    
    virtual void onConnectionFail(uint8_t connectionID) = 0;

    virtual void onConnectonClosed(uint8_t connectionID) = 0;

    virtual void onPreSendOk() = 0;

    virtual void onPreSendFail() = 0;

    virtual void onSendDataOk(uint8_t connectonID) = 0;

    virtual void onESPMiss() = 0;//?

    virtual void onEnableTTModeOk() = 0;


    //implement serialPortListener virtual 
    void onDateRecive_IT(SerialPort *reciver, char* date , uint16_t len);

    void onDateSendCplt_IT();

    void onSeralPortError();

    
    //self function call by esp
    ESPListener():mESP8266(NULL),mCurListenState(LNONE){}
    void setESP8266(ESP8266* esp8266){ mESP8266 = esp8266;}
    void setListenState(LSITENSTATE pState){mCurListenState = pState;}

};

#endif  //ESPLISTENER_H
