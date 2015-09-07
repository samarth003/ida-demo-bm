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
  char charVal_solar[6];            
  String stringVal_solar = "";
  
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
  
  //convert char array to double
  wData = atof(wSpeed);
  wAngleData = atof(wAngle);
  wTempData = atof(wTemp);

  Serial.print("wind speed:");
  Serial.print(wData);
  Serial.print(";wind angle:");
  Serial.print(wAngleData);
  Serial.print(";wind temp:");
  Serial.print(wTempData);
  
  memset(inputString,0,sizeof(inputString)); //clear the character array
  mySerial.flush();
  Serial.flush();

  //Solar radiation SP 2015 data extraction     
  solar_sens_Value = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.3V), multiplication factor of 1.52 to convert to a voltage (0 - 5V)
  //float solar_voltage = solar_sens_Value * (3.3 / 1023.0)*1.52;
  solar_val = solar_sens_Value * 0.25;
/* dtostrf(solar_val, 2, 2, charVal_solar);  //4 is mininum width, 4 is precision; float value is copied onto buff
  for(int i=0;i<sizeof(charVal_solar);i++){
    //Serial.print(charVal_temp[i]);
  }
  //convert chararray to string
  for(int i=0;i<sizeof(charVal_solar);i++){
    stringVal_solar+=charVal_solar[i];
  }
*/
  Serial.print(";solar rad:");
  Serial.println(solar_val);
        
}



