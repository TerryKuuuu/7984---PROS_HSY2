#include "main.h"

void redNth() {
  pros::Imu imu_sensor(13);
  int gyro_1 = 0;
  int gyro_2 = 0;
  /**************************************************     開機機     ************************************************************/
  armMode(1, -127) ;
  rollerMode(0, 0, -127) ;
  pros::delay(400) ;
  armMode(1, 0) ;
  rollerMode(0, 0, 0) ;

  /**************************************************     第一柱     ************************************************************/
  drive(935, 110) ;
  pros::delay(200) ;
  rotate(-90, 110) ;
  armMode(0, 127) ;
  rollerMode(0, 0, 115) ;
  driveTime(700, 90) ;
  armMode(1, 127) ;
  drive(-70, 100) ;
  driveTime(650, 90) ;
  armMode(1, 0) ;
  pros::delay(500) ;
  rollerMode(0, 0, 0) ;

  /**************************************************     第二柱     ************************************************************/
  pros::delay(100) ;
  driveTime(1000, -110) ;
  setDriveBrakeModeBRAKE();
  pros::delay(100) ;
  rotate(-45, 110) ;
  pros::delay(100) ;
  sideway(1100, 127) ;
  pros::delay(100) ;

  gyro_1 = imu_sensor.get_rotation();
  driveTime(490, -90) ;
  gyro_2 = imu_sensor.get_rotation();
  int fix = (gyro_1 - gyro_2);

  pros::delay(200) ;

  /**************************************************     第三柱     ************************************************************/
  drive(80, 100) ;
  pros::delay(100) ;
  for (int i = 0; i < 50; i++)
  {
    if (fix != 0) {
      rotate(-fix, 40);
      break;
    }
    pros::delay(1);
  }
  sideway(1000, 127) ;
  pros::delay(100) ;
  rotate(-41, 110) ;
  pros::delay(100) ;
  drive(950, 110) ;

  armMode(0, 127) ;
  rollerMode(0, 0, 115) ;
  driveTime(535, 90) ;
  armMode(1, 100) ;
  drive(-70, 100) ;
  driveTime(500, 90) ;
  armMode(1, 0) ;
  pros::delay(1000) ;
  rollerMode(0, 0, 0) ;
  armMode(0, 127) ;
  //setDriveBrakeModeCOAST();
  drive(-100, 127) ;
  armMode(1, 0) ;

}
