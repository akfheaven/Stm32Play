#include "ESPListener.h"


//implement serialPortListener virtual 
void ESPListener::onDateRecive_IT(SerialPort *reciver, char* date , uint16_t len){
  
    if(isFindStr("ready",5, date,len))
    {
        setListenState(LNONE);
        onReady();
        return ;
    }

    LSITENSTATE preState = mCurListenState;    
    switch (mCurListenState){
        case LWIFIOK:
            if(isFindStr("OK",2, date, len) || isFindStr("GOT IP",6, date, len)){
                onWifiConnectOK();
                if(mCurListenState == preState){
                  setListenState(LNONE);
                }
            } 
           
            break;  

        case LCONNOK:
            if((isFindStr("CONNEC",6, date, len) && isFindStr("OK",2, date, len)) || (isFindStr("CONNECTED",9, date, len))){
                onConnectionOk(0);
                if(mCurListenState == preState){
                  setListenState(LNONE);
                }
            }else{
                onConnectionFail(0);
            }
            break;

        case LPRESEND:
            if(isFindStr("OK",2, date, len)){
                onPreSendOk();
                if(mCurListenState == preState){
                  setListenState(LNONE);
                }
            }else if(isFindStr("ERROR", 2, date, len)){
                onPreSendFail();
            } 
            break;

        case LSENDOK:
            if(isFindStr("OK",2, date, len)){
                onSendDataOk(0);
                if(mCurListenState == preState){
                  setListenState(LNONE);
                }
            } 
            break;
        
    }


   
    
}


EBOOL ESPListener::isFindStr(char* str, uint8_t strLen, char* data, uint8_t dataLen){
    if(strLen > dataLen )return FALSE;
    int i = 0, j = 0;
    while(1){
        if(data[i+j] == str[j]){
            j++;
            if(j == strLen)return TRUE;
            else if(i+j == dataLen)return FALSE;
        }else{
            i ++;
            j = 0;
        }
        if(i == dataLen)return FALSE;
    }
    return FALSE;
}
