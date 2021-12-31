/* //////////////////////////////////////////////////////////////*
 * *******LINE FOLLOWER ROBOT USING PID ALGORITHM*****************
 * 
 * Authur: Thilina Satoru                                        *
 * NIBM:   Higher Diploma - Robotic Application Development      *
 * Date:   12/24/2021                                            *
 *///////////////////////////////////////////////////////////////*


///// Mortor pins ///////////////////////
#define INA_M1 4  // left backwards  //// 
#define INB_M1 5  // left forward    ////
#define INC_M2 6  // right forward   ////
#define IND_M2 7  // right backwards ////
/////////////////////////////////////////


///////////////////////////////// sensor inputs and pins ///////////////////////////////////////////////////////////
const int sInputs = 8;                                       /// Number of Sensors                            //////
int sensorPins[sInputs] = {53, 51, 49, 47, 45, 43, 41, 39};  /// IR sensor array Digital pins in Arduino Mega //////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//// CHANGE THE CONSTANTS TO TUNE PID ///////////////////////////////////
const float Kp = 25.5;   ////// P => Proportional    present errors  ////
const float Ki = 0.1;    ////// I => Integral        past errors     ////
const float Kd = 9.0;    ////// D => Derivative      future errors   ////
/////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////// 
float maxSpeed = 230;           // max speed the mortor can handle /////                                         
float initSpeed = 190;          // initialSpeed < 255(max)         /////
float LeftSpeed = 0;            // Left mortor speed               /////
float RightSpeed = 0;           // Right Mortor Speed              /////
////////////////////////////////////////////////////////////////////////
