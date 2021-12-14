#include "main.h"
/*
//HELPER FUNCTIONS
void setRollerUpCase(int power) {
  rollerUp = power;
}

void setRollerDownCase(int power) {
  rollerDown = power;
}

//DRIVER CONTROL FUNCTIONS
void setRollerCaseMotors() {
  int DigitalY = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
  if(abs(DigitalY) > 0)
    runRollerCase();
}

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
*/
