#include <Arduino.h>
#include <SoftwareSerial.h>

/*
  *@File  : DFRobot_Distance_A01.ino 
  *@Brief : This example use A01NYUB ultrasonic sensor to measure distance
  *         With initialization completed, We can get distance value 
  *@Copyright [DFRobot](https://www.dfrobot.com),2016         
  *           GUN Lesser General Pulic License
  *@version V1.0           
  *@data  2019-8-28
*/
const uint8_t RX = 6;
const uint8_t TX = 7;


SoftwareSerial mySerial(RX,TX); // RX, TX
unsigned char data[4]={};
float distance;
float read_distance;

void setup()
{
 Serial.begin(57600);
 mySerial.begin(9600); 
 pinMode(TX, OUTPUT);

}

float measure (bool tempCorrect){

  digitalWrite(TX,tempCorrect);
  delay(150);

  //clear buffer
  while(mySerial.available() > 0) {
    char clear = mySerial.read();
  }

  //wait for new measurement
  while(mySerial.available() <= 0) {
    delay(2);
  }
  
  //read until startbyte 0xFF is received
  do{
    data[0]=mySerial.read();
    //  Serial.print("data0:");
    //  Serial.println(data[0],HEX);
     delay(2);
  }
  while(data[0] != 0xff);
  
  //read the remaining 3 bytes
  int i;
  for(i=1;i<4;i++)
  {
    data[i]=mySerial.read();
    // Serial.print("data" + String(i)+ ":");
    // Serial.println(data[i],HEX);
    delay(2);
  }
  mySerial.flush();

  int sum;
  sum=(data[0]+data[1]+data[2])&0x00FF;
  // Serial.println("SUM:" + String(sum));
  if(sum==data[3])
  {
    distance=(data[1]<<8)+data[2];
    // Serial.println("DISTANCE:" + String(distance));
    if(distance>280)
    {
      return distance/10;
    }
    else 
    {
      Serial.println("...");
      Serial.println("Below the lower limit");      
      return 0;  
    }
  }
  Serial.println("ERROR");
  return -1;
}

void loop()
{  
  read_distance = measure(LOW);
  read_distance = measure(LOW);
  Serial.print("distance actual=");
  Serial.print(read_distance);
  Serial.println("cm");
  //delay(150);

  read_distance = measure(HIGH);
  read_distance = measure(HIGH);
  Serial.print("distance corrected=");
  Serial.print(read_distance);
  Serial.println("cm");
  Serial.println();

  delay(1000);
}