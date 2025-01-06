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
void red_ring_rush();
void red_wp_3rings();
void red_wp_4rings();
void blue_wp_4rings();
void red_tower_rush_bad();
void blue_wp_3rings();
void skills();
void actual_solo_wp();

// driver control
void redColor();
void blueColor();
void noColor();