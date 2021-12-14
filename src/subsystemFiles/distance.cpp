#include "main.h"

void distanceCorr() {
  pros::Distance distanceLeft(7);
  pros::Distance distanceRight(6);
  int fixspeed = 33;
  int LF = 0;
  int LB = 0;
  int RF = 0;
  int RB = 0;

  if (distanceLeft.get() > distanceRight.get()) {
    LF = -fixspeed;
    LB = -fixspeed;
    RF = fixspeed;
    RB = fixspeed;
  } else if (distanceLeft.get() < distanceRight.get()) {
    LF = fixspeed;
    LB = fixspeed;
    RF = -fixspeed;
    RB = -fixspeed;
  }

  setDrive(LF, LB, RF, RB);

  while(distanceLeft.get() != distanceRight.get()) {
    std::cout << "loop" << std::endl;
    pros::delay(1);
  }


  // for (int i = 0; i < milliseconds; i++)
  // {
  //   if (distanceLeft.get() == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 1 || distanceLeft.get() + 1 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 2 || distanceLeft.get() + 2 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 3 || distanceLeft.get() + 3 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 4 || distanceLeft.get() + 4 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 5 || distanceLeft.get() + 5 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 6 || distanceLeft.get() + 6 == distanceRight.get()) {
  //     LF = 0;
  //     LB = 0;
  //     RF = 0;
  //     RB = 0;
  //     break;
  //   }
  //   else if (distanceLeft.get() > distanceRight.get()) {
  //     LF = -fixspeed;
  //     LB = -fixspeed;
  //     RF = fixspeed;
  //     RB = fixspeed;
  //   } else if (distanceLeft.get() < distanceRight.get()) {
  //     LF = fixspeed;
  //     LB = fixspeed;
  //     RF = -fixspeed;
  //     RB = -fixspeed;
  //   }
  //   pros::delay(1);
  // }

  setDrive(0, 0, 0, 0);
}
