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
}

