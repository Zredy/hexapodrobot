#include <math.h>

double radBase = 0.0;
double radMiddle = 0.0;
double radTop = 0.0;

int lenMiddle = 45; // Length from the B-M servo axis to the top servo axis
int lenTop = 122; // Length from the top servo axis to the tip of the leg
int lenBottom = 45; // Lenght from the bottom servo axis to the B-M servo axis
int robHeight = 50; // Height from the bottom robot plate to the top.



/*
 * Nul point:
 * Bottom of robot on the bottom servo axis (0,0)
 * At the top of servo is (0,0,50)
 * At the bottom-middle joint is (0,45,60)
 * midToTip is distance from B-M joint to the tip of the leg. 
 */

void moveLegToPos(double x, double y, double z, int n_leg){
  currentX[n_leg] = x;
  currentY[n_leg] = y;
  currentZ[n_leg] = z;
  
  double midToTip = 0.0;
  double radTemp1 = 0.0;
  double radTemp2 = 0.0;
  calcBottomAngle(x,y);
  double distToTip = sqrt(pow(x,2) + pow(y,2));
  Serial.println(distToTip);
  double distToTipSub = distToTip-lenBottom;
  Serial.println(distToTipSub);
//  Serial.println((abs(z) + 60 ) * (abs(z) / z));

  if(z>=0){
    if(z+60 > (lenTop+lenMiddle)){
      z = 80;
    }
    midToTip = sqrt(pow( distToTipSub , 2 ) + pow( ( abs(z) + 60 ) , 2 ));
  }
  if(z<0){
    if(abs(z-60) > (lenTop+lenMiddle)){
      z = -80;
    }
    midToTip = sqrt(pow( (distToTipSub) , 2 ) + pow( ( z - 60 ) , 2 ));
  }
  
  
  Serial.println(midToTip);
  if(sqrt(pow(lenTop,2) + pow(lenMiddle,2)) == midToTip){
    radTop = PI/4;
  //  radTemp1 = atan( lenTop/lenMiddle );
  } else {
    radTop = acos((pow(lenMiddle,2) + pow(lenTop,2) - pow(midToTip,2)) / (2*lenMiddle*lenTop));
   // radTemp1 = asin( (lenTop * sin(radTop)) / midToTip);
  }

  radTemp1 = acos(( pow(lenMiddle,2) + pow(midToTip,2) - pow(lenTop,2) ) / (2*lenMiddle*midToTip));
//  Serial.println(sqrt(pow(lenTop,2) + pow(lenMiddle,2)));
//  Serial.println(radTop);
  
  radTemp2 = atan( distToTipSub / (abs(z) + 60 ));
  radMiddle = PI-radTemp1-radTemp2;
  radTop = PI - radTop; 
  radBase = radBase + (PI/2);
  
  Serial.println(getAngleFromRad(radTemp1));
  Serial.println(getAngleFromRad(radTemp2));

  Serial.print("Angle bottom: ");
  Serial.print(getAngleFromRad(radBase));
  Serial.print(" Angle middle: ");
  Serial.print(getAngleFromRad(radMiddle));
  Serial.print(" Angle top: ");
  Serial.print(getAngleFromRad(radTop));
  Serial.print("\n");
 
  analogWrite(servoPins[n_leg*3], radToSteps(radBase, n_leg*3));
  analogWrite(servoPins[n_leg*3+1], radToSteps(radMiddle, n_leg*3+1));
  analogWrite(servoPins[n_leg*3+2], radToSteps(radTop, n_leg*3+2));
}

void calcBottomAngle(double x, double y){
  radBase = atan(x/y);
//  Serial.println(radBase);
}

int radToSteps(double radian, int servo_index){
  int n_degrees = getAngleFromRad(radian);
  if(servo_index % 3 == 0){
    return map(n_degrees,300,1500,round(bottom_interval[servo_index/3] / 2), round(bottom_interval[servo_index/3] * 1.5) );
  } else if(servo_index % 3 == 1){
    return map(n_degrees,0,1600,middle_interval[servo_index/3], middle_interval[servo_index/3] + 2518 );
  } else {
    return map(n_degrees,0,1600,top_interval[servo_index/3], max_interval);
  }
}

int getAngleFromRad(double radian){
  double n_degrees = (radian*10) * (180/PI);
  return round(n_degrees);
}

double getRadFromAngle(double degree){
  return ((degree * PI) / 180);
}
