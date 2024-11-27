using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;
extern motor Left1;
extern motor Left2;
extern motor Left3;
extern motor Right1;
extern motor Right2;
extern motor Right3;
extern motor ClampScoopRatchet;
extern motor WallThingy;
extern controller Controller1;
extern motor Intake;
extern optical COLOR;

extern motor_group leftSide = motor_group(Left1, Left2, Left3);
extern motor_group rightSide = motor_group(Right1, Right2, Right3);
//Add your devices below, and don't forget to do the same in robot-config.cpp:



void vexcodeInit( void );