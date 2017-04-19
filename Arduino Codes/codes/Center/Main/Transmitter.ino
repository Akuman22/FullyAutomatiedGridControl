
void radio_transmit(unsigned long c)
{
    unsigned long int tim = millis();
    radio.stopListening();
    bool ok = false;
    int i = 0;
    while((!ok)&((millis())-tim)<1000){
      ok = radio.write(&c, sizeof(unsigned long));
      i+=1;
    }
 delay(20);
 radio.startListening();
}

