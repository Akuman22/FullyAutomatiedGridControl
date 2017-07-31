 void coordinate_ask()
 {
    timeMain = millis();
    rd = 0;
    while(((rd - i) != 0xFFF0)&&((millis()-timeMain)<4000))
    {
      rd = radio_recieve();
      delay(100);
      carNameCall = radio_recieve();
      delay(100);
      xPos[i] = radio_recieve();
      delay(100);
      yPos[i] = radio_recieve();
 //     Serial.print(String((rd - i),HEX));
 //     Serial.print("#");
      break;
      
    }
    Serial.print(String(rd,HEX));
    Serial.print(" ");
    Serial.print(xPos[i]);
    Serial.print(" ");
    Serial.print(yPos[i]);
    Serial.print(" ");
    Serial.print(carNameCall); 
    Serial.print("#");
    if((rd > 0))
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
      delay(50);
      radio_transmit(0xFFF0+carNameCall);
      radio_transmit(0xFFF0+carNameCall);
      radio_transmit(0xFFF0+carNameCall);
      radio_transmit(0xFFF0+carNameCall);
      radio_transmit(0xFFF0+carNameCall);
      Serial.print("ACK");
      Serial.print(i);
      Serial.print("XP");
      Serial.print(xPos[i]);
      Serial.print("YP");
      Serial.print(yPos[i]);
      Serial.print("#");
       }
      }
    }
