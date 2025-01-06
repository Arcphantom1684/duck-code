#include "vex.h"

int Acounter = 0;
bool clampMoving = false;
bool intakeMoving = false;
bool ladyBrownMoving = false;

// Methods
void CloseClamp()
{
  Clamp.set(true);
}

// Constants
void odom_test()
{
  chassis.set_coordinates(0, 0, 0);
  while(1)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    wait (20, msec);
  }
}

void default_constants()
{
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(0.75, 150, 2500);
  chassis.set_turn_exit_conditions(1.5, 150, 1500);
  chassis.set_swing_exit_conditions(1.5, 150, 1500);
}

void odom_constants()
{
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

void robot_auton_constants()
{
  odom_constants();
  default_constants();
  chassis.set_coordinates(0, 0, 0);
  COLOR.setLight(ledState::on);
  COLOR.brightness(100);
  Left1.setVelocity(100, percent);
  Left2.setVelocity(100, percent);
  Left3.setVelocity(100, percent);
  Right1.setVelocity(100, percent);
  Right2.setVelocity(100, percent);
  Right3.setVelocity(100, percent);
  IntakeT.setVelocity(101, percent);
  IntakeB.setVelocity(101, percent);
  WallMce.setVelocity(100, percent);
}




// Auton
void red_tower_rush_bad()
{
  robot_auton_constants();
  chassis.drive_distance(63);
  Scoop.set(true);
  wait (400, msec);
  chassis.drive_distance(-17);
  Scoop.set(false);
  WallMce.spinFor(forward, 300, degrees, false);
  chassis.drive_distance(-30);
  chassis.turn_to_angle(130);
  chassis.drive_distance(-15);
  chassis.drive_distance(-5);
  Clamp.set(true);
  wait(300, msec);
  IntakeT.spinFor(forward, 450, degrees, true);
  chassis.left_swing_to_angle(70);
  Clamp.set(false);
  IntakeB.spin(forward);
  wait (100, msec);
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_distance(40);
  wait (50, msec);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(110);
  chassis.drive_distance(-20);
  chassis.drive_distance(-5);
  Clamp.set(true);
  IntakeT.spin(forward);
  wait (700, msec);
  WallMce.spinFor(forward, 150, degrees, false);
  chassis.turn_to_angle(190);
  chassis.drive_distance(40);
}

void red_ring_rush()
{
  robot_auton_constants();
  chassis.turn_to_angle(-5);
  chassis.drive_distance(17);
  WallMce.spinFor(forward, 550, degrees, true);
  wait(20, msec);
  chassis.drive_distance(-17);
  WallMce.spinFor(reverse, 300, degrees, false);
  chassis.turn_to_angle(1);
  chassis.drive_distance(-25);
  chassis.drive_distance(-7);
  chassis.drive_distance(-4);
  Clamp.set(true);
  wait(250, msec);
  IntakeB.spin(forward);
  IntakeT.spin(forward);
  chassis.turn_to_angle(-195);
  wait(20, msec);
  chassis.drive_distance(43);
  wait(100, msec);
  chassis.right_swing_to_angle(-244);
  chassis.drive_distance(28);
  wait(200, msec);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(-230);
  chassis.drive_distance(-40);
  chassis.turn_to_angle(-270);
  chassis.drive_distance(22);
  wait(100, msec);
  chassis.turn_to_angle(-90);
  chassis.drive_distance(40);
}

void actual_solo_wp()
{
  robot_auton_constants();
  chassis.turn_to_angle(-5);
  chassis.drive_distance(17);
  WallMce.spinFor(forward, 550, degrees, true);
  wait(20, msec);
  chassis.drive_distance(-14);
  WallMce.spinFor(reverse, 300, degrees, false);
  chassis.turn_to_angle(110);
  IntakeB.spin(forward);
  chassis.drive_distance(33);
  wait(200, msec);
  chassis.drive_distance(-41);
  chassis.turn_to_angle(-4);
  chassis.drive_distance(-35);
  chassis.drive_distance(-7);
  Clamp.set(true);
  wait(250, msec);
  IntakeT.spin(forward);
  chassis.turn_to_angle(110);
}


// Driver Control
void noColor()
{
  WallMce.setBrake(vex::brakeType::hold);
  robot_auton_constants();
  while (1)
  {
    chassis.control_tank();

    if (Controller1.ButtonR2.pressing())
    {
      IntakeT.spin(forward);
      IntakeB.spin(forward);
    }
    else if (Controller1.ButtonR1.pressing())
    {
      IntakeT.spin(reverse);
      IntakeB.spin(reverse);
    }
    else
    {
      IntakeT.stop();
      IntakeB.stop();
    }

    if (Controller1.ButtonL2.pressing())
    {
      WallMce.spin(forward);
    }
    else if(Controller1.ButtonL1.pressing())
    {
      WallMce.spin(reverse);
    }
    else
    {
      WallMce.stop();
    }

    if (Controller1.ButtonB.pressing())
    {
      Clamp.set(true);
    }
    else if (Controller1.ButtonY.pressing())
    {
      Clamp.set(false);
    }

    if (Controller1.ButtonDown.pressing())
    {
      Scoop.set(true);
    }
    else if (Controller1.ButtonRight.pressing())
    {
      Scoop.set(false);
    }
  }

  wait (20, msec);
}