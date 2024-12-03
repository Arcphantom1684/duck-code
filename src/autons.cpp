#include "vex.h"

bool Acounter = 0;
bool wasButtonPressed = false;

int stopFor(motor a, int b)
{
  a.spinFor(0.01, seconds);
  vex::task::sleep(b);
  a.stop();
  return 0;
}

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants()
{
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants()
{
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

void blue_rush()
{
  odom_constants();
  COLOR.setLight(ledState::on);
  COLOR.brightness(100);
  Left1.setVelocity(100, percent);
  Left2.setVelocity(100, percent);
  Left3.setVelocity(100, percent);
  Right1.setVelocity(100, percent);
  Right2.setVelocity(100, percent);
  Right3.setVelocity(100, percent);
  Intake.setVelocity(100, percent);
  ClampScoopRatchet.setVelocity(100, percent);
  WallThingy.setVelocity(70, percent);
  ClampScoopRatchet.spinFor(-300, degrees, false);
  chassis.drive_distance(-73);
  chassis.turn_to_angle(-30);
  chassis.drive_distance(-11);
  ClampScoopRatchet.spinFor(300, degrees, true);
  Intake.spinFor(reverse, 700, degrees);
  Intake.spin(reverse);
  chassis.turn_to_angle(50);
  chassis.drive_distance(30);
  while ( 1 )
  {
    if (COLOR.hue() < 20)
    {
      Intake.stop();
      break;
    }
  }
  chassis.turn_to_angle(180);
  chassis.drive_distance(-15);
  ClampScoopRatchet.spinFor(-300, degrees);
  chassis.drive_distance(9);
  chassis.turn_to_angle(90);
  chassis.drive_distance(-34);
  ClampScoopRatchet.spinFor(300, degrees, true);
  Intake.spinFor(reverse, 500, degrees);
  chassis.turn_to_angle(65);
  WallThingy.spinFor(reverse, 300, degrees, false);
  chassis.drive_distance(-35);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void red_wp()
{
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  COLOR.setLight(ledState::on);
  COLOR.brightness(100);
  Left1.setVelocity(100, percent);
  Left2.setVelocity(100, percent);
  Left3.setVelocity(100, percent);
  Right1.setVelocity(100, percent);
  Right2.setVelocity(100, percent);
  Right3.setVelocity(100, percent);
  Intake.setVelocity(100, percent);
  ClampScoopRatchet.setVelocity(100, percent);
  WallThingy.setVelocity(100, percent);
  ClampScoopRatchet.spinFor(-300, degrees, false);
  WallThingy.spinFor(-715, degrees, true);
  wait (500, msec);
  WallThingy.spinFor(715, degrees, false);
  chassis.drive_distance(-47);
  chassis.turn_to_angle(97);
  chassis.drive_distance(-39);
  ClampScoopRatchet.spinFor(300, degrees, true);
  chassis.turn_to_angle(187);
  Intake.spin(reverse);
  chassis.drive_distance(25);
  chassis.turn_to_angle(-120);
  chassis.drive_distance(25);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(-30);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test()
{
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test()
{
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test()
{
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test()
{
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test()
{
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

void redColor()
{
  WallThingy.setStopping(vex::hold);
  ClampScoopRatchet.setStopping(vex::hold);
  // Changing the velocity of the motors and sides
  Left1.setVelocity(100, percent);
  Left2.setVelocity(100, percent);
  Left3.setVelocity(100, percent);
  Right1.setVelocity(100, percent);
  Right2.setVelocity(100, percent);
  Right3.setVelocity(100, percent);
  Intake.setVelocity(100, percent);
  ClampScoopRatchet.setVelocity(100, percent);
  WallThingy.setVelocity(70, percent);

  COLOR.setLight(ledState::on);
  COLOR.brightness(100);
  int hueColor = COLOR.hue();

  while (1)
  {
    if (hueColor > 150) 
    {
      Intake.stop();
      Intake.spinFor(reverse, 358, degrees);
      stopFor(Intake, 1);
    }
    else
    {
      if (Controller1.ButtonR2.pressing())
      {
        Intake.spin(reverse);
      }
      else if (Controller1.ButtonR1.pressing())
      {
        Intake.spin(forward);
      }
      else 
      {
        Intake.stop();
      }
    }

    if (Controller1.ButtonL2.pressing())
    {
      WallThingy.spin(reverse);
    }
    else if (Controller1.ButtonL1.pressing())
    {
      WallThingy.spin(forward);
    }
    else
    {
      WallThingy.stop();
    }

    if (Controller1.ButtonA.pressing())
    {
       ClampScoopRatchet.spinFor(-300, degrees);
    }
    else if (Controller1.ButtonB.pressing())
    {
      ClampScoopRatchet.spinFor(300, degrees);
    }
    else
    {
      ClampScoopRatchet.stop();
    }

    chassis.control_tank();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

void blueColor()
{
  WallThingy.setStopping(vex::hold);
  ClampScoopRatchet.setStopping(vex::hold);
  // Changing the velocity of the motors and sides
  Left1.setVelocity(100, percent);
  Left2.setVelocity(100, percent);
  Left3.setVelocity(100, percent);
  Right1.setVelocity(100, percent);
  Right2.setVelocity(100, percent);
  Right3.setVelocity(100, percent);
  Intake.setVelocity(100, percent);
  ClampScoopRatchet.setVelocity(100, percent);
  WallThingy.setVelocity(100, percent);

  COLOR.setLight(ledState::on);
  COLOR.brightness(100);
  int hueColor = COLOR.hue();
  
  while (1)
  {
    if (hueColor > 150) 
    {
      Intake.stop();
      Intake.spinFor(reverse, 358, degrees);
      stopFor(Intake, 1);
    }
    else
    {
      if (Controller1.ButtonR2.pressing())
      {
        Intake.spin(reverse);
      }
      else if (Controller1.ButtonR1.pressing())
      {
        Intake.spin(forward);
      }
      else 
      {
        Intake.stop();
      }
    }

    if (Controller1.ButtonL2.pressing())
    {
      WallThingy.spin(reverse);
    }
    else if (Controller1.ButtonL1.pressing())
    {
      WallThingy.spin(forward);
    }
    else
    {
      WallThingy.stop();
    }

    if (Controller1.ButtonA.pressing())
    {
       ClampScoopRatchet.spinFor(-300, degrees);
    }
    else if (Controller1.ButtonB.pressing())
    {
      ClampScoopRatchet.spinFor(300, degrees);
    }
    else
    {
      ClampScoopRatchet.stop();
    }

    chassis.control_tank();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}