#include <Sensirion.h>
#include<SoftwareSerial.h>

char inputString[128] = "";         // a char array to hold incoming data
const uint8_t sht_dataPin  =  5;//10;
const uint8_t sht_clockPin =  6;//11;

SoftwareSerial mySerial(9,8);
Sensirion tempSensor = Sensirion(sht_dataPin, sht_clockPin);

void setup() {
  Serial.begin(57600); 
  //Serial.begin(4800); //RX2 of Due
  mySerial.begin(4800);
}

void loop() {  
  uint8_t wCount;
  uint8_t wLoopCount = 6;
  uint8_t countOne;
  char *pString;
  char *pTemp;
  char wSpeed[6] = "";
  char wAngle[6] = "";
  char wTemp[6]  = "";
  float wData;
  float wAngleData;
  float wTempData;
  
  //variables for SP 2015
  int solar_sens_Value;
  float solar_val;

  //variables for temp-RH sensor
  float temperature;
  float humidity;
  //float dewpoint;

  while(!mySerial.available()){
    //loop until mySerial is available
  }
  
  while(mySerial.available()) mySerial.read(); //dump serial

  while(wLoopCount-- && wCount < 127){
    delay(100);
    while(mySerial.available() && wCount < 127) {
      inputString[wCount++] = (char) mySerial.read();  
    }
  }
  inputString[127] = '\0';
  delay(1);
  
  pString = strstr(inputString, "$IIMWV");   
  pTemp   = strstr(inputString, "$WIXDR");
  //Serial.println(*(pString+1));
  
  if((pString != NULL) && (pTemp != NULL)){
   // Serial.println("testing here.."); //with sht75, it does not enter this loop.FAIL!!
    for(wCount=0; wCount<6; wCount++){
      wSpeed[wCount] = inputString[(int)(pString-inputString+((char)15))+wCount];
      //wSpeed[wCount] = pString[15 + wCount]; 
    } 
    for(wCount=0; wCount<6; wCount++){
      wAngle[wCount] = inputString[(int)(pString-inputString+((char)7))+wCount];
    }
    /*for(wCount=0; wCount<6; wCount++){
      wTemp[wCount] = inputString[(int)(pTemp-inputString+((char)9))+wCount];
    }*/
  }else{
    Serial.println("Token not found");
  }
  
  //convert char array to double
  wData = atof(wSpeed);
  wAngleData = atof(wAngle);
  wTempData = atof(wTemp);

  Serial.print("wind speed:");
  Serial.print(wData);
  Serial.print(";wind angle:");
  Serial.print(wAngleData);
  //Serial.print(";wind temp:");
  //Serial.print(wTempData);
  
  memset(inputString,0,sizeof(inputString)); //clear the character array
  mySerial.flush();
  //Serial.flush();
  
  //Solar radiation SP 2015 data extraction     
  solar_sens_Value = analogRead(A1);
  solar_val = solar_sens_Value * 0.25;
  Serial.print(";solar rad:");
  Serial.print(solar_val);

  //sht7x data extraction
  //tempSensor.measure(&temperature, &humidity, &dewpoint); //time taken in this function is somehow affecting wind sensor data
  tempSensor.measure(&temperature, &humidity);
  Serial.print(";Temp:");
  Serial.print(temperature);
  Serial.print("C; Humidity:");
  Serial.print(humidity); Serial.println("%");
  //delay(1000);
    
  Serial.flush();      
}



