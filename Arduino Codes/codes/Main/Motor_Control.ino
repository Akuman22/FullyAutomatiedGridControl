void motor(int PinRF,int PinRB,int PinLF,int PinLB, int dir)
{
  if(dir == 2)
  {
    digitalWrite(PinLF,LOW);
    digitalWrite(PinRB,LOW);
  }
  if(dir == 1)
  {
    digitalWrite(PinLF,LOW);
    digitalWrite(PinRF,LOW);
  }
  if(dir == 0)
  {
    digitalWrite(PinLF,HIGH);
    digitalWrite(PinLB,HIGH);
    digitalWrite(PinRF,HIGH);
    digitalWrite(PinRB,HIGH);
  }
  if(dir == -1)
  {

    digitalWrite(PinLB,LOW);
    digitalWrite(PinRB,LOW);
  }
  if(dir == -2)
  {

    digitalWrite(PinRF,LOW);
    digitalWrite(PinLB,LOW);
  }
}

