#include "vex.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Variables
bool flag_RightS = false;
bool flag_LeftS = false;
bool intakeMoving = false;
bool stand = false;
bool inSim = false;
// Methods

void black_jack()
{
  inSim = true;
  stand = false;
  int card1 = (rand() % 10) + 2;
  int card2 = (rand() % 10) + 2;
  int total = card1 + card2;
  int dealerVisible = (rand() % 10) + 2;
  int dealerTotal = dealerVisible + ((rand() % 10) + 2);
  Controller1.Screen.clearScreen();
  Controller1.Screen.print("First Card: " + card1);
  Controller1.Screen.newLine(); Controller1.Screen.print("Second Card: " + card2);
  Controller1.Screen.newLine(); Controller1.Screen.print("Dealer Visible: " + dealerVisible);
  Controller1.Screen.newLine(); Controller1.Screen.print("Press up for hit and left for stand");
  if (Controller1.ButtonUp.pressing() && total < 21)
  {
    total += (rand() % 10) + 2;
  }
  else if (Controller1.ButtonLeft.pressing() || total > 21)
  {
    stand = true;
  }
  while (!stand)
  {
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("Your Total: " + total);
    Controller1.Screen.newLine(); Controller1.Screen.print("Dealer Visible: " + dealerVisible);
    Controller1.Screen.newLine(); Controller1.Screen.print("Press up for hit and left for stand");
    if (Controller1.ButtonUp.pressing() && total < 21)
    {
      total += (rand() % 10) + 2;
    }
    else if (Controller1.ButtonLeft.pressing() && total > 21)
    {
      stand = true;
    }
  }
  Controller1.Screen.clearScreen(); Controller1.Screen.print("You have: " + total);
  while (dealerTotal < 17)
  {
    dealerTotal += (rand() % 10) + 2;
  }
  Controller1.Screen.newLine(); Controller1.Screen.print("Dealer has: " + dealerTotal);
  Controller1.Screen.newLine();
  if (total > 21)
    Controller1.Screen.print("You Lose");
  else if (total <= 21 && total > dealerTotal)
    Controller1.Screen.print("You Win");
  else if (total == dealerTotal)
    Controller1.Screen.print("You Lose");
  else if (total <= 21 && dealerTotal > 21)
    Controller1.Screen.print("You Win");
  inSim = false;
}


void ringThrow_blue()
{
  COLOR.setLight(ledState::on);
  COLOR.brightness(100);
  while (1)
  {
    if (COLOR.hue() > 200 && COLOR.hue() < 300)
    {
      intakeMoving = true;
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
  LadyBrown.setVelocity(100, percent);
  LadyBrown.setPosition(0, degrees);
}




// Auton






// Driver Control
void noColor()
{
  LadyBrown.setBrake(vex::brakeType::hold);
  robot_auton_constants();
  while (1)
  {
    chassis.control_tank();

    if (Controller1.ButtonR2.pressing())
    {
      IntakeT.spin(forward);
      IntakeB.spin(reverse);
    }
    else if (Controller1.ButtonR1.pressing())
    {
      IntakeT.spin(reverse);
      IntakeB.spin(forward);
    }
    else
    {
      IntakeT.stop();
      IntakeB.stop();
    }

    if (Controller1.ButtonL2.pressing())
    {
      LadyBrown.spin(forward);
    }
    else if(Controller1.ButtonL1.pressing())
    {
      LadyBrown.spin(reverse);
    }
    else
    {
      LadyBrown.stop();
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
      if (flag_LeftS)
      {
        LeftScoop.set(false);
      }
      else if (!flag_LeftS)
      {
        LeftScoop.set(true);
      }

      if (flag_LeftS == true)
        flag_LeftS == false;
      else
        flag_LeftS == true;
    }

    if (Controller1.ButtonRight.pressing())
    {
      if (flag_RightS)
      {
        RightScoop.set(false);
      }
      else if (!flag_RightS)
      {
        RightScoop.set(true);
      }

      if (flag_RightS == true)
        flag_RightS == false;
      else
        flag_RightS == true;
    }

    if (Controller1.ButtonLeft.pressing())
    {
      RightScoop.set(false);
      LeftScoop.set(false);
    }

    if (Controller1.ButtonA.pressing())
    {
      LadyBrown.stop();
      LadyBrown.spinFor(forward, 50, degrees);
    }
    if (Controller1.ButtonX.pressing())
    {
      LadyBrown.spinFor(reverse, 10, degrees);
    }

    //Black Jack
    
  }

  wait (20, msec);
}

void blueColor()
{
  vex::thread intakeThread(ringThrow_red);
  LadyBrown.setBrake(vex::brakeType::hold);
  robot_auton_constants();
  while (1)
  {
    chassis.control_tank();

    if (Controller1.ButtonR2.pressing() && !intakeMoving)
    {
      IntakeT.spin(forward);
      IntakeB.spin(reverse);
    }
    else if (Controller1.ButtonR1.pressing() && !intakeMoving)
    {
      IntakeT.spin(reverse);
      IntakeB.spin(forward);
    }
    else
    {
      IntakeT.stop();
      IntakeB.stop();
    }

    if (Controller1.ButtonL2.pressing())
    {
      LadyBrown.spin(forward);
    }
    else if(Controller1.ButtonL1.pressing())
    {
      LadyBrown.spin(reverse);
    }
    else
    {
      LadyBrown.stop();
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
      if (flag_LeftS)
      {
        LeftScoop.set(false);
      }
      else if (!flag_LeftS)
      {
        LeftScoop.set(true);
      }

      if (flag_LeftS == true)
        flag_LeftS == false;
      else
        flag_LeftS == true;
    }

    if (Controller1.ButtonRight.pressing())
    {
      if (flag_RightS)
      {
        RightScoop.set(false);
      }
      else if (!flag_RightS)
      {
        RightScoop.set(true);
      }

      if (flag_RightS == true)
        flag_RightS == false;
      else
        flag_RightS == true;
    }

    if (Controller1.ButtonLeft.pressing())
    {
      RightScoop.set(false);
      LeftScoop.set(false);
    }

    if (Controller1.ButtonA.pressing())
    {
      LadyBrown.stop();
      LadyBrown.spinFor(forward, 50, degrees);
    }
    if (Controller1.ButtonX.pressing())
    {
      LadyBrown.spinFor(reverse, 10, degrees);
    }
  }

  wait (20, msec);
}

void redColor()
{
  vex::thread intakeThread(ringThrow_blue);
  LadyBrown.setBrake(vex::brakeType::hold);
  robot_auton_constants();
  while (1)
  {
    chassis.control_tank();

    if (Controller1.ButtonR2.pressing() && !intakeMoving)
    {
      IntakeT.spin(forward);
      IntakeB.spin(reverse);
    }
    else if (Controller1.ButtonR1.pressing() && !intakeMoving)
    {
      IntakeT.spin(reverse);
      IntakeB.spin(forward);
    }
    else
    {
      IntakeT.stop();
      IntakeB.stop();
    }

    if (Controller1.ButtonL2.pressing())
    {
      LadyBrown.spin(forward);
    }
    else if(Controller1.ButtonL1.pressing())
    {
      LadyBrown.spin(reverse);
    }
    else
    {
      LadyBrown.stop();
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
      if (flag_LeftS)
      {
        LeftScoop.set(false);
      }
      else if (!flag_LeftS)
      {
        LeftScoop.set(true);
      }

      if (flag_LeftS == true)
        flag_LeftS == false;
      else
        flag_LeftS == true;
    }

    if (Controller1.ButtonRight.pressing())
    {
      if (flag_RightS)
      {
        RightScoop.set(false);
      }
      else if (!flag_RightS)
      {
        RightScoop.set(true);
      }

      if (flag_RightS == true)
        flag_RightS == false;
      else
        flag_RightS == true;
    }

    if (Controller1.ButtonLeft.pressing())
    {
      RightScoop.set(false);
      LeftScoop.set(false);
    }

    if (Controller1.ButtonA.pressing())
    {
      LadyBrown.stop();
      LadyBrown.spinFor(forward, 50, degrees);
    }
    if (Controller1.ButtonX.pressing())
    {
      LadyBrown.spinFor(reverse, 10, degrees);
    }
  }

  wait (20, msec);
}