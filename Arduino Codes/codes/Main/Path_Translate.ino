void pathtranslate()
{
  if (xPos < xDestination)
  {
    Moveflag = 1;
  }
  else if (xPos > xDestination)
  {
    Moveflag = 2;
  }
  else if (yPos < yDestination)
  {
    Moveflag = 3;
  }
  else if (yPos > yDestination)
  {
    Moveflag = 4;
  }
  else
  {
    CCflag = 1;
    Moveflag = 0;
    motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,0);

  }
}

