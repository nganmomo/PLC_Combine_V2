#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>
#include <define.h>
//#define DEBUG
#define SETUPSTATE 0
extern char mssid[20];
extern char mpass[20];
extern char MQTINTERVAL[5][4];  
extern byte SerialMode;

extern void    rwswiches(int wonly);
extern void    runplc(uint32_t realtimeloop);
extern void    initplc();
extern byte    OnOffdevice[63];         //check table
extern byte    Deviceinit;
struct boxstate
{
byte DeviceState;
byte Linknum;
};
extern boxstate BoxState[6][40];
//timeclock//
extern byte clkid[17];
extern int32_t setbt[17];
extern int32_t setet[17];
extern int32_t setbd[17];
extern int32_t setem[17];
extern int32_t setbm[17];
extern int32_t seted[17];
extern int32_t setby[17];
extern int32_t setey[17];
extern int32_t setbdoy[17];
extern int32_t setedoy[17];
extern byte cycle[17];
extern int UTC;
extern int32_t currenttime;
extern int32_t currentdateofyear;
//netanalysis
extern byte netnum[6][40];
extern void updatestate();
extern void netanalysis();
extern byte GetlastScan();
extern byte digstate[244];
extern byte anastate[244];
//plc submain//
extern void loaddefaultvalue();
extern byte asxii2int(char *payload,byte offset); 
extern int numchartowrite;
extern char keyvalue[20];
extern char variable[1600];
extern byte Rtimersetflag[9];
extern size_t   buf_len;  
extern int8_t   mqttrun;
extern void receivedplcdata();    
extern void receivedplc(int eedata,int maxlen,char rw,int offset);     
extern byte cellkeyboard(byte work);   
extern void switchsimulate(byte stateonly);    
extern void systemsetup(); 
extern void receivedplcTable();    
extern byte getdata100(int gx,int gy,char* rebuf,int length,char *pt,char endsign=0);

extern void saveint16(char *variable,uint16_t (*dataz)[40],byte start,byte end);
extern void readinput(uint32_t realtimeloop,byte Lasty);
extern void updateinstate(uint32_t realtimeloop,byte lasty);
extern void ioinit();
///////MQTT//////////
extern void connectToMqtt();
extern void clientsetup(byte mqtt);
extern char MYTOPIC[5][64];  // = "mytopic2";
extern void disconnectmqtt();
extern  const char* ssid;
extern  const char* password;
//EEPROM
extern void eepromread(int offset,uint16_t (*dataz)[40],byte type);
extern void eepromwrite(int offset,uint16_t (*dataz)[40],byte type);
extern void eewClear(int offset,char keyc,int length);
extern void eewbyte(int offset,char* keyc,int length);
extern void eerbyte(int offset,char* keyc,int length); //add end sign later
extern void eewpassid(int offset,char* iddata,char* pwdata);
extern void eerpassid(int offset,char* iddata,char* pwdata);
extern void eewint16(int offset,int16_t data);
extern int16_t eerint16(int offset);
///////////////////
//for phone
extern String displaymess;
//for hardware//
extern char phonebuf[16];
extern byte Pinout[9];
extern byte Pinin[9];
extern byte analogpin[5];
extern byte analogpout[5];
extern byte inreadstate[9];
extern byte outstatus[9];
extern byte SerachFlag;
extern byte buttonnum;          //xhttp control button
extern byte buttonmode;
extern byte Rbuttonnum;          //xhttp control button
extern byte Rbuttonmode;
//MQTT
extern char EPHMQTT[2];
extern char EPLCMQTT[2];
extern byte getdata(byte gx,byte gy,char* rebuf);
extern void clientTX(byte topic);
extern byte clientTXStatus[4];
extern void initmattdate();

extern char RxAnaValue[4][9][4];   
extern byte RxIOpinit[4][9]; 
extern char TxAnaValue[4][8][4];   
extern byte TxIOpinit[4][8];

extern byte RelayOnOffstate[16];
extern int  rxpin;
extern byte MqttDisplay[16];
extern byte INKeyreached;
extern byte PhoneKeyIn;
extern byte mqttcellinstate;
extern byte mqttconnected;
extern byte wificonnected;
extern byte mqtten;
extern byte checkmqtt();
////////////////////
extern uint16_t dataz0[6][40];//0  sign 16
extern uint16_t dataz1[6][40];//1  id    32
extern uint16_t dataz2[6][40];//2  link  32
extern uint16_t dataz3[6][40];//3  line  16
extern uint16_t dataz4[6][40];//4  set   32
extern char   dataz100g7[100];//4  set   32
extern uint32_t timer[2][8];
extern byte beforestate[16];  //link cycle for 16 link 
extern unsigned long counter[16];
extern int16_t d2abuf[9];
extern byte    d2aupedge[9];
extern byte    d2adownedge[9];
extern byte    deboun44[9];
///run mode/////////////
extern int8_t  Runmode;
//for phone timeout
extern char phonepw[16];
extern char Storephonepw[16];
extern char Storeeditpw[16];
extern byte ctlpermit;
extern byte adminpermit;
//for phone timer
extern unsigned long phonestartTime;
extern unsigned long phoneelapsedTime;
extern unsigned long phonetimeset;
//clocktimer
void setuptimeclock(byte load);
//void inserttimeclock();

extern void anykey(byte a);
extern char encrytext[12];
extern char comparetext[12];
extern uint64_t chipId;
extern void encrypt(char* encrytext,uint64_t chipId);
extern void brokersetup(int port);
extern void brokerloop();
/*
void anykey(int test,int point1,int point2);
Serial.println("anykey");  
while (!Serial.available());
Serial.read();
*/
//void brokersetup(int port);
//void brokerloop();