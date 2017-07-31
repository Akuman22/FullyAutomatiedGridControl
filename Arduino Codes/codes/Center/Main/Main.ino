#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
RF24 radio(9,10);

const uint64_t pipes[3] = { 0xF0F0F0F0E0LL, 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL };
unsigned long carNameCall, carDistFront, carDistSide, rd, STOP;
unsigned long xStart[2],yStart[2],xDestination[2],yDestination[2];
unsigned long ACK = 0;
unsigned long int timeMain;
int flag = 0, skipFlag = 0, skipValue = 0;
int i = 1, num = 0;
unsigned long int dF,dS,xPos[2],yPos[2];





void setup() {
  Serial.begin(57600);
  Serial.print("#");
  printf_begin();
  radio.begin();
  radio.setRetries(15,15);
  radio.openReadingPipe(1,pipes[1]);
  radio.openReadingPipe(2,pipes[2]);
  radio.openWritingPipe(pipes[0]);
  radio.startListening();
  xStart[0] = 0;
  yStart[0] = 0;
  xStart[1] = 0;
  yStart[1] = 0;
  xDestination[0] = 15;
  yDestination[0] = 15;
  xDestination[1] = 25;
  yDestination[1] = 25;
}

void loop() {
  if(skipValue == 2){
    if(skipFlag == 1){
      Serial.print("SF");
      Serial.print(carNameCall);
      Serial.print("#");
      skipFlag = 0;
    }
/*    if(i == 1)
    {
      i = 2; 
      skipValue = 0;

    }
    else if(i == 2)
   {
     i = 1;
     skipValue = 0;

    }*/
  }
    ACK = 0;
    timeMain = millis();
    while((ACK==0)&&((millis() - timeMain)<3000)){
      delay(50);
      radio_transmit(0xADD0+i);
      delay(25);
      ACK = radio_recieve();
    }
     Serial.print(i);
     Serial.print("A");
     Serial.print(String(ACK,HEX));
     Serial.print("#");
    if(ACK == 6){
      skipValue = 2;
      skipFlag = 0;
      Serial.print("rACK ");
      Serial.print(i);
      Serial.print("#");
      delay(20);
      ACK = 0;
      rd = 0;
      carNameCall = 0;
      rd = radio_recieve();
      carNameCall = radio_recieve();
      timeMain = millis();
      while(((rd - carNameCall)!=0xFF00)&((millis()-timeMain)<500)){
      rd = radio_recieve();
      carNameCall = radio_recieve();
    }
    if((rd - carNameCall)==0xFF00){
      delay(100);
      radio_transmit(1);
      xPos[carNameCall-1] = radio_recieve();
      yPos[carNameCall-1] = radio_recieve();
      Serial.print("CC");
      Serial.print(carNameCall);
      Serial.print("XP");
      Serial.print(xPos[carNameCall-1]);
      Serial.print("YP");
      Serial.print(yPos[carNameCall-1]);
      Serial.print("#");
    }
    else{
      Serial.print("PM");
      Serial.print(i);
      Serial.print("#");
    }
    }
    else if(ACK == 7)
    {
      skipValue = 2;
      skipFlag = 0;
      Serial.print("C");
      Serial.print(i);
      Serial.print('#');
      while(!Serial.available()){}
      delay(30);
      num = 0;
      num = Serial.read();
      xDestination[i-1] = 0;
      while(num != '#')
      {
        xDestination[i-1] = xDestination[i-1]*10 + int(num) - 48;
        delay(30);
        num = Serial.read();
      }
      delay(30);
      num = Serial.read();
      yDestination[i-1] = 0;
      while(num != '#')
      {
        yDestination[i-1] = yDestination[i-1]*10 + int(num) - 48;
        delay(30);
        num = Serial.read();
      }
      Serial.print(xDestination[i-1]);
      Serial.print(" ");
      Serial.print(yDestination[i-1]);
      Serial.print("#");
      coordinate_ask();
    }
    else
    {
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
  /*    rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
      rd = radio_recieve();
*/      
      skipValue += 1;
      skipFlag = 1;
      }
}
  
