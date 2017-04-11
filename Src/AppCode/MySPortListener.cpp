#include "MySPortListener.h"

MySPortListener::MySPortListener(){

}

void MySPortListener::onDateRecive_IT(SerialPort* reciver, char* date , uint16_t len){
    reciver->sendDate(date, len);
}

void MySPortListener::onDateSendCplt_IT(){
    
}

void MySPortListener::onSeralPortError(){}