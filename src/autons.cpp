#include "vex.h"

// Variables
bool intakeMoving = false;

// Methods
void ringThrow_blue()
{
  COLOR.setLight(ledState::on);
  COLOR.brightness(100);
  while (1)
  {
    if (COLOR.hue() > 200 && COLOR.hue() < 300)
    {
      intakeMoving = true;
      IntakeT.stop();
      IntakeT.spinFor(forward, 300, degrees, true);
      IntakeT.spinFor(reverse, 100, degrees, true);
      wait (500, msec);
      intakeMoving = false;
    }
    intakeMoving = false;
  }
}

void ringThrow_red()
{
  COLOR.setLight(ledState::on);
  COLOR.brightness(100);
  while (1)
  {
    if (COLOR.hue() < 20)
    {
      intakeMoving = true;
      IntakeT.stop();
      IntakeT.spinFor(forward, 300, degrees, true);
      IntakeT.spinFor(reverse, 100, degrees, true);
      wait (500, msec);
      intakeMoving = false;
    }
    intakeMoving = false;
  }
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
  chassis.set_turn_constants(12, .4, 0.006, 3, 15);
  chassis.set_swing_constants(12, .3, 0, 2, 15);

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
  WallMce.setPosition(0, degrees);
}




// Auton

void tune_pid()
{
  chassis.drive_distance(-20);
  chassis.turn_to_angle(-90);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(90);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(0);
  chassis.drive_distance(20);
}

void red_tower_rush_good()
{
  robot_auton_constants();
  robot_auton_constants();
  chassis.drive_distance(60);
  Scoop.set(true);
  wait (400, msec);
  chassis.drive_distance(-14);
  Scoop.set(false);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(10);
  chassis.drive_distance(23);
  wait(15, seconds);
}

void blue_tower_rush_bad()
{
  robot_auton_constants();
  IntakeB.spin(forward);
  chassis.drive_distance(60);
  Scoop.set(true);
  wait(200, msec);
  IntakeB.stop();
  wait (200, msec);
  chassis.drive_distance(-20);
  wait (50, msec);
  Scoop.set(false);
  chassis.drive_distance(-15);
  chassis.turn_to_angle(-165);
  chassis.drive_distance(-22);
  chassis.drive_distance(-8);
  Clamp.set(true);
  wait (350, msec);
  IntakeB.spin(forward);
  IntakeT.spin(forward);
  chassis.turn_to_angle(165);
  chassis.drive_distance(45);
  IntakeT.stop();
  chassis.turn_to_angle(90);
  chassis.drive_distance(-10);
  Clamp.set(false);
  wait (100, msec);
  chassis.turn_to_angle(225);
  /*chassis.drive_distance(-7);
  chassis.drive_distance(-10);
  Clamp.set(true);
  IntakeT.spin(forward);
  chassis.turn_to_angle(135);
  chassis.drive_distance(30);
  Scoop.set(true);
  wait (15, seconds);*/
}

void red_tower_rush_bad()
{
  robot_auton_constants();
  chassis.drive_distance(60);
  Scoop.set(true);
  wait (400, msec);
  chassis.drive_distance(-14);
  Scoop.set(false);
  WallMce.spinFor(forward, 200, degrees, false);
  chassis.drive_distance(-20);
  chassis.turn_to_angle(35);
  IntakeB.spin(forward);
  chassis.drive_distance(30);
  wait(100, msec);
  chassis.drive_distance(-15);
  chassis.turn_to_angle(175);
  chassis.drive_distance(-17);
  chassis.drive_distance(-8);
  Clamp.set(true);
  wait(100, msec);
  IntakeT.spin(forward);
  wait(200, msec);
  chassis.turn_to_angle(165);
  chassis.drive_distance(47);
  IntakeT.stop();
  chassis.turn_to_angle(250);
  Clamp.set(false);
  wait(100, msec);
  chassis.turn_to_angle(125);
  chassis.drive_distance(-35);
  chassis.drive_distance(-8);
  Clamp.set(true);
  wait(200, msec);
  IntakeT.spin(forward);
  wait(1500, msec);
  chassis.drive_distance(-40);
  wait(15, seconds);
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
  chassis.drive_distance(40);
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
  WallMce.spinFor(forward, 100, degrees, false);
  chassis.drive_distance(40);
}

void blue_ring_rush()
{
  robot_auton_constants();
  chassis.turn_to_angle(5);
  chassis.drive_distance(17);
  WallMce.spinFor(forward, 550, degrees, true);
  wait(20, msec);
  chassis.drive_distance(-17);
  WallMce.spinFor(reverse, 300, degrees, false);
  chassis.turn_to_angle(-1);
  chassis.drive_distance(-25);
  chassis.drive_distance(-7);
  chassis.drive_distance(-4);
  Clamp.set(true);
  wait(250, msec);
  IntakeB.spin(forward);
  IntakeT.spin(forward);
  chassis.turn_to_angle(195);
  wait(20, msec);
  chassis.drive_distance(43);
  wait(100, msec);
  chassis.left_swing_to_angle(244);
  chassis.drive_distance(28);
  wait(200, msec);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(230);
  chassis.drive_distance(-40);
  chassis.turn_to_angle(270);
  chassis.drive_distance(22);
  wait(100, msec);
  chassis.turn_to_angle(90);
  WallMce.spinFor(forward, 100, degrees, false);
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

    if (Controller1.ButtonA.pressing())
    {
      WallMce.stop();
      WallMce.spinFor(forward, 50, degrees);
    }
    if (Controller1.ButtonX.pressing())
    {
      WallMce.spinFor(reverse, 10, degrees);
    }
  }

  wait (20, msec);
}

void blueColor()
{
  vex::thread intakeThread(ringThrow_red);
  WallMce.setBrake(vex::brakeType::hold);
  robot_auton_constants();
  while (1)
  {
    chassis.control_tank();

    if (Controller1.ButtonR2.pressing() && !intakeMoving)
    {
      IntakeT.spin(forward);
      IntakeB.spin(forward);
    }
    else if (Controller1.ButtonR1.pressing() && !intakeMoving)
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

    if (Controller1.ButtonA.pressing())
    {
      WallMce.stop();
      WallMce.spinFor(forward, 50, degrees);
    }
    if (Controller1.ButtonX.pressing())
    {
      WallMce.spinFor(reverse, 10, degrees);
    }
  }

  wait (20, msec);
}

void redColor()
{
  vex::thread intakeThread(ringThrow_blue);
  WallMce.setBrake(vex::brakeType::hold);
  robot_auton_constants();
  while (1)
  {
    chassis.control_tank();

    if (Controller1.ButtonR2.pressing() && !intakeMoving)
    {
      IntakeT.spin(forward);
      IntakeB.spin(forward);
    }
    else if (Controller1.ButtonR1.pressing() && !intakeMoving)
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

    if (Controller1.ButtonA.pressing())
    {
      WallMce.stop();
      WallMce.spinFor(forward, 50, degrees);
    }
    if (Controller1.ButtonX.pressing())
    {
      WallMce.spinFor(reverse, 10, degrees);
    }
  }

  wait (20, msec);
}