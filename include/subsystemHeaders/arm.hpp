#include "main.h"

//HELPER FUNCTIONS
void setArm(int power);
void resetArmEncoders();
double avgArmEncodeValue();

//DRIVER CONTROL FUNCTIONS
void setArmMotors();

//AUTONOMOUS FUNCTIONS
void arm(int units, int voltage);
void armTime(int milliseconds, int voltage);
void armMode(int mode, int voltage);
