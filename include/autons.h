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
void blue_rush();
void red_wp_3rings();
void red_wp_4rings();
void blue_wp_4rings();
void red_rush();
void blue_wp_3rings();
void skills();

// driver control
void redColor();
void blueColor();
void noColor();