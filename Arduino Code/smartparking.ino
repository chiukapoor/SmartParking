#include <SoftwareSerial.h>
SoftwareSerial espSerial =  SoftwareSerial(2,3); 

int ir_1 = 12; // Input pin 1
int ir_2 = 8;  // Input pin 2
int ir_3 = 7;  // Input pin 3
int ir_4 = 4;  // Input pin 4
int read_1 = 1;
int read_2 = 1;
int read_3 = 1;
int read_4 = 1;

#define VAL_PROBE 2 // Analog pin 3
String apiKey = "------";     // replace with your channel's thingspeak WRITE API key 
String ssid="----";    // Wifi network SSID
String password ="-----";  // Wifi network password
boolean DEBUG=true;

void showResponse(int waitTime)
{
    long t=millis();
    char c;
    //Serial.println("Working");
    while (t+waitTime>millis())
    {
      if (espSerial.available())
      {
        c=espSerial.read();
        Serial.print(c);
        if (DEBUG){
            //Serial.print(c);
      }
    } 
}
}

boolean thingSpeakWrite(int value1, int value2, int value3, int value4)
{
  String cmd = "AT+CIPSTART=\"TCP\",\"";     // TCP connection
  cmd += "api.thingspeak.com";
  cmd += "\",80";
  espSerial.println(cmd);
  if (DEBUG) 
      Serial.println(cmd);
  if(espSerial.find("Error"))
  {
    if (DEBUG) 
      Serial.println("AT+CIPSTART error");
    return false;
  }
  Serial.println("Sending");
  String getStr = "GET /update?api_key=";   // prepare GET string
  getStr += apiKey;
  
  getStr +="&field1=";
  getStr += String(value1);
  getStr +="&field2=";
  getStr += String(value2);
  getStr +="&field3=";
  getStr += String(value3);
  getStr +="&field4=";
  getStr += String(value4);   
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  espSerial.println(cmd);
  if (DEBUG)  Serial.println(cmd);
  Serial.print(getStr);
  delay(100);
  if(espSerial.find(">"))
  {
    espSerial.print(getStr);
    if (DEBUG)  
      Serial.print(getStr);
  }
  else
  {
    espSerial.println("AT+CIPCLOSE");
    // alert user
    if (DEBUG)   
      Serial.println("AT+CIPCLOSE");
    return false;
  }
  return true;
}


void setup() {
  pinMode(ir_1, INPUT);
  pinMode(ir_2, INPUT);
  pinMode(ir_3, INPUT);
  pinMode(ir_4, INPUT);
  DEBUG=true;           // enable debug serial
  Serial.begin(9600);   
  espSerial.begin(9600); 
  
  espSerial.println("AT+RST");
  showResponse(1000);

  espSerial.println("AT+UART_CUR=9600,8,1,0,0");
  showResponse(1000);

  espSerial.println("AT+CWMODE=1");   // set esp8266 as client
  showResponse(1000);

  espSerial.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");  // set your home router SSID and password
  showResponse(5000);

   if (DEBUG)  
    Serial.println("Setup completed");
}
void loop() {
  if(digitalRead(ir_1) == HIGH){
    read_1 = 1;
  }
  else{
    read_1 = 0;
  }
  if(digitalRead(ir_2) == HIGH){
    read_2 = 1;
  }
  else{
    read_2 = 0;
  }
  if(digitalRead(ir_3) == HIGH){
    read_3 = 1;
  }
  else{
    read_3 = 0;
  }
  if(digitalRead(ir_4) == HIGH){
    read_4 = 1;
  }
  else{
    read_4 = 0;
  }
  //thingSpeakWrite(read_1,read_2,read_3,read_4);
  Serial.println(thingSpeakWrite(read_1,read_2,read_3,read_4));
 
  delay(20000);
}
