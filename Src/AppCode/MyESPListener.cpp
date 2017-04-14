#include "MyESPListener.h"
#include "ESP8266.h"


void MyESPListener::onDataReive_IT(int connectionID, char* data, uint8_t len){

}

void MyESPListener::onReady(){//boot/reboot signal
    char* date = "chip ready\r\n\0";
    usbPort->sendDate(date,strlen(date));
    mESP8266->connectWIFI("ziroom501","4001001111");
}

void MyESPListener::onWifiConnectOK(){
    char* date = "connect wifi ESP_3C981B ok\r\n\0";
    usbPort->sendDate(date,strlen(date));
    mESP8266->startConnection(0, "TCP", "192.168.1.104", "8888", NULL);
    //enable TTmode?
}

void MyESPListener::onWifiDisConnection(){
    
}

void MyESPListener::onServerOn(){
     
}
    
void MyESPListener::onConnectionOk(uint8_t connectionID){
    char* date = "chip connect ok\r\n\0";
    //usbPort->sendDate(date,strlen(date));
    //send data
    //int i = 50000;
    //while(i > 0)i--;
    mESP8266->setPreSend(0, 5);
}

void MyESPListener::onConnectionFail(uint8_t connectionID){
    //reconnect
    mESP8266->startConnection(0, "TCP", "192.168.1.104", "8888", NULL);
}

void MyESPListener::onConnectonClosed(uint8_t connectionID){

}

void MyESPListener::onPreSendOk(){
    
    mESP8266->sendDate("hhh\r\n", 5);
}

void MyESPListener::onPreSendFail(){
    mESP8266->startConnection(0, "TCP", "192.168.1.104", "8888", NULL);
}

void MyESPListener::onSendDataOk(uint8_t connectonID){
   
    mESP8266->setPreSend(connectonID, 5);
}


void MyESPListener::onEnableTTModeOk(){

}