#include "main.h"

//HELPER FUNCTIONS
void setRoller(int powerUp, int powerDown);
//void setArmRoller(int powerArm);
void resetRollerEncoders();
double avgRollerEncodeValue();

//DRIVER CONTROL FUNCTIONS
void setRollerMotors();

//AUTONOMOUS FUNCTIONS
void roller(int units, int voltage);
void rollerTime(int milliseconds, int voltage);
void rollerMode(int mode, int units, int voltage);
