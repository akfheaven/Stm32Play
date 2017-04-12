#include "main.h"
#include "Application.h"
#include "SerialPort.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"


static UART_HandleTypeDef initUART_Handle;//for init purpose
static USBD_HandleTypeDef initUsbDeviceFS;

map<SerialPort::Type, SerialPort*> *SerialPort::PortPool = NULL;
uint16_t SerialPort::maxDateLen = 500;

SerialPort::SerialPort(){
    ListenerPool = NULL;
    mRxBuffer = new uint8_t[maxDateLen];
    mTxBuffer = new uint8_t[maxDateLen];
    mUartHandle = initUART_Handle;
    mUsbDeviceFS = initUsbDeviceFS;
}


SerialPort::~SerialPort(){
    delete[] mRxBuffer;
    delete[] mTxBuffer;
    delete[] ListenerPool;
}



SerialPort* SerialPort::getSerialPort(SerialPort::Type PortType, uint32_t bauteRate){

    EBOOL isGetOk = TRUE;
    if(PortPool != NULL && (*PortPool)[PortType] != NULL){
        SerialPort* curport = (*PortPool)[PortType];
        curport->setBauteRate(bauteRate);
        return curport;
    }

    SerialPort* portToMake = new SerialPort();
    
    
    switch (PortType) {

        case SerialPort::TUSART1: {

            break;
        }


        case SerialPort::TUSART2: {
            /*##-1- Configure the UART peripheral ######################################*/
            /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
            /* UART2 configured as follow:
            - Word Length = 8 Bits
            - Stop Bit = One Stop bit
            - Parity = None
            - BaudRate = 115200 baud
            - Hardware flow control disabled (RTS and CTS signals) */
           
            portToMake->mUartHandle.Instance = USARTx;
            portToMake->mUartHandle.Init.BaudRate = bauteRate;
            portToMake->mUartHandle.Init.WordLength = UART_WORDLENGTH_8B;
            portToMake->mUartHandle.Init.StopBits = UART_STOPBITS_1;
            portToMake->mUartHandle.Init.Parity = UART_PARITY_NONE;
            portToMake->mUartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
            portToMake->mUartHandle.Init.Mode = UART_MODE_TX_RX;
            portToMake->mUartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

            if (HAL_UART_Init(&(portToMake->mUartHandle)) != HAL_OK)
            {
                    //Error_Handler();
                    isGetOk = FALSE;
            }

            __HAL_UART_ENABLE_IT(&(portToMake->mUartHandle), UART_IT_IDLE);
       
            if (HAL_UART_Receive_DMA(&(portToMake->mUartHandle), (uint8_t *)(portToMake->mRxBuffer), maxDateLen) != HAL_OK)
            {
                    //Error_Handler();
            }

            portToMake->mType = TUSART2;

            break;
        }
        case TUSBVCP:{

            /* Initialize all configured peripherals */
            /* GPIO Ports Clock Enable */
            __HAL_RCC_GPIOH_CLK_ENABLE();
            __HAL_RCC_GPIOA_CLK_ENABLE();
          

            MX_USB_DEVICE_Init();

           portToMake->mType = TUSBVCP;
           break;
        }


      

    }


    if (isGetOk == FALSE);//TODO

    if (PortPool == NULL) {
         PortPool = new map<SerialPort::Type, SerialPort*>();
    }

    (*PortPool)[PortType] = portToMake;
    return portToMake;
}
        

SerialPort::State SerialPort::setBauteRate(uint32_t rate){
    return SerialPort::BUSSY;
}
    
uint32_t SerialPort::getBauteTate(){
    return 1;
}

SerialPort::State SerialPort::sendDate(char* date, uint8_t len){
    if(len > maxDateLen)return FAIL;
    memcpy(mTxBuffer, date, len);
    if(mType != TUSBVCP )
    {
      if(HAL_UART_Transmit_DMA(&mUartHandle, mTxBuffer, len)!= HAL_OK){
        //Error_Handler();
        return FAIL;
      }
    }else if(CDC_Transmit_FS(mTxBuffer, len) != HAL_OK){
        return FAIL;
    }
    return OK;
}

void SerialPort::addListener(SerialPortListener *Listener){
    if(ListenerPool == NULL){
        ListenerPool = new vector<SerialPortListener*>();
    }

    ListenerPool->push_back(Listener);
}

SerialPort::State SerialPort::removeListener(SerialPortListener *Listener){
    return SerialPort::BUSSY; 
}

SerialPort::State SerialPort::rebootSerial(SerialPort* serial){
    return SerialPort::BUSSY;
}




void SerialPort::IRQHandle(uint8_t isDMA, uint8_t isTx){

    if(PortPool == NULL)return ;
    map<SerialPort::Type, SerialPort*>::iterator it = PortPool->begin();

    while(it != PortPool->end()){
        SerialPort *curPort = it->second;
        if(curPort->mType == TUSBVCP){ it++; continue;}
        
        UART_HandleTypeDef* uartHanle = &(curPort->mUartHandle);
        
        if(isDMA == 0){
            uint32_t temp;
            if((__HAL_UART_GET_FLAG(uartHanle,UART_FLAG_IDLE) != RESET))  
            {   
              __HAL_UART_CLEAR_IDLEFLAG(uartHanle);  
              HAL_UART_DMAStop(uartHanle);  
              temp = uartHanle->hdmarx->Instance->NDTR;  
              curPort->readLen = maxDateLen - temp;
              HAL_UART_Receive_DMA(uartHanle, curPort->mRxBuffer,maxDateLen);  
                
              if(curPort->ListenerPool!=NULL){
                vector<SerialPortListener*>::iterator sit = curPort->ListenerPool->begin();
                while(sit != curPort->ListenerPool->end()){
                    SerialPortListener* curListener = *sit;
                    curListener->onDateRecive_IT(curPort, (char*)curPort->mRxBuffer, curPort->readLen);
                    sit++;
                }
                
              }
              
            }

            HAL_UART_IRQHandler(uartHanle);
            
        }else if(isTx == 1){
            HAL_DMA_IRQHandler(uartHanle->hdmatx);
        }else{//Rx
            HAL_DMA_IRQHandler(uartHanle->hdmarx);
        }

        it++;
    }
    

}


void SerialPort::USBDateInHandle(char* date,  int len){
    if(PortPool == NULL)return ;
    SerialPort* port = (*PortPool)[TUSBVCP];
    if(port== NULL || port->ListenerPool == NULL)return ;
    for(int i = 0; i < port->ListenerPool->size();i++){
        SerialPortListener *it = (*(port->ListenerPool))[i];
        it->onDateRecive_IT(port, (char*)date, len);

    }  
}


