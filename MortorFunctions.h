/* //////////////////////////////////////////////////////////////*
 * *******LINE FOLLOWER ROBOT USING PID ALGORITHM*****************
 * 
 * Authur: Thilina Satoru                                        *
 * NIBM:   Higher Diploma - Robotic Application Development      *
 * Date:   12/24/2021                                            *
 *///////////////////////////////////////////////////////////////*

void M_drive(int mB, int mC){ // mortor forward, variable Left&Right speeds
  analogWrite(INA_M1, 0);  // left backwards
  analogWrite(INB_M1, mB); // left forwards
  analogWrite(INC_M2, mC); // right forwards
  analogWrite(IND_M2, 0);  // right backwards
}
void M_stop(){
  analogWrite(INA_M1, 0);  // left backwards
  analogWrite(INB_M1, 0);  // left forwards
  analogWrite(INC_M2, 0);  // right forwards
  analogWrite(IND_M2, 0);  // right backwards
  delay(200);
}
void M_back(){
  analogWrite(INA_M1, 100);  // left backwards
  analogWrite(INB_M1, 0);    // left forwards
  analogWrite(INC_M2, 0);    // right forwards
  analogWrite(IND_M2, 100);  // right backwards
}
void M_turn_Left180(){ // 180 turn
  analogWrite(INA_M1, 130); // left backwards
  analogWrite(INB_M1, 0);   // left forwards
  analogWrite(INC_M2, 150); // right forwards
  analogWrite(IND_M2, 0);   // right backwards
}
void M_turn_Right180(){ // 180 turn
  analogWrite(INA_M1, 0); // left backwards
  analogWrite(INB_M1, 150);   // left forwards
  analogWrite(INC_M2, 0); // right forwards
  analogWrite(IND_M2, 130);   // right backwards
}


void M_turn_Left90(){ // 180 turn
  analogWrite(INA_M1, 0); // left backwards
  analogWrite(INB_M1, 50);   // left forwards
  analogWrite(INC_M2, 100); // right forwards
  analogWrite(IND_M2, 0);   // right backwards
}
void M_turn_Right90(){ // 180 turn
  analogWrite(INA_M1, 0); // left backwards
  analogWrite(INB_M1, 100);   // left forwards
  analogWrite(INC_M2, 50); // right forwards
  analogWrite(IND_M2, 0);   // right backwards
}
