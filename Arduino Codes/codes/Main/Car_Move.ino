//Posflag -> 1 --> facing towards +x, 2 --> facing towards -x, 3 --> facing towards +y, 4 --> facing towards -y
//Moveflag -> 1 --> move towards +x, 2 --> move towards -x, 3 --> move towards +y, 4 --> move towards -y
void carmove()
{
  if(Moveflag == 1){
      if(Posflag == 1){
         motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1); // move forward
         }
         if(Posflag == 2){
            timeMovefunc = millis();
            while(millis()-timeMovefunc < 1000){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,2); // turn around
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 1;
         }
         if(Posflag == 3){
            timeMovefunc = millis();
            while(millis()-timeMovefunc < 500){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,2); // turn right
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 1;
         }
         if(Posflag == 4){
            timeMovefunc = millis();
            while(millis()-timeMovefunc < 500){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,-2); // turn left
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 1;
         }        
     }
    if(Moveflag == 2){
         if(Posflag == 1){
         timeMovefunc = millis();
            while(millis()-timeMovefunc < 1000){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,2); // turn around
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 2;
         }
         if(Posflag == 2){
           motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,2);      // move forward
         }
         if(Posflag == 3){
            timeMovefunc = millis();
            while(millis()-timeMovefunc < 500){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,-2); // turn left
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 2;
         }
         if(Posflag == 4){
            timeMovefunc = millis();
            while(millis()-timeMovefunc < 500){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,2);  // turn right
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 2;          
         }
      }
  if(Moveflag == 3){
        if(Posflag == 1){
          timeMovefunc = millis();
          while(millis()-timeMovefunc < 500){
              motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,-2); // turn left
          }
          motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
          Posflag = 3;
         }
         if(Posflag == 2){
            timeMovefunc = millis();
            while(millis()-timeMovefunc < 500){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,2); // turn right
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 3;
         }
         if(Posflag == 3){
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1); // move forward
         }
         if(Posflag == 4){
            timeMovefunc = millis();
            while(millis()-timeMovefunc < 1000){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,-2); // turn around
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 3;
         }        
     }
 if(Moveflag == 4){
        if(Posflag == 1){
          timeMovefunc = millis();
          while(millis()-timeMovefunc < 500){
              motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,2); // turn right
          }
          motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
          Posflag = 4;
         }
         if(Posflag == 2){
            timeMovefunc = millis();
            while(millis()-timeMovefunc < 500){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,-2); // turn left
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 4;
         }
         if(Posflag == 3){
            timeMovefunc = millis();
            while(millis()-timeMovefunc < 1000){
                motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,-2); // turn around
            }
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1);
            Posflag = 4;
         }
         if(Posflag == 4){
            motor(m1PinRF,m1PinRB,m1PinLF,m1PinLB,1); // move forward
         }        
     }
}
