#include <math.h>

/* !IMPORTANT!
 * DEFAULT VARIABLE DEFINITIONS
 * CHANGE ONLY IF YOU KNOW WHAT YOU ARE DOING
 * RANDOMLY CHANGING THESE VALUES COULD BREAK THE FUNCTIONALITY OF THE ROBOT
 */

const int numServo = 18;
int servoPins[numServo] = {2,3,4,5,6,7,8,9,10,14,29,30,20,21,22,35,36,37};
double currentX[6];
double currentY[6];
double currentZ[6];
double currentAnglePitch = 0.0;
double currentAngleRoll = 0.0;

int c_nul_x = 0;
int c_nul_y = 50;
int c_nul_z = -50;

int middle = 5;
int currentServoNum;

int min_interval = 595;
int max_interval = 3138;
int bottom_interval[6] = {1870,1800,1835,2000,1790,1870};
int middle_interval[6] = {560,650,595,600,590,550};
int top_interval[6] = {665,595,623,700,665,635};

String incString;

//PREDEFINED FUNCTIONS BELOW

/* moveLegZTo(double z, int legNum)
 * Raises the specified leg to a height
 * z - specifies height of the leg
 * legNum - number of the leg you want to move(0-5)
 */

void moveLegZTo(double z, int legNum){
  moveLegToPos(currentX[legNum], currentY[legNum], z, legNum);
}

/* robotStand()
 * Make the robot stand to predetermined height
 */

void robotStand(){
  for(int i=0;i<6;i++){
    moveLegToPos(c_nul_x,c_nul_y,c_nul_z,i);
  }
}

/* robotToZ(double z)
 * Raise the whole robot to set z level
 * z - specifies z level(in positive scale)
 */

void robotToZ(double z){
  for(int i=0;i<6;i++){
    moveLegToPos(currentX[i],currentY[i],-z,i);
  }
}

struct Point{
  double x;
  double y;
};

/*  gesture_wave()
 *  Makes the robot do a wave
 */

void gesture_wave(){
  double tempX[6];
  double tempY[6];
  double tempZ[6];
  for(int i=0;i<6;i++){
    tempX[i] = currentX[i];
    tempY[i] = currentY[i];
    tempZ[i] = currentZ[i];
  }
  angleBaseOverTime(15,0,-70, 1000);
  delay(200);
  analogWrite(servoPins[1], radToSteps(0, 1));
  analogWrite(servoPins[4], radToSteps(0, 4));
  delay(200);
  for(int r=0;r<3;r++){
    for(double i=0;i<PI/2;i+=PI/25){
      analogWrite(servoPins[2], radToSteps(i, 2));
      analogWrite(servoPins[5], radToSteps(i, 5));
      delay(50);
    }
    for(double i=PI/2;i>0;i-=PI/25){
      analogWrite(servoPins[2], radToSteps(i, 2));
      analogWrite(servoPins[5], radToSteps(i, 5));
      delay(50);
    }
  }
  delay(200);
  moveLegToPos(tempX[0],tempY[0],tempZ[0],0);
  moveLegToPos(tempX[1],tempY[1],tempZ[1],1);
  delay(50);
  angleBaseOverTime(0,0,-70, 500);
}

/*  angleBaseOverTime(double n_pitch, double n_roll, double n_mid_height, double n_time)
 *  Move base to desired angle over a set period of time(ms)
 *  n_pitch - Desired pitch angle in degrees
 *  n_roll - Desired roll angle in degrees
 *  n_mid_height - Specifies the height of the robot in the middle
 *  n_time - Specifies the desired time to do the action(ms)
 */

void angleBaseOverTime(double n_pitch, double n_roll, double n_mid_height, double n_time){
  double temp_pitch = currentAnglePitch;
  double temp_roll = currentAngleRoll;
  double pitch_c = temp_pitch;
  double roll_c = temp_roll;
  double res = 100.0;

  double pitch_step = -(temp_pitch-n_pitch) / res;
  double roll_step = -(temp_roll-n_roll) / res;

  for(int i=0;i<res;i++){
    angleBase(pitch_c,roll_c,n_mid_height);
    roll_c+=roll_step;
    pitch_c+=pitch_step;
    delay(n_time/res);
  }
}

/*  angleBase(double n_angle, double n_mid_height)
 *  Set the angle of the base that you want the robot to take.
 *  n_angle - specifies the angle you want the base to go at
 *  n_mid_height - specifies the height of the robot in the center
 */

void angleBase(double n_pitch, double n_roll, double n_mid_height){
  currentAnglePitch = n_pitch;  
  currentAngleRoll = n_roll;

  double n_pitch_rad = getRadFromAngle(n_pitch);
  double n_roll_rad = getRadFromAngle(n_roll);
  int d_pitch = 120;
  int d_roll_mid = 55;
  int d_roll_out = 42;
  double z_pitch = sin(n_pitch_rad) * d_pitch;
  double z_roll_mid = sin(n_roll_rad) * d_roll_mid;
  double z_roll_out = sin(n_roll_rad) * d_roll_out;
  
  moveLegZTo(n_mid_height + z_pitch + z_roll_out,0);
  moveLegZTo(n_mid_height + z_pitch - z_roll_out,1);
  moveLegZTo(n_mid_height + z_roll_mid ,2);
  moveLegZTo(n_mid_height - z_roll_mid ,3);
  moveLegZTo(n_mid_height - z_pitch + z_roll_out ,4);
  moveLegZTo(n_mid_height - z_pitch - z_roll_out,5);
}

/* turnRobot(String side, double n_stride, int n_delay)
 * Turn the robot(not really precise nor well made, semi-works);
 * side - define if you want the robot to turn to the right or to the left
 * n_stride - define the size of the step the robot takes, dictates speed
 * n_delay - the delay between individual movements of the robot, dictates speed
 */

void turnRobot(String side, double n_stride, int n_delay){
  if(side == "left"){
    struct Point start_point;
    start_point = getLineStartPoint(0, n_stride);
    double x1 = c_nul_x + start_point.x;
    double y1 = c_nul_y + start_point.y;
    double x2 = c_nul_x - start_point.x;
    double y2 = c_nul_y - start_point.y;
    
    x1 = -x1;
    x2 = -x2;
    moveLegToPos(x1,y1,-50,1);
    moveLegToPos(x1,y1,-50,2);
    moveLegToPos(x1,y1,-50,5);
    delay(round(n_delay / 4));
    moveLegToPos(x1,y1,-30,0);
    moveLegToPos(x1,y1,-30,3);
    moveLegToPos(x1,y1,-30,4);
    delay(round(n_delay * (3/4) ));

    moveLegToPos(x2,y2,-50,1);
    moveLegToPos(x2,y2,-50,2);
    moveLegToPos(x2,y2,-50,5);
    delay(round(n_delay / 4));
    moveLegToPos(x2,y2,-30,0);
    moveLegToPos(x2,y2,-30,3);
    moveLegToPos(x2,y2,-30,4);
    delay(round(n_delay * (3/4) ));
  
    moveLegToPos(x2,y2,-50,0);
    moveLegToPos(x2,y2,-50,3);
    moveLegToPos(x2,y2,-50,4);
    delay(round(n_delay / 4));
    moveLegToPos(x2,y2,-30,1);
    moveLegToPos(x2,y2,-30,2);
    moveLegToPos(x2,y2,-30,5);
    delay(round(n_delay * (3/4) ));

    moveLegToPos(x1,y1,-50,0);
    moveLegToPos(x1,y1,-50,3);
    moveLegToPos(x1,y1,-50,4);
    delay(round(n_delay / 4));
    moveLegToPos(x1,y1,-30,1);
    moveLegToPos(x1,y1,-30,2);
    moveLegToPos(x1,y1,-30,5);
    delay(round(n_delay * (3/4) ));
  } else{
    struct Point start_point;
    start_point = getLineStartPoint(180, n_stride);
    double x1 = c_nul_x + start_point.x;
    double y1 = c_nul_y + start_point.y;
    double x2 = c_nul_x - start_point.x;
    double y2 = c_nul_y - start_point.y;
    
    x1 = -x1;
    x2 = -x2;
    moveLegToPos(x1,y1,-50,1);
    moveLegToPos(x1,y1,-50,2);
    moveLegToPos(x1,y1,-50,5);
    delay(round(n_delay / 4));
    moveLegToPos(x1,y1,-30,0);
    moveLegToPos(x1,y1,-30,3);
    moveLegToPos(x1,y1,-30,4);
    delay(round(n_delay * (3/4) ));

    moveLegToPos(x2,y2,-50,1);
    moveLegToPos(x2,y2,-50,2);
    moveLegToPos(x2,y2,-50,5);
    delay(round(n_delay / 4));
    moveLegToPos(x2,y2,-30,0);
    moveLegToPos(x2,y2,-30,3);
    moveLegToPos(x2,y2,-30,4);
    delay(round(n_delay * (3/4) ));
  
    moveLegToPos(x2,y2,-50,0);
    moveLegToPos(x2,y2,-50,3);
    moveLegToPos(x2,y2,-50,4);
    delay(round(n_delay / 4));
    moveLegToPos(x2,y2,-30,1);
    moveLegToPos(x2,y2,-30,2);
    moveLegToPos(x2,y2,-30,5);
    delay(round(n_delay * (3/4) ));

    moveLegToPos(x1,y1,-50,0);
    moveLegToPos(x1,y1,-50,3);
    moveLegToPos(x1,y1,-50,4);
    delay(round(n_delay / 4));
    moveLegToPos(x1,y1,-30,1);
    moveLegToPos(x1,y1,-30,2);
    moveLegToPos(x1,y1,-30,5);
    delay(round(n_delay * (3/4) ));
  }
  
}

/* moveAtAngle(String move_object, int n_object, double n_angle, double n_stride, int n_delay)
 * Move a leg, leg set or the robot at an desired angle.
 * move_object - leg, leg_set, robot
 * n_object - if move_object set to leg, defines leg number; if move_object set to leg_set defines leg set(1 or 2); no use in robot case, set to 0
 * n_angle - angle at which to move the robot. 0 degrees is forward, 180 is backward
 * n_stride - length of each step on each leg, lower stride means slower movement
 * n_delay - delay between individual motions, lower delay means faster walking
 */
void moveAtAngle(String move_object, int n_object, double n_angle, double n_stride, int n_delay){
  struct Point start_point;
  start_point = getLineStartPoint(n_angle, n_stride);
  double x1 = c_nul_x + start_point.x;
  double y1 = c_nul_y + start_point.y;
  double x2 = c_nul_x - start_point.x;
  double y2 = c_nul_y - start_point.y;

  if(move_object == "leg"){
    moveLegToPos(x1,y1,currentZ[n_object],n_object);
    delay(n_delay);
    moveLegToPos(x2,y2,currentZ[n_object],n_object);
    delay(n_delay);
  } else if(move_object == "leg_set"){
    if(n_object == 1){
      //Move Leg set 1
      //Leg set 1 are legs 0, 3, 4
      moveLegToPos(x1,y1,currentZ[0],0);
      moveLegToPos(-x1,y1,currentZ[3],3);
      moveLegToPos(x1,y1,currentZ[4],4);
      delay(n_delay);
      moveLegToPos(x2,y2,currentZ[0],0);
      moveLegToPos(-x2,y2,currentZ[3],3);
      moveLegToPos(x2,y2,currentZ[4],4);
      delay(n_delay);
    } else if(n_object == 2){
      //Move Leg set 2
      //Leg set 2 are legs 1 , 2, 5
      moveLegToPos(x1,y1,currentZ[1],1);
      moveLegToPos(-x1,y1,currentZ[2],2);
      moveLegToPos(x1,y1,currentZ[5],5);
      delay(n_delay);
      moveLegToPos(x2,y2,currentZ[1],1);
      moveLegToPos(-x2,y2,currentZ[2],2);
      moveLegToPos(x2,y2,currentZ[5],5);
      delay(n_delay);
    }
  } else if(move_object == "robot"){
    //Moves the whole robot at the angle specified.
      moveLegToPos(-x1,y1,-50,1);
      moveLegToPos(x1,y1,-50,2);
      moveLegToPos(-x1,y1,-50,5);
      delay(round(n_delay / 2));
      moveLegToPos(-x1,y1,-30,0);
      moveLegToPos(x1,y1,-30,3);
      moveLegToPos(-x1,y1,-30,4);
      delay(round(n_delay * (3/4) ));

      moveLegToPos(-x2,y2,-50,1);
      moveLegToPos(x2,y2,-50,2);
      moveLegToPos(-x2,y2,-50,5);
      delay(round(n_delay / 4));
      moveLegToPos(-x2,y2,-30,0);
      moveLegToPos(x2,y2,-30,3);
      moveLegToPos(-x2,y2,-30,4);
      delay(round(n_delay * (3/4) ));
      
      moveLegToPos(-x2,y2,-50,0);
      moveLegToPos(x2,y2,-50,3);
      moveLegToPos(-x2,y2,-50,4);
      delay(round(n_delay / 2));
      moveLegToPos(-x2,y2,-30,1);
      moveLegToPos(x2,y2,-30,2);
      moveLegToPos(-x2,y2,-30,5);
      delay(round(n_delay * (3/4) ));

      moveLegToPos(-x1,y1,-50,0);
      moveLegToPos(x1,y1,-50,3);
      moveLegToPos(-x1,y1,-50,4);
      delay(round(n_delay / 4));
      moveLegToPos(-x1,y1,-30,1);
      moveLegToPos(x1,y1,-30,2);
      moveLegToPos(-x1,y1,-30,5);
      delay(round(n_delay * (3/4) ));
  }
}

struct Point getLineStartPoint(double n_angle, double n_stride){
  double radian = getRadFromAngle(n_angle);
  struct Point t_point;
  t_point.x = cos(radian) * (n_stride/2);
  t_point.y = sin(radian) * (n_stride/2);
  return t_point;
}

void initializeRobot(){
  currentAnglePitch = 0.0;
  currentAngleRoll = 0.0;

  for(int i=0;i<6;i++){
    currentX[i] = c_nul_x;
    currentY[i] = c_nul_y;
    currentZ[i] = c_nul_z;
  }
  
  analogWriteResolution(12);
  for(int i=0;i<numServo;i++){
    pinMode(servoPins[i], OUTPUT);
    analogWriteFrequency(servoPins[i], 300);
  }
  
  Serial.begin(9600);
  Serial.println("Starting serial link.");
 
  Serial.println("Servos initialized!");

  robotStand();
}
