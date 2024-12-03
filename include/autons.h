#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

// auton
void blue_rush();
void red_wp();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void holonomic_odom_test();

// driver control
void redColor();
void blueColor();