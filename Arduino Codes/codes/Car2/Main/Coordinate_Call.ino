void coordinate_call()
{
  unsigned long int timeTemp;
  while((rd <= 60000)){
      timeMove = millis();
      rd = radio_recieve();
      Serial.println("looking for poll");
      while(rd!=0xADD0+CarName)
      {
          rd = radio_recieve();
      }
      Serial.println("Got Poll");
      delay(50);
      radio_transmit(7);
      delay(200);
      timeMain = millis();
      while((rd != 0xFFF0+CarName)&&((millis()-timeMain)<2000)){
        ACK = 0;
        Serial.println("Sending Preamble");
        timeTemp = millis();
        while((ACK!=2)&&(millis() - timeTemp)<1000){
            radio_transmit(0xFFF0+CarName);    //Coordinate preamble
            delay(100);
            radio_transmit(CarName);
            delay(100);
            radio_transmit(xPos);
            delay(100);
            radio_transmit(yPos);
            ACK = radio_recieve();
         }
        if(ACK == 2){
            Serial.println("Received ACK");
            xDestination = radio_recieve();
            yDestination = radio_recieve();
            delay(50);
            radio_transmit(3);                 //Coordinate Acknowledgement
            radio_transmit(3);                 //Coordinate Acknowledgement
            radio_transmit(3);                 //Coordinate Acknowledgement
            rd = radio_recieve();
            
            Serial.print(xPos);
            Serial.print(" ");
            Serial.print(yPos);
            Serial.print(" ");
            Serial.print(xDestination);
            Serial.print(" ");
            Serial.println(yDestination);
            if ((((xPos - xDestination)*(xPos - xDestination))+
            ((yPos - yDestination)*(yPos - yDestination)))>9)
              {
                rd = 0;
              }
             Serial.println(rd);
          }
      }
  }
 coordinate_print();
 delay(50);
}

