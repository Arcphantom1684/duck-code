#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// Brain declaration
brain  Brain;

// Declaring the motor ports and values
motor Left1 = motor(PORT1, ratio6_1, false);
motor Left2 = motor(PORT2, ratio6_1, true);
motor Left3 = motor(PORT3, ratio6_1, true);
motor Right1 = motor(PORT4, ratio6_1, true);
motor Right2 = motor(PORT5, ratio6_1, false);
motor Right3 = motor(PORT6, ratio6_1, false);
motor ClampScoopRatchet = motor(PORT8, ratio18_1, false);
motor WallThingy = motor(PORT19, ratio18_1, false);
motor Intake = motor(PORT7, ratio18_1, false);
optical COLOR = optical(PORT20);
inertial INERTIAL = inertial(PORT18);
controller Controller1 = controller(primary);


void vexcodeInit( void ) {
  // nothing to initialize
}