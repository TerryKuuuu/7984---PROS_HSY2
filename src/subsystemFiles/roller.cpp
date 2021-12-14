#include "main.h"

//DEFINE
//pros::ADIAnalogIn lineTrackerUp('H');
//pros::ADIAnalogIn lineTrackerDown('G');

//HELPER FUNCTIONS
void setRoller(int powerUp, int powerDown) {
  rollerUp = powerUp;
  rollerDown = powerDown;
}

void setRollerUpCase(int power) {
  rollerUp = power;
}

void setRollerDownCase(int power) {
  rollerDown = power;
}

/*void setArmRoller(int powerArm) {
  armLeft = powerArm;
  armRight = powerArm;
}*/

void resetRollerEncoders() {
  rollerUp.tare_position();
  rollerDown.tare_position();
}

double avgRollerEncodeValue() {
  int RU = rollerUp.get_position();
  int RD = rollerDown.get_position();

  return (fabs(RU) + fabs(RD)) / 2;
}

//DRIVER CONTROL FUNCTIONS
void setRollerMotors() {
  int l1 = 127 * controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
  int l2 = 127 * controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
  int x = 127 * controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
  int b = 127 * controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);

  int rollerUp = 0;
  int rollerDown = 0;

  if(abs(l1) > 0 && abs(l2) > 0) {
    rollerUp = -127;
    rollerDown = 127;
  }
  else if (abs(l1) > 0) {
    rollerUp = 127;
    rollerDown = 127;
  }
  else if (abs(l2) > 0) {
    rollerUp = -127;
    rollerDown = -127;
  }
  else if (abs(x) > 0) {
    rollerDown = 127;
  }
  else if (abs(b) > 0) {
    rollerDown = -127;
  }
  else {
    rollerUp = 0;
    rollerDown = 0;
  }

  setRoller(rollerUp, rollerDown);

  /*int rollerPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
  setRoller(rollerPower, rollerPower);*/
}

//AUTONOMOUS FUNCTIONS
void roller(int units, int voltage) {
  //define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset roller encoders
  resetRollerEncoders();

  //roll until units are reached
  while(avgRollerEncodeValue() < abs(units)) {
    setRoller(voltage * direction, voltage * direction);
    pros::delay(10);
  }

  //roll back to neutral
  setRoller(0, 0);
}

void rollerTime(int milliseconds, int voltage) {
  //reset roller encoders
  resetRollerEncoders();

  //drive until times are reached
  setRoller(voltage, voltage);
  for (int i = 0; i < milliseconds; i++)
  {
    if (i > milliseconds)
    {
      break;
    }
    pros::delay(1);
  }

  //set drive back to neutral
  setRoller(0, 0);
}


void rollerMode(int mode, int units, int voltage) {
  //define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset roller encoders
  resetRollerEncoders();

  //roll until units are reached
  switch(mode){
    case 1:
      {
        //pros::lcd::set_text(4, "Running Case 1");
        while(rollerDown.get_position() < abs(units)) {
          setRoller(0, voltage * direction);
          pros::delay(10);
        }
        //roll back to neutral
        setRoller(0, 0);
        break;
      }
    case 2:
      {
        //pros::lcd::set_text(4, "Running Case 2");
        while(rollerUp.get_position() < abs(units)) {
          setRoller(voltage * direction, 0);
          pros::delay(10);
        }
        //roll back to neutral
        setRoller(0, 0);
        break;
      }
    case 3:
      {
        //pros::lcd::set_text(4, "Running Case 3");
        while(avgRollerEncodeValue() < abs(units)) {
          setRoller(voltage, voltage);
          pros::delay(10);
        }
        //roll back to neutral
        setRoller(0, 0);
        break;
      }
      /*case 4:
        {
          //pros::lcd::set_text(4, "Running Case 4");
          setRoller(0, voltage * direction);
          for (int i = 0; i < units; i++)
          {
            if (lineTrackerDown.get_value() < 2700)
            {
              break;
            }
            pros::delay(1);
          }
          break;
        }*/
      /*case 5:
        {
          //pros::lcd::set_text(4, "Running Case 5");
          setRoller(voltage * direction, voltage * direction);
          for (int i = 0; i < units; i++)
          {
            if (lineTrackerUp.get_value() < 2700)
            {
              break;
            }
            pros::delay(1);
          }
          //roll back to neutral
          setRoller(0, 0);
          break;
        }*/
    default:
        //pros::lcd::set_text(4, "Running Default Case");
        setRoller(voltage * direction, voltage * direction);
        pros::delay(10);
  }
}

/*
void runRollerCase() {
  pros::ADIPotentiometer lineTrackerUp ('H');
  pros::ADIPotentiometer lineTrackerDown ('G');

  int ltu = lineTrackerUp.get_value();
  int ltd = lineTrackerDown.get_value();

  int caselt = 0;
  int caseltu = 0;
  int caseltd = 0;

  if (ltu > 2800) {
    caseltu = 1 ;
  }
  else {
    caseltu = 2 ;
  }

  if (ltd > 2800) {
    caseltd = 1 ;
  }
  else {
    caseltd = 2 ;
  }

  if (caseltu = 2, caseltd = 2) { //both sensor were active
    caselt = 1 ;
  }
  else if (caseltu = 2, caseltd = 1) { // only up sensor active
    caselt = 2 ;
  }
  else if (caseltu = 1, caseltd = 2) { // only down sensor active
    caselt = 3 ;
  }
  else if (caseltu = 1, caseltd = 1) {// both sesor were not active
    caselt = 4 ;
  }
  else {
    caselt = 0 ;
  }

  switch(caselt){
    case 1: //do nth
      {
        pros::lcd::set_text(4, "Running Case 1");
        break;
      }
    case 2: // only active down roller
      {
        pros::lcd::set_text(4, "Running Case 2");
        while(abs(ltd) < 2750) {
          setRollerDownCase(127);
        }
        setRollerDownCase(0);
        break;
      }
    case 3: // only active up roller
      {
        pros::lcd::set_text(4, "Running Case 3");
        while(abs(ltu) < 2750) {
          setRollerUpCase(127);
        }
        setRollerUpCase(0);
        break;
      }
    case 4: // active both roller
      {
        pros::lcd::set_text(4, "Running Case 4");
        while(abs(ltu) < 2750) {
          setRollerUpCase(127);
        }
        setRollerUpCase(0);
        break;
      }
    default:
        pros::lcd::set_text(4, "Running Default Case");
  }
}

void setRollerCaseMotors() {
  int DigitalY = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
  if(abs(DigitalY) > 0)
    runRollerCase();
}
*/
