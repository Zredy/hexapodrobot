#include <math.h>

//Variable definitions
/*
int c_nul_x = 0;
int c_nul_y = 80;
int c_nul_z = -50;
*/

void moveLegZTo(double z, int legNum){
  moveLegToPos(currentX[legNum], currentY[legNum], z, legNum);
}

void robotStand(){
  for(int i=0;i<6;i++){
    moveLegToPos(0,80,-50,i);
  }
}

void robotToZ(double z){
  for(int i=0;i<6;i++){
    moveLegToPos(currentX[i],currentY[i],z,i);
  }
}

void moveBackward(double strideLength){
  //Spustanje noga 1,2,5
  moveLegToPos(strideLength, 80, -50, 1);
  moveLegToPos(-strideLength, 80, -50, 2);
  moveLegToPos(strideLength, 80, -50, 5);
  delay(50);
  //Dizanje noga 0,3,4
  moveLegToPos(strideLength, 80, -30, 0);
  moveLegToPos(-strideLength, 80, -30, 3);
  moveLegToPos(strideLength, 80, -30, 4);
  delay(200);
  moveLegToPos(-strideLength, 80, -50, 1);
  moveLegToPos(strideLength, 80, -50, 2);
  moveLegToPos(-strideLength, 80, -50, 5);
  
  moveLegToPos(-strideLength, 80, -30, 0);
  moveLegToPos(strideLength, 80, -30, 3);
  moveLegToPos(-strideLength, 80, -30, 4);
  delay(200);
  //Spustanje noga 0,3,4
  moveLegToPos(-strideLength, 80, -50, 0);
  moveLegToPos(strideLength, 80, -50, 3);
  moveLegToPos(-strideLength, 80, -50, 4);
  delay(50);
  //Dizanje noga 1,2,5
  moveLegToPos(-strideLength, 80, -30, 1);
  moveLegToPos(strideLength, 80, -30, 2);
  moveLegToPos(-strideLength, 80, -30, 5);
  delay(200);
  moveLegToPos(strideLength, 80, -50, 0);
  moveLegToPos(-strideLength, 80, -50, 3);
  moveLegToPos(strideLength, 80, -50, 4);

  moveLegToPos(strideLength, 80, -30, 1);
  moveLegToPos(-strideLength, 80, -30, 2);
  moveLegToPos(strideLength, 80, -30, 5);
  delay(200);
}

void moveForward(double strideLength){
  //Spustanje noga 1,2,5
  moveLegToPos(-strideLength, 80, -50, 1);
  moveLegToPos(strideLength, 80, -50, 2);
  moveLegToPos(-strideLength, 80, -50, 5);
  delay(50);
  //Dizanje noga 0,3,4
  moveLegToPos(-strideLength, 80, -30, 0);
  moveLegToPos(strideLength, 80, -30, 3);
  moveLegToPos(-strideLength, 80, -30, 4);
  delay(200);
  moveLegToPos(strideLength, 80, -50, 1);
  moveLegToPos(-strideLength, 80, -50, 2);
  moveLegToPos(strideLength, 80, -50, 5);
  
  moveLegToPos(strideLength, 80, -30, 0);
  moveLegToPos(-strideLength, 80, -30, 3);
  moveLegToPos(strideLength, 80, -30, 4);
  delay(200);
  //Spustanje noga 0,3,4
  moveLegToPos(strideLength, 80, -50, 0);
  moveLegToPos(-strideLength, 80, -50, 3);
  moveLegToPos(strideLength, 80, -50, 4);
  delay(50);
  //Dizanje noga 1,2,5
  moveLegToPos(strideLength, 80, -30, 1);
  moveLegToPos(-strideLength, 80, -30, 2);
  moveLegToPos(strideLength, 80, -30, 5);
  delay(200);
  moveLegToPos(-strideLength, 80, -50, 0);
  moveLegToPos(strideLength, 80, -50, 3);
  moveLegToPos(-strideLength, 80, -50, 4);

  moveLegToPos(-strideLength, 80, -30, 1);
  moveLegToPos(strideLength, 80, -30, 2);
  moveLegToPos(-strideLength, 80, -30, 5);
  delay(200);
}

struct Point{
  double x;
  double y;
};

void moveAtAngle(String move_object, int n_object, double n_angle, double n_stride, int n_delay){
  struct Point start_point;
  start_point = getLineStartPoint(n_angle, n_stride);
  double x1 = c_nul_x + start_point.x;
  double y1 = c_nul_y + start_point.y;
  double x2 = c_nul_x - start_point.x;
  double y2 = c_nul_y - start_point.y;

  Serial.print(x1);
  Serial.print(" - ");
  Serial.print(y1);
  Serial.print(" - ");
  Serial.print(x2);
  Serial.print(" - ");
  Serial.print(y2);
  Serial.print("\n");

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
