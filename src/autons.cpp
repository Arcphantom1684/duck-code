#include "vex.h"

int Acounter = 0;
bool clampMoving;


// Methods and buttons
void openClamp()
{
  clampMoving = true;
  ClampScoopRatchet.spinFor(-300, degrees);
  clampMoving = false;
}

void closeClamp()
{
  clampMoving = true;
  ClampScoopRatchet.spinFor(300, degrees);
  clampMoving = false;
}

void stopFor(motor a, int b)
{
  a.spinFor(0.1, degrees);
  a.stop();
  this_thread::sleep_for(b);
  a.spinFor(0.1, degrees);
}

void AbuttonRotater()
{
  if (Acounter % 2 == 0)
  {
    ClampScoopRatchet.spinFor(-300, degrees);
    Acounter++;
  }
  else if (Acounter % 2 != 0)
  {
    ClampScoopRatchet.spinFor(300, degrees);
    Acounter++;
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
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
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
  chassis.set_coordinates(0, 0, 0);
  COLOR.setLight(ledState::on);
  COLOR.brightness(100);
  Left1.setVelocity(100, percent);
  Left2.setVelocity(100, percent);
  Left3.setVelocity(100, percent);
  Right1.setVelocity(100, percent);
  Right2.setVelocity(100, percent);
  Right3.setVelocity(100, percent);
  Intake.setVelocity(101, percent);
  ClampScoopRatchet.setVelocity(100, percent);
  WallThingy.setVelocity(100, percent);
}




//Autonomous
void blue_rush()
{
  robot_auton_constants();
  ClampScoopRatchet.spinFor(-300, degrees, false);
  chassis.drive_distance(-73);
  chassis.turn_to_angle(-30);
  chassis.drive_distance(-11);
  ClampScoopRatchet.spinFor(300, degrees, true);
  Intake.spinFor(reverse, 700, degrees);
  Intake.spin(reverse);
  chassis.turn_to_angle(54);
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


void red_wp_3rings()
{
  robot_auton_constants();
  ClampScoopRatchet.spinFor(-300, degrees, false);
  WallThingy.spinFor(-715, degrees, true);
  wait (500, msec);
  WallThingy.spinFor(720, degrees, false);
  chassis.drive_distance(-46);
  chassis.turn_to_angle(97);
  chassis.drive_distance(-39);
  ClampScoopRatchet.spinFor(300, degrees, true);
  wait (10, msec);
  chassis.turn_to_angle(187);
  Intake.spin(reverse);
  chassis.drive_distance(25);
  chassis.turn_to_angle(-115);
  wait (700, msec);
  chassis.drive_distance(25);
  wait (200, msec);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(-30);
  WallThingy.spinFor(-715, degrees, false);
  chassis.drive_distance(33);
}

void red_wp_4rings()
{
  robot_auton_constants();
  ClampScoopRatchet.spinFor(-300, degrees, false);
  WallThingy.spinFor(-715, degrees, true);
  wait (100, msec);
  WallThingy.spinFor(715, degrees, false);
  chassis.drive_distance(-47);
  chassis.turn_to_angle(98);
  chassis.drive_distance(-34);
  wait (50, msec);
  chassis.drive_distance(-8);
  ClampScoopRatchet.spinFor(310, degrees, true);
  wait (10, msec);
  chassis.turn_to_angle(187);
  Intake.spin(reverse);
  chassis.drive_distance(25);
  chassis.turn_to_angle(-115);
  wait (500, msec);
  chassis.drive_distance(25);
  wait (200, msec);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(-138);
  chassis.drive_distance(18);
  wait (700, msec);
  chassis.drive_distance(-18);
  chassis.turn_to_angle(-30);
  WallThingy.spinFor(-715, degrees, false);
  chassis.drive_distance(33);
}

void red_rush()
{
  robot_auton_constants();
  ClampScoopRatchet.spinFor(-300, degrees, false);
  chassis.drive_distance(-73);
  chassis.turn_to_angle(30);
  chassis.drive_distance(-11);
  ClampScoopRatchet.spinFor(310, degrees, true);
  Intake.spinFor(reverse, 700, degrees);
  Intake.spin(reverse);
  chassis.turn_to_angle(-60);
  chassis.drive_distance(30);
  while ( 1 )
  {
    if (COLOR.hue() > 200)
    {
      Intake.stop();
      break;
    }
  }
  chassis.turn_to_angle(-180);
  chassis.drive_distance(-15);
  ClampScoopRatchet.spinFor(-300, degrees);
  chassis.drive_distance(8);
  chassis.turn_to_angle(-89);
  chassis.drive_distance(-34);
  ClampScoopRatchet.spinFor(310, degrees, true);
  Intake.spinFor(reverse, 500, degrees);
  chassis.turn_to_angle(-65);
  WallThingy.spinFor(reverse, 300, degrees, false);
  chassis.drive_distance(-35);
}

void blue_wp_3rings()
{
  robot_auton_constants();
  ClampScoopRatchet.spinFor(-300, degrees, false);
  WallThingy.spinFor(-715, degrees, true);
  wait (500, msec);
  WallThingy.spinFor(720, degrees, false);
  chassis.drive_distance(-46);
  chassis.turn_to_angle(97);
  chassis.drive_distance(-39);
  ClampScoopRatchet.spinFor(310, degrees, true);
  wait (10, msec);
  chassis.turn_to_angle(187);
  Intake.spin(reverse);
  chassis.drive_distance(25);
  chassis.turn_to_angle(-115);
  wait (700, msec);
  chassis.drive_distance(25);
  wait (200, msec);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(-30);
  WallThingy.spinFor(-715, degrees, false);
  chassis.drive_distance(33);
}

void blue_wp_4rings()
{
  robot_auton_constants();
  ClampScoopRatchet.spinFor(-300, degrees, false);
  WallThingy.spinFor(-715, degrees, true);
  wait (100, msec);
  WallThingy.spinFor(715, degrees, false);
  chassis.drive_distance(-47);
  chassis.turn_to_angle(-98);
  chassis.drive_distance(-30);
  wait (50, msec);
  chassis.drive_distance(-8);
  ClampScoopRatchet.spinFor(310, degrees, true);
  chassis.drive_distance(-4);
  wait (10, msec);
  chassis.turn_to_angle(-173);
  Intake.spin(reverse);
  chassis.drive_distance(25);
  chassis.turn_to_angle(115);
  wait (500, msec);
  chassis.drive_distance(25);
  wait (200, msec);
  chassis.drive_distance(-10);
  wait (400, msec);
  chassis.turn_to_angle(138);
  chassis.drive_distance(15);
  wait (50, msec);
  chassis.drive_distance(3);
  wait (700, msec);
  WallThingy.spinFor(-715, degrees, false);
  chassis.drive_distance(-18);
  chassis.turn_to_angle(30);
  chassis.drive_distance(33);
}

void skills()
{
  robot_auton_constants();
  ClampScoopRatchet.spinFor(-300, degrees, false);
  chassis.drive_distance(-5);
  WallThingy.spinFor(-715, degrees, true);
  wait (500, msec);
  WallThingy.spinFor(715, degrees, false);
  chassis.drive_distance(-13);
  chassis.turn_to_angle(-88);
  chassis.drive_distance(-30);
  ClampScoopRatchet.spinFor(300, degrees, true);
  chassis.drive_distance(-17);
  chassis.turn_to_angle(180);
  Intake.spin(reverse);
  chassis.drive_distance(43);
  wait (1000, msec);
  chassis.turn_to_angle(90);
  chassis.drive_distance(45);
  wait (1000, msec);
  chassis.turn_to_angle(0);
  chassis.drive_distance(35);
  wait (1500, msec);
  chassis.drive_distance(22);
  chassis.turn_to_angle(-100);
  wait (500, msec);
  chassis.drive_distance(-15);
  Intake.stop();
  Intake.spinFor(500, degrees, false);
  ClampScoopRatchet.spinFor(-300, degrees, true);
  chassis.drive_distance(20);
  ClampScoopRatchet.spinFor(300, degrees, false);
  chassis.turn_to_angle(180);
  chassis.drive_distance(-15);
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_distance(26);
  chassis.turn_to_angle(-88);
  ClampScoopRatchet.spinFor(-300, degrees, false);
  chassis.drive_distance(-99);
  ClampScoopRatchet.spinFor(300, degrees, true);
  chassis.turn_to_angle(90);
  Intake.spin(reverse);
  chassis.drive_distance(50);
  wait (1000, msec);
  chassis.drive_distance(20);
  wait (1000, msec);
  chassis.turn_to_angle(-30);
  chassis.drive_distance(-10);
  Intake.stop();
  Intake.spinFor(500, degrees, false);
  ClampScoopRatchet.spinFor(-300, degrees, true);
  chassis.drive_distance(10, false);
  ClampScoopRatchet.spinFor(300, degrees, false);
  Intake.spin(reverse);
  chassis.drive_distance(30);
  while ( 1 )
  {
    if (COLOR.hue() < 20)
    {
      Intake.stop();
      break;
    }
  }
  chassis.turn_to_angle(-90);
  chassis.drive_distance(-20);
}





// Driver Control
void redColor()
{
  ClampScoopRatchet.setPosition(0, degrees);
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
    if (hueColor > 200) 
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

    if (!clampMoving)
    {
      if (Controller1.ButtonLeft.pressing())
      {
        ClampScoopRatchet.spin(reverse);
      }
      else if (Controller1.ButtonRight.pressing())
      {
        ClampScoopRatchet.spin(forward);
      }
      else
      {
        ClampScoopRatchet.stop();
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

    if (Controller1.ButtonA.pressing() && !clampMoving)
    {
      vex::thread clampThread(openClamp);
    }

    if (Controller1.ButtonB.pressing() && !clampMoving)
    {
      vex::thread clampThread(closeClamp);
    }  

    /*if (Controller1.ButtonA.pressing())
    {
      ClampScoopRatchet.spinFor(-300, degrees, false);
    }
    else if (Controller1.ButtonB.pressing())
    {
      ClampScoopRatchet.spinFor(300, degrees, false);
    }
    else
    {
      ClampScoopRatchet.stop();
    }*/

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
    if (hueColor < 20) 
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

    if (!clampMoving)
    {
      if (Controller1.ButtonLeft.pressing())
      {
        ClampScoopRatchet.spin(reverse);
      }
      else if (Controller1.ButtonRight.pressing())
      {
        ClampScoopRatchet.spin(forward);
      }
      else
      {
        ClampScoopRatchet.stop();
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

    if (Controller1.ButtonA.pressing() && !clampMoving)
    {
      vex::thread clampThread(openClamp);
    }

    if (Controller1.ButtonB.pressing() && !clampMoving)
    {
      vex::thread clampThread(closeClamp);
    }

    chassis.control_tank();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

void noColor()
{
  ClampScoopRatchet.setPosition(0, degrees);
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
  

    if (!clampMoving)
    {
      if (Controller1.ButtonLeft.pressing())
      {
        ClampScoopRatchet.spin(reverse);
      }
      else if (Controller1.ButtonRight.pressing())
      {
        ClampScoopRatchet.spin(forward);
      }
      else
      {
        ClampScoopRatchet.stop();
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

    if (Controller1.ButtonA.pressing() && !clampMoving)
    {
      vex::thread clampThread(openClamp);
    }

    if (Controller1.ButtonB.pressing() && !clampMoving)
    {
      vex::thread clampThread(closeClamp);
    }  

    /*if (Controller1.ButtonA.pressing())
    {
      ClampScoopRatchet.spinFor(-300, degrees, false);
    }
    else if (Controller1.ButtonB.pressing())
    {
      ClampScoopRatchet.spinFor(300, degrees, false);
    }
    else
    {
      ClampScoopRatchet.stop();
    }*/

    chassis.control_tank();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}