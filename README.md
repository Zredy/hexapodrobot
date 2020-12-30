# hexapodrobot

Hi! Welcome to my HexaPod repo!

This is a personal project, so don't expect anything grandiose from it.
The goal is to program the robot to walk, turn around and do some gestures.
The code "should" work with all HexaPod robots that have their legs perpendicular to each other, but don't expect any guarantees

----

How it "works"
- NOTE: I am by no means an expert in robotics or programming, the code I wrote was to suit this robot and not for wide spread use, I know i made quite a bit of mistakes and some things could be shortened, but it works.
- Inverse Kinematics: Contained in the IK.ino file, a simple piece of code that converts the XYZ coordinate of the tip of the leg to the corresponding angles for the micro servos
- Servo movement: All servos are controlled via PWM since I couldn't figure out how to run 18 servos from the servo library, and PWMServo doesn't support writeMicroseconds which are needed for higher precision. After code rework and adjusting to PWM, realized that these servos dont have that much precision either way so this was half fail. (Works well enough)
- Functions for running the robot: The main function to move the robot or the legs is "moveAtAngle" which runs either a leg, a leg_set or the whole robot at the specified angle
Individiual legs can also be moved to a given XYZ position.
- I have not mada spatial range map for each leg, as I don't see the use of it at the moment(maybe in the future)

----

Hardware
- Teensy 3.6 running Teensyduino
- Arduino 1.8.13
- Arduino nano breakout board(only temporary for connecting all the motors to power, will be replaced once I get to the making of PCB)
- Micro servo motors(plastic geared);

----

TODO
- Add ability for robot to turn - DONE but not final
- Add ablity for robot to tilt backward/forward on only 4 legs, use the 2 free legs for "gestures" - DONE
- Add ability for the robot base to tilt(should be able to implement with the previous) - DONE(tilting in two axes)
