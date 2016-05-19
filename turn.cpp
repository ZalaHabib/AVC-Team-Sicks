int turn(int error){
  //Left wheel turns backwards
  int left_wheel=0;
  int right_wheel=0;
  if(white<1){
    if(prev_error>0)
      //If path was lost and was last to the left, turn left sharply
      left_wheel=200;
      right_wheel=200;
    }
    else{
      //If path was lost and was last to right, turn right sharply
      left_wheel=-200;
      right_wheel=-200;
    }
  }
  else{
    if(error>0){
      left_wheel=((-error/160)*120)-40;
      right_wheel=((-error/160)*350)+40;
    }
    else{
      left_wheel=((-error/160)*350)-40;
      right_wheel=((-error/160)*120)+40;
    }
  set_motor(1,left_wheel);
  set_motor(2,right_wheel);
return 0;}
