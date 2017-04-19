void coordinate_call()
{
  unsigned long int timeTemp;
  while((rd != 0xFFF0+CarName)){
  timeMove = millis();
  rd = radio_recieve();
  Serial.println("looking for poll");
  while(rd!=0xADD0+CarName)
  {
      rd = radio_recieve();
  }
  Serial.println("Got Poll");
  delay(50);
  radio_transmit(2);
  timeMain = millis();
  while((rd != 0xFFF0+CarName)&&((millis()-timeMain)<4000)){
  ACK = 0;
  Serial.println("Sending Preamble");
  timeTemp = millis();
  while((ACK!=2)&&(millis() - timeMain)<1000){
  radio_transmit(0xFFF0+CarName);    //Coordinate preamble
  delay(100);
  radio_transmit(CarName);
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
  }
  }
  }
 coordinate_print();

}

