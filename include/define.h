#define ipcworld
#define MQTTACTIVE
//#define SWITCHTOBROKER
//*******************************//
#define BYPASSSETUP
//#define CreateUnicode
#define CheckUnicode    //software lock security
//*******************************//
#define ver2    
//#define B32            //option 1-5 or B32
//#define fixedurl      //fixed url for [ESP32S3] only

#define chphpw      //bypass check phone password
//#define uart1       //software uart   

//#define invout      1         //invert input
//#define invin       1         //invert output

#define writeonly   0           //rwswitchs
#define readwrite   1           //rwswitchs

#define DPLAY       1           //phone
#define VERIFY      2
#define DWORK       3
#define AWORK       4
#define KEYINIT     5
#define JDONE       6

#define ON          1
#define OFF         0
#define CLOSE       3           //for STATUS
#define OPEN        2

#define xcount      6           //edit table
#define ycount      40

#define eessid      0           //50
#define adddataz0   50          //240       8 bit            
#define adddataz1   290         //240       8 bit shif 8
#define adddataz2   530         //240       8 bit shit 8
#define adddataz3   770         //240       8 bit 
#define adddataz4   1010        //480       16 bit
#define MQSTdata    1490        //500
#define phpw        2000        //20
#define editpw      2020        //20    
#define MQtopic     2040        //40  
#define phonesize   2080        //4 
#define keychar     2084        //400
#define unicode     2484        //16
#define timeclock   2450        //500
#define mqttpass    2950        //
#define EEPROM_SIZE 3072        //

//https://www.espressif.com/sites/default/files/documentation/esp32-s3_hardware_design_guidelines_en.pdf
//GPIO 26-32 SPI flash
//PSRAM 33-37
//ESP32-S3R8 ESP32-S3R8V GPIO 33-37
//Should not use 0 3 45 46
//38 led rgb
#ifdef B32              
#define MaxOut  4
//#define MaxIn   4
//#define MaxAin  4
#define setuppin 34
#define Pout1   32
#define Pout2   33
#define Pout3   25
#define Pout4   26
#define Pout5   32
#define Pout6   33
#define Pout7   25
#define Pout8   26
#define Pin1    13
#define Pin2    14
#define Pin3    13
#define Pin4    14
#define Pin5    13
#define Pin6    14
#define Pin7    13
#define Pin8    14
#define Ain1    12
#define Ain2    12
#define Ain3    12
#define Ain4    12
#define pw_enable_sw    27
#endif

#ifdef ver1     //T board
#define SERIAL1_TX_PIN 47 
#define SERIAL1_RX_PIN 45 

#define Pin1 47
#define Pin2 48
#define Pin3 45
#define Pin4 35
#define Pin5 35
#define Pin6 36
#define Pin7 37   
#define Pin8 38

#define Pout1 8
#define Pout2 18
#define Pout3 17
#define Pout4 16
#define Pout5 15
#define Pout6 7
#define Pout7 6   
#define Pout8 5
#define Ain0 0
#define Ain1 9
#define Ain2 10
#define Ain3 11
#define Ain4 12

#define SETUPSTATE  1                //17
#define Enmqttclient  16           //RUN OR SIM BUTTON    
#define mqttbrokenpin  15
#define setuppin  13
#endif
#ifdef ver2     //squre board 8 output 8 input

#define SERIAL1_TX_PIN 47 
#define SERIAL1_RX_PIN 45 

#define MaxIn  8
#define Pin1 7
#define Pin2 15    //DEBUG PIN  
#define Pin3 16
#define Pin4 17
#define Pin5 18
#define Pin6 8
#define Pin7 46   
#define Pin8 13     

#define MaxOut  8
#define Pout1 42
#define Pout2 41
#define Pout3 40
#define Pout4 39
#define Pout5 37
#define Pout6 36
#define Pout7 35   
#define Pout8 45

#define Ain1 4
#define Ain2 5
#define Ain3 3
#define Ain4 6

#define Aout1 9
#define Aout2 10
#define Aout3 11
#define Aout4 12   

#define setuppin    1         //SETUP BUTTON
#define pw_enable_sw   2 
#define Enmqttclient  16   
#define mqttbrokenpin  15 

//#define mqttbrokenpin  37
//#define mqttclientpin  38
#endif

#ifdef ver3             //with circle watch inside//
#define SERIAL1_TX_PIN 47 
#define SERIAL1_RX_PIN 45 

#define Pin1 37
#define Pin2 38
#define Pin3 39
#define Pin4 40
#define Pin5 41
#define Pin6 42
#define Pin7 2   
#define Pin8 1

#define Pout1 8
#define Pout2 18
#define Pout3 17
#define Pout4 16
#define Pout5 15
#define Pout6 7
#define Pout7 6
#define Pout8 5   

#define Ain1 14
#define Ain2 13
#define Ain3 12
#define Ain4 11

#define Aout1 9
#define Aout2 10
#define Aout3 35
#define Aout4 36

#define setuppin        15  //work with SETUPSTATE
#define setuppassword   7  //work with SETUPSTATE

#endif
#ifdef ver4             //4 input/output small PLC
#define SERIAL1_TX_PIN 47 
#define SERIAL1_RX_PIN 45 

#define Pin1 35
#define Pin2 36
#define Pin3 37
#define Pin4 38
#define Pin5 0
#define Pin6 0
#define Pin7 0
#define Pin8 0

#define Pout1 21        //4066 convert voltage to 3.3V
#define Pout2 14
#define Pout3 13
#define Pout4 12
#define Pout5 0        //4066 convert voltage to 3.3V
#define Pout6 0
#define Pout7 0
#define Pout8 0

#define Aout0 0
#define Aout1 0
#define Aout2 0
#define Aout3 0
#define Aout4 0

#define Ain0 0
#define Ain1 0
#define Ain2 0
#define Ain3 0
#define Ain4 0

#define setuppin  4         //SETUP BUTTON
#define pw_enable_sw  7 
//#define mqttbrokenpin  37
//#define mqttclientpin  38
#endif
#ifdef ver5             //5 Liligo 4 relay
#define Pin1 0
#define Pin2 0
#define Pin3 0
#define Pin4 0
#define Pin5 0
#define Pin6 0
#define Pin7 0
#define Pin8 0

#define Pout1 21        
#define Pout2 19
#define Pout3 18
#define Pout4 5
#define Pout5 0        //4066 convert voltage to 3.3V
#define Pout6 0
#define Pout7 0
#define Pout8 0

#define Aout0 0
#define Aout1 0
#define Aout2 0
#define Aout3 0
#define Aout4 0

#define Ain0 0
#define Ain1 0
#define Ain2 0
#define Ain3 0
#define Ain4 0

#define setuppin  13         //SETUP BUTTON
#define pw_enable_sw 27 
//#define mqttclientpin  36
#endif
#ifdef  ver6    //KC868
#define SERIAL1_TX_PIN 17 
#define SERIAL1_RX_PIN 16 

#define MaxOut  4
#define MaxIn   4
#define UartTx  17
#define UartRx  16

#define Pin1 36
#define Pin2 39
#define Pin3 27
#define Pin4 14

#define Pout1 2        
#define Pout2 15
#define Pout3 29
#define Pout4 26

#define Ain0 32
#define Ain1 33
#define Ain2 34
#define Ain3 35

#define Aout 27
#define Aout 14

#define Timp2 12
#define Timp1 16

#define Beep  18

#define IRD   23
#define IRS   22  

#define setuppin  19         //SETUP BUTTON
#define pw_enable_sw 21 
#endif