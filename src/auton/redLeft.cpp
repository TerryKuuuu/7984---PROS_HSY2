#include "main.h"

void redLeft() {
  pros::Imu imu_sensor(13);
  double A = imu_sensor.get_rotation();
  /**************************************************     開機機     ************************************************************/
  rollerMode(1, 100, 127) ;

  /**************************************************     第一柱     ************************************************************/
  setDrive(90, 90, 90, 90);
  pros::delay(100);
  setDrive(30, 30, 127, 127);
  armMode(1, 127) ;
  pros::delay(500);
  setDrive(20, 20, 20, 20);
  setDriveBrakeModeBRAKE();
  rollerMode(0, 0, 110) ;
  pros::delay(900);
  armMode(1, 0) ;
  pros::delay(400);
  rollerMode(0, 0, 0) ;
  setDriveBrakeModeCOAST();
  pros::delay(200);
  double C = imu_sensor.get_rotation();
  printf("%f\n", C);

  /**************************************************     第二柱     ************************************************************/
  rollerMode(0, 0, -127) ;
  armMode(1, -127) ;
  setDriveBrakeModeBRAKE();
  drive(-800, 127);
  rollerMode(0, 0, 0) ;
  armMode(1, 0) ;

  rotate(-140, 90);
  double B = imu_sensor.get_rotation();
  printf("%f\n", B);
  pros::delay(500);
  driveTime(300, -100);
  driveTime(200, -80);
  driveTime(200, -60);
  pros::delay(500);
  setDriveBrakeModeCOAST();
  drive(3325, 100);
  //drive(500, 100);
  //drive(500, 80);
  //drive(150, 100);
  //setDriveBrakeModeBRAKE();
  pros::delay(500);

  rotate(50, 90);
  armMode(1, 127) ;
  pros::delay(500);
  drive(900, 70);
  setDrive(20, 20, 20, 20);
  setDriveBrakeModeBRAKE();
  rollerMode(0, 0, 110) ;
  pros::delay(1200);
  armMode(1, 0) ;
  pros::delay(400);
  rollerMode(0, 0, 0) ;
  setDriveBrakeModeCOAST();
  pros::delay(200);

  rollerMode(0, 0, -127) ;
  armMode(1, -127) ;
  setDriveBrakeModeBRAKE();
  drive(-800, 127);
  pros::delay(200) ;
  rollerMode(0, 0, 0) ;
  armMode(1, 0) ;
  pros::delay(200) ;
  rotate(-135, 90);
}
