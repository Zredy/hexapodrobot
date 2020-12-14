void setup(){
  initializeRobot();
}

void loop(){
  robotStand();
  delay(5000);
  /*
  angleBaseOverTime(15,0,-70,1000);
  angleBaseOverTime(0,0,-70,1000);
  */
  gesture_wave();
  delay(1000000);

  /*
  for(int i=0;i<5;i++){
    moveAtAngle("robot", 0, 180, 20, 400);
  }
  robotStand();
  */
  while(true){
    delay(1000);
  }
}
