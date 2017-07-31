void posupdate()
{
  if ((Moveflag != 9)&&(Moveflag != 0)){
    if(Posflag == 1){
      xPos+=1;
      timeMove = millis() - updrem;
    }
    else if(Posflag == 2){
    xPos -=1;
    timeMove = millis() - updrem;
    }
    else if(Posflag == 3){
      yPos+=1;
      timeMove = millis() - updrem;
    }
    else if(Posflag == 4){
       yPos -=1;
    timeMove = millis() - updrem;
    }
  }
}

