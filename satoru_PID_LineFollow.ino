/* //////////////////////////////////////////////////////////////*
 * *******LINE FOLLOWER BOT USING PID ALGORITHM*******************
 * 
 * Authur: Thilina Satoru                                        *
 * NIBM:   Higher Diploma - Robotic Application Development      *
 * Date:   12/24/2021                                            *
 *///////////////////////////////////////////////////////////////*
#include "configuration.h"

// Flags for modes //
#define STOPPED 0
#define ON_LINE 1
#define OFF_LINE 2
#define TURN_LEFT 3
#define TURN_RIGHT 4
#define CROSS 5

bool reading[sInputs]; //Digital readings of sensors into array 
int coefficient[sInputs] = {-4000, -3000, -2000, -1000, 1000, 2000, 3000, 4000}; // Coefficient of error values    (-4000 is to Leftmost sensor)

float error = 0;       //difference between the desired final output, => ("error=0")   AND    the actual one, => ("error = coeficient*sensor reading") 
float PID_output = 0;  // calculated PID value/the difference

short mode;     // mode of the sensor postion logic
int sum;        // sum of digital sensor array. 'if all black sum=8'
bool isGoal;
#include "BebuggFunctions.h"
#include "MortorFunctions.h"

void setup() { /////////////////////////////////////////  START SETUP  ///////////////////////////////////////////////////////////////////////////////////////////
   isGoal = false;
  // set pins as output/input
  pinMode(INA_M1, OUTPUT);
  pinMode(INB_M1, OUTPUT);
  pinMode(INC_M2, OUTPUT);
  pinMode(IND_M2, OUTPUT);
  
  Serial.begin(115200); // serial monitor
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END SETUP ////////////////////////////////

void loop() { //////////////////////////////////////////  START LOOP   ///////////////////////////////////////////////////////////////////////////////////////////

  if(!isGoal){ // destination not arrived
    IR_read();
    checkReading();
    IR_debug();
  
    switch(mode){
      
      case STOPPED:     
        M_stop();
        break;
        
      case ON_LINE:
        Serial.print("+++ON LiNE++");
        calculatePID();
        motorPIDcontrol();
        break;
        
      case OFF_LINE:
        M_turn_Left180();
        break;
        
      case TURN_RIGHT:
        delay(1000);
        while(sum == 0 ){
          Serial.print("+++ while R +++");
          M_turn_Right90();
          
          IR_read();
        }
        break;
        
      case TURN_LEFT:
        delay(1000);
        while(sum == 0){
          Serial.print("+++ while L+++");
          M_turn_Left90();
          
          IR_read();
        }
        break;
        
      case CROSS:
        doCross();
        break;
    }
  }
  else{
    // loop ended, destination arrived
  }
  
}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  END LOOP  //////////////////////////////

void IR_read(){
  sum = 0;
  error = 0;
                                                      // Through out whole sensor array,
  for(int i; i < sInputs; i++){
    reading[i] = digitalRead(sensorPins[i]) ;         // digital read, and put to sensor reading array
    error = error + ( reading[i]* coefficient[i] );   // calculate corresponding, 'sum of errors' for sensors which have "1".
    sum = sum + reading[i];                           // calculate how many 1's are detected in the reading
  }
}
void checkReading(){
  if(sum == 0){                              // if sum=0, all readings are '0'  and  all white 
    mode = OFF_LINE;
  }
  
  else if(sum < 4){
    mode = ON_LINE;
  }
  
  else if(sum > 2 && sum < 7){                          // if there are several lines detected as '1'
      //mode = ON_LINE;
      if(reading[0] == 1 && reading[1] == 1 && reading[2] == 1){
        mode = TURN_LEFT;
      }
      else if(sum < 4){
        mode = ON_LINE;
      }
      else if(reading[5] == 1 && reading[6] == 1 && reading[7] == 1){
        mode = TURN_RIGHT;
      }   
  }
  
  else if(sum == 8 || sum == 7){
    mode = CROSS;
  }
}
void calculatePID(){                   // PID error algorithm

  float PP = 0, II = 0, DD = 0;
  float previousError = 0, previousI = 0;
  float I = I + error;
  
  PP = Kp * error;                     //Kp*P    p = error
  II = Ki * I;                         //Ki*I    I = I + error
  DD = Kd * (error - previousError);   //Kd*D    d = error - previousError
  
  PID_output = (PP + II + DD) / 1000;  // devide by 1000, because coefficients are thousand values
  previousError = error;
  
  //Serial.print(PID_output);
}
void motorPIDcontrol(){ // Apply PID to motors
  LeftSpeed = initSpeed + PID_output;
  RightSpeed = initSpeed - PID_output;

/// limit:  max. mortor speed = 255  and  min. = 0
  if(LeftSpeed < 0)
    LeftSpeed = 0;
  if(LeftSpeed > maxSpeed)
    LeftSpeed = maxSpeed;
  if(RightSpeed < 0)
    RightSpeed = 0;
  if(RightSpeed > maxSpeed)
    RightSpeed = maxSpeed;
  
  M_drive(LeftSpeed,RightSpeed);
}

void doCross(){
  M_stop();
  delay(50);
  M_drive(100,100);
  delay(200);
  M_stop();

  IR_read();
  
  if(sum > 1 && sum < 4){
    M_turn_Left180();
    delay(1200);
  }
    
  else if(sum > 6){
    M_stop();
    isGoal = true;
  }
}
