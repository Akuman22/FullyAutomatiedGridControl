void posupdate()
{
  if (Moveflag != 9){
    if(Posflag == 1){
      xPos+=upd;
      timeMove = millis() - updrem;
    }
    else if(Posflag == 2){
    xPos -=upd;
    timeMove = millis() - updrem;
    }
    else if(Posflag == 3){
      yPos+=upd;
      timeMove = millis() - updrem;
    }
    else if(Posflag == 4){
       yPos -=upd;
    timeMove = millis() - updrem;
    }
  }
}
