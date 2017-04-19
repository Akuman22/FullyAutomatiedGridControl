
unsigned long radio_recieve()
{
  unsigned long int tim = millis();
  unsigned long inp = 0;
  radio.startListening();
  bool done = false;
  while(!radio.available()){
    if((millis()-tim)>1000){
      return(0);
       }
      }
    while((!done)){
      done = radio.read( &inp, sizeof(unsigned long));
    }
 delay(20);
 return(inp);
}


