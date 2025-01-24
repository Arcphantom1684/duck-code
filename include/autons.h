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
void red_tower_rush_good();
void tune_pid();
void red_ring_rush();
void blue_ring_rush();
void blue_tower_rush_bad();
void red_tower_rush_bad();
void skills();
void actual_solo_wp();

// driver control
void redColor();
void blueColor();
void noColor();