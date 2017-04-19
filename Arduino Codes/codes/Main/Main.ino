#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
RF24 radio(9,10);

#define trigFront 5
#define echoFront 4
#define trigSide 7
#define echoSide 6
#define irFront 2
#define irSide 3
#define m1PinLF A2
#define m1PinLB A3
#define m1PinRF A0
#define m1PinRB A1

//dir 2-> Turn Right, 1-> Forward, 0-> Stop, -1-> Back, -2-> Turn Left
unsigned long CarName = 1;
const uint64_t pipes[2] = { 0xF0F0F0F0E0LL, (0xF0F0F0F0E0LL+CarName) };
int obsFront, obsSide ,dir;
unsigned long distFront, distSide, xDestination, yDestination, xStart, yStart, rd;
unsigned long dirCar;
int upd, updrem, i = 0;
unsigned long  toFront;
unsigned long  dirChange;
unsigned long ACK = 0;
unsigned long int  timeMain;
unsigned long int timeMove , timeMovefunc;
unsigned long int xPos = 0;
unsigned long int yPos = 0;
int Posflag = 1;
int Moveflag = 0;
int flag = 0;

void setup() {
  //Serial communication for debugging
  Serial.begin(57600);
  //Sensor and motor pin control
  pinMode(irFront, INPUT);
  pinMode(irSide, INPUT);
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigSide, OUTPUT);
  pinMode(echoSide, INPUT);
  pinMode(m1PinLF, OUTPUT);
  pinMode(m1PinLB, OUTPUT);
  pinMode(m1PinRF, OUTPUT);
  pinMode(m1PinRB, OUTPUT);
  //Set car to Stop
  motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,0);
  //Radio communication for Inter node transmission
  printf_begin();
  radio.begin();
  radio.openReadingPipe(1,pipes[0]);
  radio.openWritingPipe(pipes[1]);
  radio.setRetries(15,15);
  radio.startListening();
  coordinate_call();
  timeMove = millis();
}

void loop() {

    
    distFront  = ultra(echoFront,trigFront);
    distSide  = ultra(echoSide,trigSide);
    obsFront = ir(irFront);
    obsSide = ir(irSide);
    Serial.print(Moveflag);
    Serial.print(" ");
    Serial.print(Posflag);
    Serial.print(" ");
    Serial.print(xPos);
    Serial.print(" ");
    Serial.print(yPos);
    Serial.print(" ");
    Serial.print((millis() - timeMove)/2000);
    Serial.print(" ");
    Serial.println(distFront);
    if ((distFront > 10)){
      pathtranslate();
      carmove();
      posupdate();
    }
    else{
        motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,0);
        Moveflag = 9;
    }
    
    if(radio.available()){
        rd = radio_recieve();
        bool timeout = false;
        delay(20);
        if(rd == (0xADD0+CarName)){
            radio_transmit(1);
            Serial.println("Call ACK sent");
            ACK = 0;
            timeMain = millis();
            while ((ACK != 1)&&((millis()-timeMain)<2000)){
                radio_transmit(0xFF00+CarName);  //Comm preamble
                radio_transmit(CarName);
                ACK = radio_recieve();
            }
            if(ACK==1){
                Serial.println("ACK recieved");
                delay(100);
                radio_transmit(xPos);
                delay(100);
                radio_transmit(yPos);
                Serial.print(distFront);
                Serial.print(" ");
                Serial.print(xPos);
                Serial.print(" ");
                Serial.print(yPos);
                Serial.print(" ");
                Serial.println(Moveflag);
                
            }
            else
              Serial.println("Reply missed");
         }
     }
  }
