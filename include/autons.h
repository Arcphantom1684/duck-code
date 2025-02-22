#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

// constants
void default_constants();
void odom_constants();
void odom_test();
void robot_auton_constants();

// auton
void drive();

// driver control
void redColor();
void blueColor();
void noColor();