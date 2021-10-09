#include <Arduino.h>
#include <SoftwareSerial.h>

const uint8_t MOSI_pin = 10;
const uint8_t MISO_pin = 11;
const uint8_t SCK_pin = 12;
const uint8_t SCL_pin = 9;
const uint8_t SDA_pin = 8;
#define RX PIN_PB3
#define TX PIN_PB2
#define SENSORS_ON_PIN PIN_PA5
const uint8_t Sensors_ON = 1;




void setup()
{
  Serial.begin(9600);
  // mySerial.begin(57600);
  delay(100);
  // pinMode(TX, OUTPUT);
  // digitalWrite(TX, LOW);
  
  pinMode(SENSORS_ON_PIN, OUTPUT);
  digitalWrite(SENSORS_ON_PIN, HIGH);
}

void loop(){
  Serial.println("test");
  delay (1000);
}





// unsigned char data[4]={};
// float distance;
// float read_distance;


// void setup()
// {
//   Serial.begin(9600);
//   mySerial.begin(115200); 
//   delay(100);
//   pinMode(TX, OUTPUT);
//   // digitalWrite(TX, LOW);
//   pinMode(Sensors_ON, OUTPUT);
//   digitalWrite(Sensors_ON, HIGH);
//   mySerial.println("Setup complete");
//   mySerial.flush();
// }


// float measure (bool tempCorrect){

//   //digitalWrite(TX, tempCorrect);
//   delay(150);

//   //clear buffer
//   while(Serial.available() > 0) {
//     char clear = Serial.read();
//   }

//   //wait for new measurement
//   while(Serial.available() <= 0) {
//     delay(2);
//   }
  
//   //read until startbyte 0xFF is received
//   do{
//     data[0]=Serial.read();
//      mySerial.print("data0:");
//      mySerial.println(data[0],HEX);
//     delay(2);
//   }
//   while(data[0] != 0xff);
  
//   //read the remaining 3 bytes
//   int i;
//   for(i=1;i<4;i++)
//   {
//     data[i]=Serial.read();
//     mySerial.print("data" + String(i)+ ":");
//     mySerial.println(data[i],HEX);
//     delay(2);
//   }
//   Serial.flush();

//   int sum;
//   sum=(data[0]+data[1]+data[2])&0x00FF;
//   // mySerial.println("SUM:" + String(sum));
//   if(sum==data[3])
//   {
//     distance=(data[1]<<8)+data[2];
//     // mySerial.println("DISTANCE:" + String(distance));
//     if(distance>280)
//     {
//       return distance/10;
//     }
//     else 
//     {
//       // mySerial.println("...");
//       // mySerial.println("Below the lower limit");      
//       return 0;  
//     }
//   }
//   // mySerial.println("ERROR");
//   return -1;
// }

// void loop()
// {  
//   read_distance = measure(LOW);
//   // read_distance = measure(LOW);
//   mySerial.print("distance actual=");
//   mySerial.print(read_distance);
//   mySerial.println("cm");
//   //delay(150);

//   // read_distance = measure(HIGH);
//   // read_distance = measure(HIGH);
//   // mySerial.print("distance corrected=");
//   // mySerial.print(read_distance);
//   // mySerial.println("cm");
//   // mySerial.println();

//   delay(1000);
// }