#include <math.h>

void moveLegZTo(double z, int legNum){
  moveLegToPos(currentX[legNum], currentY[legNum], z, legNum);
}

void robotStand(){
  for(int i=0;i<6;i++){
    moveLegToPos(c_nul_x,c_nul_y,c_nul_z,i);
  }
}

void robotToZ(double z){
  for(int i=0;i<6;i++){
    moveLegToPos(currentX[i],currentY[i],z,i);
  }
}

struct Point{
  double x;
  double y;
};

void angleBase(double n_angle, double n_mid_height){
  //distance - 120mm
  double n_radian = getRadFromAngle(n_angle);
  int d_motorToMotor = 120;
  double z = sin(n_radian) * d_motorToMotor;
  Serial.println(z);
  moveLegZTo(n_mid_height-z,0);
  moveLegZTo(n_mid_height-z,1);
  moveLegZTo(n_mid_height,2);
  moveLegZTo(n_mid_height,3);
  moveLegZTo(n_mid_height+z,4);
  moveLegZTo(n_mid_height+z,5);
}

void turnRobot(String side, double n_stride, int n_delay){
  //side - left or right
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

void moveAtAngle(String move_object, int n_object, double n_angle, double n_stride, int n_delay){
  struct Point start_point;
  start_point = getLineStartPoint(n_angle, n_stride);
  double x1 = c_nul_x + start_point.x;
  double y1 = c_nul_y + start_point.y;
  double x2 = c_nul_x - start_point.x;
  double y2 = c_nul_y - start_point.y;
/*
  Serial.print(x1);
  Serial.print(" - ");
  Serial.print(y1);
  Serial.print(" - ");
  Serial.print(x2);
  Serial.print(" - ");
  Serial.print(y2);
  Serial.print("\n");
*/
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
      delay(round(n_delay / 4));
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
      delay(round(n_delay / 4));
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
