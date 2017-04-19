#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,10);

char Fechotext[] = "Front Echo = ";
char Sechotext[] = " Side Echo = ";
char NL = '\n';
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xABCDABCD71LL };

typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};


role_e role = role_pong_back;

void setup(void)
{

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  Serial.begin(57600);
  printf_begin();
  radio.begin();
  radio.setRetries(15,15);
  radio.openReadingPipe(1,pipes[1]);
  radio.openWritingPipe(pipes[2]);
  radio.startListening();
  delay(1000);
  radio.stopListening();
  delay(1000);
  radio.startListening();
  analogWrite(A0,255);
  analogWrite(A1,255);
  analogWrite(A2,255);
  analogWrite(A3,255);



}

void loop(void)
{ 
  unsigned long inp;
  radio.startListening();
  while ( !radio.available() )
    {
      Serial.println("Read");
      int j = 0;
      bool done = false;
      while ((!done)&(j<15))
      {
        j++;
        done = radio.read( &inp, sizeof(unsigned long) );
       }
       Serial.println(inp);
    }
 if(inp == 1)
 {
 analogWrite(A0,0);// FL - back
 analogWrite(A1,255);
 analogWrite(A2,0); // BR back
 analogWrite(A3,255);

 delay(100);

 }
 if(inp == 3)
 {
 analogWrite(A0,255);// FL - back
 analogWrite(A1,0);
 analogWrite(A2,255); // BR back
 analogWrite(A3,0);

 delay(100);
 
 }
 if(inp == 2)
 {
 analogWrite(A0,0);// FL - back
 analogWrite(A1,255);
 analogWrite(A2,255); // BR back
 analogWrite(A3,0);
 
 delay(100);
 }
 if(inp == 4)
 {
 analogWrite(A0,255);// FL - back
 analogWrite(A1,0);
 analogWrite(A2,0); // BR back
 analogWrite(A3,255);


 delay(100);
 
 }
    
 else
 {
  analogWrite(A0,255);
  analogWrite(A1,255);
  analogWrite(A2,255);
  analogWrite(A3,255);

 }
 bool ok;
 int Fecho = ultra(4,5);
 int Secho = ultra(6,7);
 int i = 0;
 delay(50);
    ok = false;
    while((!ok)&(i<2)){
      radio.stopListening();
      i++;
      ok = radio.write("F", sizeof(char) );
      Serial.println("F");
      radio.startListening();
    }
    i = 0;
    delay(50);
    ok = false;
    while((!ok)&(i<2)){
      radio.stopListening();
      i++;
      ok = radio.write( &Fecho, sizeof(int) );
      Serial.println(Fecho);
    }
    i = 0;
    delay(50);
    ok = false;
    while((!ok)&(i<2)){
      i++;
      ok = radio.write("S", sizeof(char) );
      Serial.println("S");
    }
    i = 0;
    delay(50);
    ok = false;
    while((!ok)&(i<2)){
      i++;
      ok = radio.write( &Secho, sizeof(int) );
      Serial.println(Secho);
    }
    

} 


