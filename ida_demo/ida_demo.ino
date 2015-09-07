#include<SoftwareSerial.h>

char inputString[128] = "";         // a char array to hold incoming data
//boolean stringComplete = false;
SoftwareSerial mySerial(9,8);

void setup() {
  Serial.begin(57600); 
  //Serial.begin(4800); //RX2 of Due
  mySerial.begin(4800);
}

void loop() {
  String sensor_data = "";  
  uint8_t wCount;
  uint8_t wLoopCount = 6;
  uint8_t countOne;
  char *pString;
  char *pTemp;
  char wSpeed[6] = "";
  char wAngle[6] = "";
  char wTemp[6]  = "";
  //String windSpeed = "";
  //String windAngle = "";
  //String windTemp = "";
  
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
/*      
  for(uint8_t countOne=0; countOne<wCount; countOne++){
      //Serial.print(inputString[countOne]);
  }
  if(mySerial.overflow()){
    Serial.println("buffer is overflown!");  
  }
*/
  pString = strstr(inputString, "$IIMWV");   
  pTemp   = strstr(inputString, "$WIXDR");
  //Serial.println(*(pString+1));
  
  if((pString != NULL) && (pTemp != NULL)){
    //Serial.println("testing here.."); //with SP 2015, it does not enter this loop.FAIL!!
    for(wCount=0; wCount<6; wCount++){
      wSpeed[wCount] = inputString[(int)(pString-inputString+((char)15))+wCount];
      //wSpeed[wCount] = pString[15 + wCount]; 
    }
    for(wCount=0; wCount<6; wCount++){
      wAngle[wCount] = inputString[(int)(pString-inputString+((char)7))+wCount];
    }
    for(wCount=0; wCount<6; wCount++){
      wTemp[wCount] = inputString[(int)(pTemp-inputString+((char)9))+wCount];
    }
    //for(wCount=0; wCount<5; wCount++){
     // Serial.print(wTemp[wCount]);    //to print the values from the buffer
   // }
   
  }else{
    Serial.println("Token not found");
  }
  
  String windSpeed(wSpeed);
  String windAngle(wAngle);
  String windTemp(wTemp);

//convert char array to string        
  for(uint8_t num1=0; num1<sizeof(wSpeed); num1++){
    windSpeed += wSpeed[num1];
  }
  for(uint8_t num2=0; num2<sizeof(wAngle); num2++){
    windAngle += wAngle[num2];
  }
  for(uint8_t num3=0; num3<sizeof(wTemp); num3++){
    windTemp += wTemp[num3];
  }
  
  //Serial.println(wData);
  //Serial.println(wAngleData);
  //Serial.println(wTempData);
    
  sensor_data += windSpeed;
  //sensor_data += "; ";
  sensor_data += windAngle;
  //sensor_data += "; ";
  sensor_data += windTemp;
  //sensor_data += "; ";
  //sensor_data += stringVal_solar;
  
  Serial.println(sensor_data);
  
  memset(inputString,0,sizeof(inputString)); //clear the character array
  mySerial.flush();
  Serial.flush();      
}



