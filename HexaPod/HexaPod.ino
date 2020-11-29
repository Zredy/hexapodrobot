#include <math.h>

const int numServo = 18;
int servoPins[numServo] = {2,3,4,5,6,7,8,9,10,14,29,30,20,21,22,35,36,37};
double currentX[6];
double currentY[6];
double currentZ[6];

int c_nul_x = 0;
int c_nul_y = 80;
int c_nul_z = -50;

int middle = 900;
int currentServoNum;

int min_interval = 595;
int max_interval = 3138;
int bottom_interval[6] = {1870,1800,1835,2000,1790,1870};
int middle_interval[6] = {560,650,595,600,590,550};
int top_interval[6] = {665,595,623,700,665,635};

String incString;

void setup(){
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
}

void loop(){
  
  while(Serial.available()){
    char c = Serial.read();
    incString += c;
    delay(2);
  }

  if(incString.length() > 0){
    Serial.println(incString);
    int n = incString.toInt();
    //Write to servo
    middle = n;
    incString = "";
  }
/* moveAtAngle(String move_object, int n_object, double n_angle, double n_stride, int n_delay)
 * move_object - leg, leg_set, robot
 * n_object - if move_object set to leg, defines leg number; if move_object set to leg_set defines leg set(1 or 2); no use in robot case, set to 0
 * n_angle - angle at which to move the robot. 0 degrees is forward, 180 is backward
 * n_stride - length of each step on each leg, lower stride means slower movement
 * n_delay - delay between individual motions, lower delay means faster walking
 */

  moveAtAngle("robot", 0, -90, 40, 1000);
 /* moveAtAngle("robot", 0, 180, 40, 400);
  delay(500);*/
  
}
