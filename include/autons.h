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
void skills();
void qual_GR_RED();
void qual_GR_BLUE();
void qual_ALring_RED();
void qual_ALring_BLUE();
void elim_ring_RED();
void elim_ring_BLUE();
void elim_GR_RED();
void elim_GR_BLUE();

// driver control
void redColor();
void blueColor();
void noColor();