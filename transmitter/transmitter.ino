
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xABCDABCD71LL };

typedef enum { role_ping_out = 1, role_pong_back } role_e;

const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

role_e role = role_pong_back;

void setup(void)
{

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

}

void loop(void)
{  
  radio.startListening();
  bool ok = false;
  while(!Serial.available())
  { 
    if ( radio.available() )
    {
      unsigned long inp;
      bool done = false;
      while (!done)
      {
        done = radio.read( &inp, sizeof(unsigned long) );
       }
       if (isalpha(inp))
        {
            Serial.println(char(inp));
        }
       else
        {
             Serial.println(inp);
        }
    }
  }
      if ( radio.available() )
    {
      char inp;
      bool done = false;
      int j = 0;
      while ((!done)&(j<5))
      {
        j++;
        done = radio.read( &inp, sizeof(char) );
       }
       Serial.println(inp);
    }
    unsigned long t;
    char a = Serial.read();
    if (a == 'w')
      t = 1;
    if (a == 'a')
      t = 2;
    if (a == 's')
      t = 3;
    if (a == 'd')
      t = 4;    
    Serial.println(t);
    delay(50);
    radio.stopListening();
    int i = 0;
    while((!ok)&(i<15)){
    Serial.println(t);
    i++;
    ok = radio.write( &t, sizeof(unsigned long) );
}
   radio.startListening();

}

// vim:cin:ai:sts=2 sw=2 ft=cpp
