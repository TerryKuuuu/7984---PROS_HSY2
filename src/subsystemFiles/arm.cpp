#include "main.h"

//HELPER FUNCTIONS
void setArm(int power) {
  armLeft = power;
  armRight = power;
}

void resetArmEncoders() {
  armLeft.tare_position();
  armRight.tare_position();
}

double avgArmEncodeValue() {
  int AL = armLeft.get_position();
  int AR = armRight.get_position();

  return (fabs(AL) + fabs(AR)) / 2;
}

//DRIVER CONTROL FUNCTIONS
void setArmMotors() {
  int armPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setArm(armPower);
}

//AUTONOMOUS FUNCTIONS
void arm(int units, int voltage) {
  //define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset arm encoders
  resetArmEncoders();

  //roll until units are reached
  while(avgArmEncodeValue() < abs(units)) {
    setArm(voltage * direction);
    pros::delay(10);
  }

  //set drive back to neutral
  setArm(0);
}

void armTime(int milliseconds, int voltage) {
  //reset roller encoders
  resetRollerEncoders();

  //drive until times are reached
  setArm(voltage);
  for (int i = 0; i < milliseconds; i++)
  {
    if (i > milliseconds)
    {
      break;
    }
    pros::delay(1);
  }

  //set drive back to neutral
  setArm(0);
}


void armMode(int mode, int voltage) {
  if (mode > 0) { // if mode = 1
    setArm(voltage);
  }
  else if (mode < 1) { // if mode = 0
    setArm(-voltage * (1 - 0.5));
    pros::delay(350);
    setArm(-voltage * (1 - 0.3));
    pros::delay(200);
    setArm(-voltage);
  }
}
