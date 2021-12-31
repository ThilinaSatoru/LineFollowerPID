/* //////////////////////////////////////////////////////////////*
 * *******LINE FOLLOWER ROBOT USING PID ALGORITHM*****************
 * 
 * Authur: Thilina Satoru                                        *
 * NIBM:   Higher Diploma - Robotic Application Development      *
 * Date:   12/24/2021                                            *
 *///////////////////////////////////////////////////////////////*

void IR_debug(){ // monitor data
  Serial.print("Error:");
  Serial.print(error);
  
  Serial.print(" --");
  for(int i; i < 8; i++){ Serial.print(reading[i]); }
  Serial.print("-- ");
  
  Serial.print(" sum:");
  Serial.print(sum);
  
  Serial.print(" LeftSpeed:");Serial.print(LeftSpeed);
  Serial.print(" RightSpeed:");Serial.print(RightSpeed);
  
  Serial.println();
}
