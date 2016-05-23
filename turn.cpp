int turn(double error){
  int left_wheel=0;
  int right_wheel=0;
  if(white<1){
    if(prev_error>0)
      //If path was lost and was last to the left, turn left sharply
      left_wheel=-50;
      right_wheel=50;
    }
    else{
      //If path was lost and was last to right, turn right sharply
      left_wheel=50;
      right_wheel=-50;
    }
  }
  else{
    if(error>0){
      left_wheel=((error/160)*50)+50;
      right_wheel=((-error/160)*300)+50;
    }
    else{
      left_wheel=((error/160)*300)+50;
      right_wheel=((-error/160)*50)+50;
    }
  set_motor(1,left_wheel);
  set_motor(2,right_wheel);
return 0;}
