static const char PROGMEM INDEX_HTML_mqsetup[] = R"rawliteral(
<!--4/10/2024-->
<html>
<script src='https://cdnjs.cloudflare.com/ajax/libs/qrcodejs/1.0.0/qrcode.min.js'></script>  
<body><div id=ssetup></div>
<h2 id='UTLI1'></h2>
<div class='qr' id='qrcode1' style='margin-left:200px;'></div><br><br>
<h2>PHONE REMOTE CONTROL follow steps, press buttons below</h2>
<td><button type='button' id='grc' onclick='GererateRC(2)' style='margin-left:40px'>Gererate random PHCODE</button></td><br>
<br><button type='button' onclick='PhoneLogicCode()' style='margin-left:50px' >Gen Phone Login code</button><br>
<h2 id='remine' style='background-color:yellow;'></h2>
<h2 id='UTLI2'></h2>
<div class='qr' id='qrcode2' style='margin-left:200px;margin-bottom:50px;'></div><br><br>
<div id=dsetup></div>
</body>
</html>  
<script>
// For mqtt
var xsetdev=4;
var ysetdev=7;
var unid;
var txdata;
//for htmltestpage.html
var rowtext = Array.from(Array(xsetdev), () => new Array(ysetdev)); 
var systcell = Array.from(Array(xsetdev), () => new Array(ysetdev).fill("")); 

function sysloadinitdata(){      
console.log('cd0',systcell);   
  //localStorage.clear(); //all items
  //localStorage.removeItem('systcell');
  var np = ['SERVER','LocalTopic','MASTER TOPIC','SLAVE TOPIC A','SLAVE TOPIC C','SLAVE TOPIC B','SLAVE TOPIC C'];
  var pp = ['PORT','ECODE','* Subscribe Master','*Subscribe Slave A','*Subscribe Slave B','*Subscribe Slave C'];
  var dp1 = ['User ID','Qos','Refresh','Refresh','Refresh','Refresh'];
  var dp2 = ['PW','Refresh period','Refresh period','Refresh period','Refresh period','Refresh period'];  
  for(let t=0;t<ysetdev;t++)                                       
      {if(t===0)  
        {rowtext[0][t] = "<td>"+np[t]+":<input type='text' id='ecode' maxlength='120' value='"+systcell[0][t]+"'onchange=updatetcell(0,"+t+",value) style='width:180px'></td>"                      
        rowtext[1][t] = "<td>"+pp[t]+":<input type='number' step='any' maxlength='4' value='"+systcell[1][t]+"'onchange=updatetcell(1,"+t+",value) style='width:100px;margin-right:50px'></td>"   
        rowtext[2][t] = "<td>"+dp1[t]+":<input type='text' maxlength='20' value='"+systcell[2][t]+"'onchange=updatetcell(2,"+t+",value) style='width:100px'></select></td>"             
        rowtext[3][t] = "<td>"+dp2[t]+"<input type='text' maxlength='20' value='"+systcell[3][t]+"'onchange=updatetcell(3,"+t+",value) style='width:100px'></select></td>"
        }                                  
      if(t===1)
        {//rowtext[0][t] = "<td>*Local MQTT server encrypt<input type='checkbox' id='mybox' onclick='updatecolor()'></td>"
        rowtext[0][t] = "<td>"+pp[t]+":<input id='Ecode' type='text' maxlength='32' value='"+systcell[1][t]+"'onchange=updatetcell(1,"+t+",value) style='width:200px'></select></td>"   
        rowtext[1][t] = "<td>PHCODE<input id='PHcode' type='text' maxlength='32' value='"+systcell[2][t]+"'onchange=updatetcell(1,"+t+",value) style='width:162px'></select></td>"
        rowtext[2][t]=  "<td><button onclick='copyToClipboard()' style='margin-left:15px'>Copy ECODE to Clipboard</button></td>"
        rowtext[3][t] = "<td><button type='button' id='grc' onclick='GererateRC(1)' style='margin-left:10px'>***Gererate random code</button></td>"               
        }           
      if(t>1 && t<6) 
        {rowtext[0][t] = "<td>"+np[t]+":<input type='text' maxlength='20' value='"+systcell[0][t]+"'onchange=updatetcell(0,"+t+",value) style='width:160px'></td>"
        rowtext[1][t] = "<td>"+pp[t]+":<input type='radio' id='radio"+t+"' name='group1' value='' onclick='updatecolor()'><br>"
        rowtext[2][t] = "<td>"+dp2[t]+":<input type='number' step='any' maxlength='4' value='"+systcell[2][t]+"'onchange=updatetcell(2,"+t+",value) style='width:80px'></select></td>"             
        rowtext[3][t] = "<td></td>"             
        }  
      if(t>=6)
        {rowtext[0][t] = "<td>##WSS encrypt(Phone only)<input type='checkbox' id='enwss' onclick='updatecolor()'></td>"              
        rowtext[1][t] = "<td>Enable PLC Mqtt<input type='checkbox' id='enplc' onclick='updatecolor()'></td>"
        rowtext[2][t] = "<td>Enable phone Mqtt<input type='checkbox' id='enphone' onclick='updatecolor()'></td>"             
        rowtext[3][t] = ""   
        }  
      } 
       
  for(let j=0;j<ysetdev;j++)  
      {row = document.getElementById('myDRow'+j.toString());         
        x0 = row.insertCell(0);  //insert
        x1 = row.insertCell(1);  //insert
        x2 = row.insertCell(2);  //insert
        x3 = row.insertCell(3);     
        x0.innerHTML = rowtext[0][j];  //                      
        x1.innerHTML = rowtext[1][j];  //           
        x2.innerHTML = rowtext[2][j];  //   
        x3.innerHTML = rowtext[3][j];  //        
      }
      
  }     


function copyToClipboard() {
    // Get the textarea element
var textarea = document.getElementById("Ecode");    
    textarea.select();
    textarea.setSelectionRange(0, 99); // For mobile devices
    document.execCommand("copy");    
    textarea.setSelectionRange(0, 0);
}

function updatetcell(x,y,value)
{systcell[x][y]=value;
localStorage.setItem('systcell',JSON.stringify(systcell));
document.getElementById('upl').style.backgroundColor='yellow';
}

function updatecolor()
{
document.getElementById('upl').style.backgroundColor='yellow';  
}

function UploadsetupMqsu()  //for ????//
{
Uploadsetup('MQSU');
document.getElementById('uph').style.backgroundColor='yellow';   
}

function Uploadsetup(txdata)  //txdata= "MQSD"
{//MQSU MQSD      
var xhtp = new XMLHttpRequest(); 
  xhtp.onreadystatechange = function() {
  txre="";  
  tyre="";
  if(this.readyState == 4 && this.status == 200) {      
      txre=this.responseText[0]+this.responseText[1]+this.responseText[2]+this.responseText[3];                                       
      tyre=this.responseText;
      if(txre==="mQsD")   //mQsU is Download     
      {if(tyre[4]==='#' && tyre[5]==='#')
        {Localdefault(1);      
        localStorage.removeItem('plcdata'); 
        console.log('localStorage.removeItem3');                
        }
      else  
        {console.log('mqs upload ok',this.responseText);
        unid=this.responseText[494]+this.responseText[495]+this.responseText[496]+this.responseText[497]+this.responseText[498]+this.responseText[499];       
        let x=0;let y=0;let z=0;
        for(var t=4;t<500;t++)
          {if(tyre[t]=='%')
            {if(x++>=(xsetdev-1))
              {x=0;y++;
              if(y>=ysetdev)  
                break; //y=0;   
              }                                 
            }  
          else                       
            systcell[x][y]=systcell[x][y]+tyre[t];      
          }
        if(systcell[0][0]===null || systcell[0][0]===undefined || systcell[0][0]==="" || systcell[1][1].length!=32 || systcell[2][1].length!=32)
          Localdefault(2);  
        else
          DisplayUpdate();
        }
      }  
    }  
  else
    {if(this.readyState == 4 && this.status == 0)
      {window.alert('Unique code not found, check LAN not match');                                                      
      unid="123456";
      }
    } 
  t=systcell[3][1]-0x30;
  if(!(t>=2 && t<=5)) t=2;
      document.getElementById('radio'+t).checked='checked';                 
  }  
  if(txdata==="MQSU")
  {
  systcell[0][6]='0';
  if(document.getElementById('enwss').checked===true)
    systcell[0][6]='1';
  
  systcell[1][6]='0';
  if(document.getElementById('enplc').checked===true)
    systcell[1][6]='1';       

  systcell[2][6]='0';
  if(document.getElementById('enphone').checked===true)
    systcell[2][6]='1';   

  //systcell[3][6]='0';
  //if(document.getElementById('mybox').checked===true)
  //  systcell[3][6]='1'; 

  for(let t=2;t<=5;t++)
  {if(document.getElementById('radio'+t).checked)
    { systcell[0][1]=systcell[0][t]; //main topic move to location
      systcell[3][1]=t+0x30;  
      break;
    }
  }    
  for(var y=0;y<ysetdev;y++)
    {for(var x=0;x<xsetdev;x++)
      txdata=txdata+systcell[x][y]+'%';   //^%";    
    }   
  window.alert("Upload successful");
  }  
  console.log("txdata=",txdata);     
  //URL="192.168.1.95:8088";
  URL=window.location.host; 
  let t=0;
  let Txdata="";
  let L=txdata.length;
  for(t=0;t<L;t++)
    {if(txdata[t]===" ")
      Txdata=Txdata+"_";
    else
      Txdata=Txdata+txdata[t];
    }
  xhtp.open("GET","http://"+URL+"/action?go=" + Txdata, true);     
  xhtp.send();  
}

function makeid(length) {
    let result = '';
    const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    const charactersLength = characters.length;
    let counter = 0;
    while (counter < length) {
      result += characters.charAt(Math.floor(Math.random() * charactersLength));
      counter += 1;
    }
    return result;
}

function sumCode(str) {
    let sum = 0;
    for (let i = 0; i < str.length; i++) {
        sum += str.charCodeAt(i);
    }
    return sum;
}


function GererateRC(type)
{var code1;
var code2;    
if(type==2)
  {code1=unid+makeid(22);  
  systcell[2][1]=code1+sumCode(code1);
  }
if(type==1 || type==3)
  {code2=unid+makeid(22);   
  systcell[1][1]=code2+sumCode(code2);
  }
DisplayUpdate();  
//Uploadsetup('MQSU');  //upload and display
}

function Loaddefault(type)      
{
if(type===1)   //HIVEMQ WSS
  {//systcell[0][0]='XXX eu.hivemq.cloud';//ste=localStorage.getItem('myurl'); 
  systcell[0][0]='f27d2ae246004779b11b64b42778b4a1.s2.eu.hivemq.cloud'; 
  systcell[1][0]='8883'
  systcell[2][0]='nganmomo'; 
  systcell[3][0]='5585Ngan';  
  systcell[0][6]='1';   
  systcell[1][6]='0'; //Enable PLC Mqtt
  systcell[2][6]='1'; 
  }
else if(type===2)     //Simple HIVEMQ
  {systcell[0][0]='broker.hivemq.com';                       //ste=localStorage.getItem('myurl'); 
  systcell[1][0]='1883'
  systcell[2][0]=''; 
  systcell[3][0]=''; 
  systcell[0][6]='0'; 
  systcell[1][6]='1'; //Enable PLC Mqtt
  systcell[2][6]='1'; //Enable phone Mqtt     
  }    
else if(type===3)   //Local Broker
  {systcell[0][0]='192.168.1.186';                       //ste=localStorage.getItem('myurl'); 
  systcell[1][0]='1883';  
  systcell[2][0]='input_id'; 
  systcell[3][0]='input_pw';   
  systcell[0][6]='0';
  systcell[1][6]='1'; //Enable PLC Mqtt
  systcell[2][6]='1'; //Enable phone Mqtt
  }
//systcell[0][1]="myTopic1";
//systcell[1][1]='Z7?P[{|L'; 
/////for mqtt master ans slave////////
systcell[3][1]='1';  //Subscribe Mqtt master 
for(var t=2;t<ysetdev-1;t++)  
  {
  systcell[0][t]="myTopic"+(t-1);     
  systcell[1][t]='1'; 
  systcell[2][t]='1'; 
  systcell[3][t]='1';    
  }     
t=2;
systcell[0][1]=systcell[0][t];  //select typic follow Subscribe
systcell[3][1]=t+0x30;  //Subscribe master
document.getElementById('radio'+t).checked='checked';  
document.getElementById('efftopic').innerText=effectivetopic;
GererateRC(1);
Uploadsetup('MQSU');  //upload and display
document.getElementById('uph').style.backgroundColor='yellow';
if(type==2)
  Uploadsetup('MQSU');
else
  document.getElementById('upl').style.backgroundColor='yellow';
}

//Z7?P  
function Localdefault(type)
{Loaddefault(type);
DisplayUpdate()
}

function DisplayUpdate(){
localStorage.setItem('systcell',JSON.stringify(systcell));
for(let y=0;y<ysetdev;y++)  
  {var row = document.getElementById('myDRow'+y.toString());      
    {for(let j=0;j<xsetdev;j++)          
      row.deleteCell(0);         
    }   
  }    
sysloadinitdata();
if(systcell[0][6]==='0')  
  document.getElementById('enwss').checked=false;
else  
  document.getElementById('enwss').checked=true;
//if(systcell[2][1]==='0')  
//  document.getElementById('mybox').checked=false;
//else  
//  document.getElementById('mybox').checked=true;
///////////////////////
if(systcell[1][6]==='0') 
  document.getElementById('enplc').checked=false;
else
  document.getElementById('enplc').checked=true; 
///////////////////////
if(systcell[2][6]==='0') 
  document.getElementById('enphone').checked=false;
else
  document.getElementById('enphone').checked=true;     
///////////////////////
  t=systcell[3][1]-0x30;  //subscript master
if(!(t>=2 && t<=5)) t=2;
  document.getElementById('radio'+t).checked='checked';    
}

//let t=systcell[3][1];
// Get the radio input element by its id
//var radioInput = document.getElementById("radio2");
// Set the checked property to true
//radioInput.checked = true;
syssetup=
"<h3>To unlock this setting, the 'PWSET' switch must be in the set position and locked again to take effect.</h3>\
<table class='devtable'>\
<tbody>\
<tr id='myDRow0'></tr><tr id='myDRow1'></tr><tr id='myDRow2'>\
</tr><tr id='myDRow3'></tr><tr id='myDRow4'></tr><tr id='myDRow5'></tr><tr id='myDRow6'></tr>\
</tbody>\
</table>\
<h3 style='display:inline'>For communcation between two PLC module, set master and slave to the same ECODD</h3><br>\
<h3 style='display:inline'>PLC MQTT EFECTIVE TOPIC = prefix + ECODE + input topic</h3><br>\
<h3 style='display:inline'>PHONE MQTT EFECTIVE TOPIC = prefix + Phcode</h3><br>\
<br>\
<h3 style='display:inline'>SELECT DEFAULT CONFIG:</h3><br>\
<button type='button' onclick='Localdefault(1)' style='margin-left:50px' >HIVEMQ WSS(Phone)</button>\
<h3 style='display:inline'> Use for WSS mqtt (PASSWWORD AND USERID REQUIRE)</h3><br>\
<button type='button' onclick='Localdefault(2)' style='margin-left:50px' >#Simple HIVEMQ</button>\
<h3 style='display:inline'> Use for Simple mqtt without password and use ID</h3><br>\
<button type='button' onclick='Localdefault(3)' style='margin-left:50px' >#Local Broker</button>\
<h3 style='display:inline'> Use for Simple local mqtt broker without password and use ID</h3><br><br>\
<label for='cars' style='margin-left:50px'>Choose a Free Mqtt Broker [Obtional]: </label>\
<select name='freemqtt' id='freemqtt' onchange='recopycolor()'>\
<option value='broker.hivemq.com'>broker.hivemq.com</option>\
<option value='test.mosquitto.org'>test.mosquitto.org</option>\
<option value='broker.emqx.io'>broker.emqx.io</option>\
<option value='public.mqtthq.com'>public.mqtthq.com</option>\
</select>\
<button type='button' id='cts' onclick='copytoserver()' style='margin-left:70px'>Copy to server input</button><br>\
<h3 id='uph'>Press Hardware reset key and than Press [Network] button to test the condition.</h3>\
<button type='button' id='upl' onclick='UploadsetupMqsu()' style='margin-left:50px;' >Upload setup</button><br>\
<br><button type='button' onclick='EffectTopic()' style='margin-left:50px' >Get effective Topic</button>\
<h3 id='testNet' style='display:inline;margin-left:100px'></h3>\
<h3 style='display:inline'><label type='text' id='efftopic'></label></h3>\
<h3>##If use MQTT broker encrypt, password and user ID must set, select HIVEMQ to get default setting</h3>\
<h3>*Select one of the four as the subscription topic to receive Mqtt signals, other three are for transmission.</h3>\
<h3>** All PLC card mush use same ECODE.</h3>\
<h3>Mqtt control is based on static control and the response time is about 1 second. For communication between PLC boards, refresh interval can adjust from 1 second to 10 second</h3>"

var dsetup=
"<br><button onclick='savetoedit()' style='margin-left:40px' id='popupbut' class='popupbut'>Load default test ladder program</button><br><br>\
<h3>close Mqtt setup window, and then,</h3><h3> press Edit page button to upload this program into Edit page</h3><br><br><br>"



var MQqrcode1 = new QRCode('qrcode1','https://ipcworld.w3spaces.com/SVGPLC/PLC/pwaphwss.html');
document.getElementById('UTLI1').innerText='https://ipcworld.w3spaces.com/SVGPLC/PLC/pwaphwss.html';

var loginincode;
var effectivetopic="";
function copytoserver()
{let va=document.getElementById('freemqtt').value; 
document.getElementById('ecode').value=va;
systcell[0][0]=va;
document.getElementById('upl').style.backgroundColor='yellow';
}

function recopycolor()
{
document.getElementById('cts').style.backgroundColor='yellow';  
}

function mqtttest()
{
  client.publish(systcell[1][1],systcell[1][1],true);  
}

function PhoneLogicCode()
{
//loginincode='***'+systcell[0][0]+'***'+systcell[1][0]+'***'+systcell[2][0]+'***'+systcell[3][0]+'***'+systcell[2][1]; 
loginincode="https://freeplc.w3spaces.com/phone/phpwawss?"+systcell[2][1]; 
document.getElementById('qrcode2').innerText='';
var MQqrcode2 = new QRCode('qrcode2',loginincode);
//document.getElementById('remine').innerText='When all input is complete, press the HARDWARE RESET button to make it effective.';
document.getElementById('UTLI2').innerText='Scan QR code by Phone, URL='+loginincode;
}

function EffectTopic()
{
for(let t=2;t<ysetdev-1;t++)  
  {if(document.getElementById('radio'+t).checked===true)
    effectivetopic='P'+systcell[1][1]+systcell[0][t];
  }
//effectivetopic='P'+systcell[1][1]+systcell[0][1];
document.getElementById('efftopic').innerText="Effective topic ="+effectivetopic;
}

window.onload = async function(){
  document.getElementById('ssetup').innerHTML=syssetup; 
  document.getElementById('dsetup').innerHTML=dsetup; 
  loginincode='***'+systcell[0][0]+'***'+systcell[1][0]+'***'+systcell[2][0]+'***'+systcell[3][0]+'***'+systcell[2][1];
  sysloadinitdata();
  Uploadsetup("MQSD");            
}

function savetoedit(){
    //var rplcdata=document.getElementById("values");     
    var rplcdata="50,306,256,0,256,,,,,,,4,,,,,,,,4,,,,,,,,4,,,,,,,,4,,,,,43,299,299,0,,,,,50,306,562,0,306,,,,,,,4,,,,,,,,4\
    ,,,,,,,,4,,,,,,,,4,,,,,43,555,299,0,,,,,50,562,256,0,256,,,,,,,4,,,,,,,,4,,,,,,,,4,,,,,,,,4,,,,,43,811,299,0,,,,,50,562,\
    562,0,306,,,,,,,4,,,,,,,,4,,,,,,,,4,,,,,,,,4,,,,,43,1067,299,0,"
    //document.getElementById("popupbut").innerText="Press Close";   
    document.getElementById("popupbut").style.backgroundColor="green";   
    //rplcdata=rplcdata.value;       
    var test = Array(1920).fill("");  
      var arraylength=0;
      var result="";
      for(var t=0;t<5770;t++)  
        {if(rplcdata[t]===',')
          {if(result!="" && result[0]>='0'&& result[0]<='9')
            test[arraylength]=parseInt(result);
          else
            test[arraylength]=result;  
          result="";
          if(arraylength++>1920)
            break;
          }
        else
          {if(rplcdata[t]==='_') 
            result=result+' ';
          else if(rplcdata[t]>='0' && rplcdata[t]<='~' && rplcdata[t]!=']' && rplcdata[t]!='[')
            {result=result+rplcdata[t];
            //console.log('result=',result);
            }
          }
        }    
      console.log('upptest=',test);
      console.log('uppLength=',test.length);
      //localStorage.setItem('plcdata',rplcdata);
      localStorage.setItem('plcdata',JSON.stringify(test));
      localStorage.setItem('refreshpage',"required");
}

</script>
)rawliteral";