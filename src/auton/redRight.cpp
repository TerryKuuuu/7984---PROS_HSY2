#include "main.h"

void redRight() {
  // rotate(90, 90);
  rotateWithPID(90, 90);
  pros::delay(1000);
  rotateWithPID(90, 90);
  pros::delay(1000);
  rotateWithPID(180, 127);
}
