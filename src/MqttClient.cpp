#include <plcsvg.h>
#ifndef wssencode
char phonetopic[60];
char mqtt_port_char[6];
char MYTOPIC[5][64];  // = "mytopic2";
char ECODE[40];  
char EnECODE[2];  
char EWSS[2];  
char MQTT_BROKER[64];  
char MPASSWORD[32];  
char MUSERID[32]; 
char MQTINTERVAL[5][4];  
char EPHMQTT[2];
char EPLCMQTT[2];
byte RelayOnOffstate[16];
byte MqttDisplay[16];
int  rxpin;
char lastTxAnaValue[4][8][4];  
byte lastTxIOpinit[4][8];
byte mqttconnected=0;
byte wificonnected=0;
void TxToPhone(byte isinit,int length); 

extern "C" {
	#include "freertos/FreeRTOS.h"
	#include "freertos/timers.h"
}
#include <AsyncMqttClient.h>
//#define WIFI_SSID "ATT3jl8Tns"
//#define WIFI_PASSWORD "6mrk8iyf26vn"
AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer; 
//////////////////
//IPAddress staticIP(192, 168, 1, 186); 
//IPAddress gateway(192, 168, 1, 1);   // Replace this with your gateway IP Addess
//IPAddress subnet(255, 255, 0, 0);  // Replace this with your Subnet Mask
//IPAddress dns(192, 168, 1, 1);  
///////////////////
void connectToWifi() { 
////////////////////
  //if (WiFi.config(staticIP, gateway, subnet, dns, dns) == false) {
  // Serial.println("Configuration failed.");
  //}
//////////////////// 
  WiFi.begin(&mssid[0],&mpass[0]);
}

void connectToMqtt() {
  //if((WiFi.status() != WL_CONNECTED))
  {mqttconnected=0;
  mqttClient.connect();
  }
}

void WiFiEvent(WiFiEvent_t event) {   
    Serial.printf("[WiFi-event] event: %d\n", event);
    switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        if(EPHMQTT[0]=='1'|| EPLCMQTT[0]=='1')
          {connectToMqtt();
          mqtten=1;
          }
        wificonnected=1;
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection");
        xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
        xTimerStart(wifiReconnectTimer, 0);
        break;
    }    
}

void onMqttConnect(bool sessionPresent) { 
  mqttconnected=1;
  Serial.println("Connected to MQTT.");
  char str[100];
  char tstr[100];
  
  str[0]='P';
  str[1]='\0';
  tstr[0]='T';
  tstr[1]='\0';
  
  if(EPLCMQTT[0]=='1')
    strcat(str, ECODE);
  strcat(str, &MYTOPIC[0][0]);
  Serial.print("PLC subscribe:");
  Serial.println(str);
  mqttClient.subscribe(str,0); 
    
  strcat(tstr,phonetopic);
  Serial.print("Phone subscribe:");
  Serial.println(tstr);
  mqttClient.subscribe(tstr,0);   
} 
 
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {  
  Serial.println("Subscribe acknowledged.");
}

void onMqttUnsubscribe(uint16_t packetId) {
}

//callback
//all parameter will not take effect in Mqtt mode
//payload format: start at 0= '*'=on '%'=off, switch no. in position 1-2, value at 3-5, mode at 6, 'p','t','v', for pulse toggle & value 
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
if(topic[0]=='P')
  {byte t,j;
  byte y=0;  
  for(t=0;t<8;t++)    //2D array to 1D array
    {for(j=0;j<4;j++)
      {RxAnaValue[t][j]=payload[y++]-0x30;       
      }
    }  
  for(t=0;t<8;t++)    
    RxIOpinit[t]=payload[y++]-0x30; //and cnange to ascii  
  //Serial.print("payload=");   
  //Serial.println(payload);   
  }
if(topic[0]=='T')   //for phone
  {byte Length;
  if(payload[0]=='D' && payload[1]=='I' && payload[2]=='S'&& payload[3]=='P'&& payload[4]=='L')  
    { variable[4]='t';    //request display
      Length=cellkeyboard();                
      TxToPhone(0,Length+5); 
      payload[0]=='/'; //avoid repeat  
    }             
  else if(payload[0]=='I' && payload[1]=='N' && payload[2]=='I'&& payload[3]=='T'&& payload[4]=='K')
    TxToPhone(2,0);      //requess initial keyboard
  else if(payload[0]=='K' && payload[1]=='E' && payload[2]=='Y'&& payload[3]=='I'&& payload[4]=='N')       
    {Serial.print("payload=");      //normal key in 
    Serial.println(payload);       
    if(len>100) len=100;      
      for(int t=0;t<len;t++)
        {variable[t+4]=payload[t+5];
        }      
      Serial.print("variable1=");
      Serial.println(variable);     
      Length=cellkeyboard();        
      Serial.print("Length=");
      Serial.println(Length);   
      Serial.print("variable2=");
      Serial.println(variable);   
      if(payload[5]=='9')         //verify password
        TxToPhone(0,Length+5); 
      else
        TxToPhone(1,Length+5);    
    }                   
  }  
}
/*
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
*/
void onMqttPublish(uint16_t packetId) {
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}
//setup
void clientsetup(byte mqtt) {
  if(mqtt)
  { Serial.println("mattsetup");    
    eerbyte(MQtopic,phonetopic,32);    
    getdata(0,0,MQTT_BROKER);  
    getdata(1,0,mqtt_port_char);
    getdata(2,0,MUSERID);
    getdata(3,0,MPASSWORD);
    
    getdata(0,1,&MYTOPIC[0][0]);    
    getdata(1,1,ECODE); 
    
    getdata(0,6,EWSS);
    getdata(1,6,EPLCMQTT);
    getdata(2,6,EPHMQTT);       
    getdata(3,6,EnECODE); 
    
    Serial.print("Local topic :"); 
    Serial.println(&MYTOPIC[0][0]);  

    Serial.print("MQTT_BROKER :"); 
    Serial.println(MQTT_BROKER);   
    Serial.print("mqtt_port_char :"); 
    Serial.println(mqtt_port_char); 
    
    Serial.print("ECODE :");  
    Serial.println(ECODE);  
    Serial.print("EnECODE :");  
    Serial.println(EnECODE[0]);   
    
    Serial.print("USERID :");  
    Serial.println(MUSERID);   
    Serial.print("MPASSWORD :");
    Serial.println(MPASSWORD);
    
    Serial.print("EWSS=");  
    Serial.println(EWSS);  
    
    Serial.print("EPLCMQTT=");  
    Serial.println(EPLCMQTT);     
    
    Serial.print("EPHMQATT=");  
    Serial.println(EPHMQTT);     
    int mqtt_port=(mqtt_port_char[0]-0x30)*1000+
    (mqtt_port_char[1]-0x30)*100+
    (mqtt_port_char[2]-0x30)*10+
    (mqtt_port_char[3]-0x30);          
    Serial.println("This PLC assigned=");  
    for(int t=0;t<6;t++)       
      {if(t==5) 
        {Serial.print("This Phone assigned=");  
        Serial.println(phonetopic);  
        }
      else
        {getdata(0,t+1,&MYTOPIC[t][0]);    
        Serial.println(&MYTOPIC[t][0]);         
        }
      }      
////////////////////////////////////////////
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt)); 
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);  
  Serial.print("mqtt_port:");  
  Serial.println(mqtt_port);  
  mqttClient.setServer(MQTT_BROKER, mqtt_port);
  mqttClient.setCredentials(MUSERID,MPASSWORD);
  }
  //connectToMqtt();
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));
  WiFi.onEvent(WiFiEvent);
  connectToWifi();
}

void disconnectmqtt()
{
mqttClient.disconnect();  
}

void TxToPhone(byte isinit,int length) {
char str[100];
//if(EPHMQTT[0]=='1')
str[0]='T';
str[1]='\0';
//strcat(str, ECODE);
//strcat(str, &MYTOPIC[5][0]);    
strcat(str,phonetopic);
if(isinit==0)   //handle keyin   
  {variable[0]='d';variable[1]='i';variable[2]='s';variable[3]='d';
  mqttClient.publish(str,0,false,variable,length-5);   
  }  
if(isinit==1)   //handle keyin   
  {variable[0]='j';variable[1]='o';variable[2]='b';variable[3]='d';
  mqttClient.publish(str,0,false,variable,5);   
  }      
if(isinit==2)   //keyboard setup 
  {int t;
  eerbyte(keychar,&variable[4],350);
  for(t=60;t<350;t++)     
    {if(variable[t]=='*' && variable[t+1]=='$' && variable[t+2]=='^')                         
      break;
    }                  
  variable[0]='i';variable[1]='n';variable[2]='i';variable[3]='R';
  mqttClient.publish(str,0,false,variable,t+5);   
  }    
}

void clientTX(byte topic) {
byte t,j;
byte y=0;
byte txrequired=0;  //if no change bypass tx;
//Serial.print("MYTOPIC=");  
//Serial.println(&MYTOPIC[topic+1][0]);  
char pay_load[41];
if(EPLCMQTT[0]=='1')
  {for(t=0;t<8;t++)    //2D array to 1D array
    {for(j=0;j<4;j++)
      {pay_load[y++]=TxAnaValue[topic][t][j];         
      if(TxAnaValue[topic][t][j]!=lastTxAnaValue[topic][t][j])
        {txrequired=1;
        lastTxAnaValue[topic][t][j]=TxAnaValue[topic][t][j];    
        }
      }
    }  
    for(t=0;t<8;t++)    
    {pay_load[y++]=TxIOpinit[topic][t]; //and cnange to ascii
    if(TxIOpinit[topic][t]!=lastTxIOpinit[topic][t])
      {txrequired=1;
      lastTxIOpinit[topic][t]=TxIOpinit[topic][t];
      }
    }
    if(txrequired==1)      
    { char str[100];
      str[0]='P';
      str[1]='\0';
      for(t=0;t<40;t++)    
      pay_load[t]=pay_load[t]+0x30;
      pay_load[40]='\0';      
      if(EnECODE[0]=='1')
        strcat(str, ECODE);               
      strcat(str, &MYTOPIC[topic+1][0]);
      //Serial.print("str=");
      //Serial.println(str);       
      mqttClient.publish(str,0,false,pay_load,41);                   
    } 
  } 
}
#endif
