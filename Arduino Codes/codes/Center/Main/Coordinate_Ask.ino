 void coordinate_ask()
 {
    timeMain = millis();
    while(((rd - carNameCall) != 0xFFF0)&&((millis()-timeMain)<4000))
    {
      rd = radio_recieve();
      delay(50);
      carNameCall = radio_recieve();
    }
    Serial.print(String(rd,HEX));
    Serial.print("#");
    if(rd - carNameCall == 0xFFF0)
    {
      delay(100);
      radio_transmit(2);
      timeMain = millis();
      ACK = 0;
      while((ACK == 0)&&((millis()-timeMain)<2000))
     {
      delay(50);
      radio_transmit(xDestination[i-1]);
      delay(50);
      radio_transmit(yDestination[i-1]);
      ACK = radio_recieve();        
     }
     if(ACK == 3)
     {
      radio_transmit(0xFFF0+carNameCall);
      radio_transmit(0xFFF0+carNameCall);
      radio_transmit(0xFFF0+carNameCall);
      radio_transmit(0xFFF0+carNameCall);
      radio_transmit(0xFFF0+carNameCall);
      
       }
      }
    }
