#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// Brain declaration
brain  Brain;

// Declaring the motor ports and values
motor Left1 = motor(PORT1, ratio6_1, true);
motor Left2 = motor(PORT2, ratio6_1, false);
motor Left3 = motor(PORT3, ratio6_1, false);
motor Right1 = motor(PORT4, ratio6_1, false);
motor Right2 = motor(PORT5, ratio6_1, true);
motor Right3 = motor(PORT6, ratio6_1, true);
vex::digital_out Clamp = vex::digital_out(Brain.ThreeWirePort.H);
motor LadyBrown = motor(PORT10, ratio18_1, true);
motor IntakeB = motor(PORT9, ratio18_1, true);
motor IntakeT = motor(PORT7, ratio18_1, false);
vex::digital_out Scoop = vex::digital_out(Brain.ThreeWirePort.A);
vex::digital_out LeftScoop = vex::digital_out(Brain.ThreeWirePort.G);
optical COLOR = optical(PORT20);
inertial INERTIAL = inertial(PORT19);
controller Controller1 = controller(primary);


void vexcodeInit( void ) {
  // nothing to initialize
}