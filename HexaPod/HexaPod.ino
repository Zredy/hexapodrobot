void setup(){
  initializeRobot();
}

void loop(){
  //Robot test run sequence
  robotStand();
  delay(5000);
  gesture_wave();
  for(int i=0;i<15;i++){
    moveAtAngle("robot", 0 , -30, 30, 600);
  }
  delay(200);
  robotStand();
  delay(200);
  for(int i=0;i<14;i++){
    turnRobot("left", 20, 400);
  }
  delay(1000);
  robotStand();
  angleBaseOverTime(15,0,-70,2000);
  angleBaseOverTime(0,0,-70,2000);
  robotStand();
  delay(1000);
  for(int i=0;i<7;i++){
    moveAtAngle("robot", 0 , -30, 20, 600);
  }
  delay(200);
  for(int i=0;i<4;i++){
    turnRobot("left",20,400);
  }
  robotStand();
  gesture_wave();
  robotStand();
  delay(200);
  for(int i=0;i<4;i++){
    turnRobot("right",20,400);
  }
  robotStand();
  delay(200);
  for(int i=0;i<8;i++){
    moveAtAngle("robot", 0 , -20, 20, 600);
  }
  delay(200);
  robotStand();
  while(true){
    delay(1000);
  }
  
}
