int ir(int inPin)
{
  pinMode(inPin, INPUT);
  if(inPin == HIGH)
  {
    return(1);
  }
  if(inPin == LOW)
  {
    return(0);
  }
}

