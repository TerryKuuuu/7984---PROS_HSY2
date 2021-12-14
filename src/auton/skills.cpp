#include "main.h"

void skills() {
  pros::Imu imu_sensor(13);
  // 84267315
  /**************************************************     開機機     ************************************************************/
  armTime(300, -127);

  /**************************************************     第一柱     ************************************************************/
  setDrive(90, 90, 90, 90);
  pros::delay(200);
  armMode(1, 127) ;
  pros::delay(250);
  rollerMode(0, 0, 127) ;
  pros::delay(450);
  setRoller(0, 127);

  /**************************************************     第二柱     ************************************************************/
  pros::delay(800);
  setArm(0);
  drive(-25, 60);
  setRoller(0, 0);
  pros::delay(50);
  setArm(-127);
  setRoller(-127, -127);
  curve(-460, 127, 23) ;
  setRoller(0, 127);
  setArm(0) ;
  curve(-115, 127, 25) ;
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  drive(-200, 90);  //**************************************************     第一球
  setDriveBrakeModeCOAST();

  pros::delay(200) ;
  curve(-600, 18, 127) ;
  pros::delay(50) ;
  curve(-575, 20, 127) ;
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  drive(-180, 100); //**************************************************     第二球
  setDriveBrakeModeCOAST();
  setRoller(0, 0);

  int gyro_1 = imu_sensor.get_rotation();

  driveTime(800, 90);
  pros::delay(10);
  armMode(1, 127) ;
  driveTime(400, 60);
  pros::delay(100);
  setDriveBrakeModeBRAKE();
  setRoller(127, 0);
  pros::delay(300);
  setRoller(0, 0);
  pros::delay(10);
  setRoller(127, 127);
  pros::delay(350);
  setRoller(0, 127);
  armMode(1, 0) ;
  pros::delay(200);
  rollerMode(0, 0, 0) ;
  setDriveBrakeModeCOAST();

  /**************************************************     第三柱     ************************************************************/
  pros::delay(200);
  setArm(-127);
  drive(-100, 40);

  int gyro_2 = imu_sensor.get_rotation();
  int fix = (gyro_1 - gyro_2);
  for (int i = 0; i < 100; i++)
  {
    if (fix != 0) {
      rotateWithoutCorr(fix, 30);
      break;
    }
  }

  setDrive(-127, -127, 15, 15);
  pros::delay(600);
  setDrive(0, 0, 0, 0);
  pros::delay(100);
  setRoller(127, 127);
  drive(-200, 90);
  setRoller(0, 127);
  setArm(0) ;
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  drive(-400, 100); //**************************************************     第三柱
  setDriveBrakeModeCOAST();

  pros::delay(100);
  rotate(45, 90);
  driveTime(700, -90);
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  driveTime(430, -100); //**************************************************     第四柱
  setDriveBrakeModeCOAST();
  setRoller(0, 0);

  pros::delay(100);
  rotateWithoutCorr(75, 90);
  brake(400);

  setDrive(90, 90, 90, 90);
  pros::delay(900);
  armMode(1, 127) ;
  setDrive(25, 25, 25, 25);
  setDriveBrakeModeBRAKE();
  setRoller(127, 0);
  pros::delay(350);
  setRoller(0, 0);
  pros::delay(10);
  setRoller(127, 127);
  pros::delay(500);
  setRoller(0, 127);
  pros::delay(100);
  armMode(1, 0) ;
  pros::delay(250);
  setDriveBrakeModeCOAST();
  setRoller(0, 0) ;

  /**************************************************     第四柱     ************************************************************/
  drive(-800, 90) ;
  pros::delay(50) ;
  setArm(-127);
  setRoller(127, 127);
  drive(-500, 70) ;
  pros::delay(50) ;
  setArm(0);
  setRoller(0, 127) ;
  pros::delay(100) ;
  curve(-475, 127, 18) ;
  pros::delay(50);
  curve(-140, 127, 20) ;
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  drive(-350, 100); //**************************************************     第五柱
  setDriveBrakeModeCOAST();

  driveTime(150, 40);
  pros::delay(50) ;
  rotate(105, 88);
  armMode(1, 127) ;
  driveTime(800, 90); //**************************************************     第六柱
  pros::delay(10);
  driveTime(300, 60);
  pros::delay(100);
  setDriveBrakeModeBRAKE();
  setRoller(127, 0);
  pros::delay(300);
  setRoller(0, 0);
  pros::delay(10);
  setRoller(127, 127);
  pros::delay(350);
  setRoller(0, 127);
  armMode(1, 0) ;
  pros::delay(200);
  rollerMode(0, 0, 0) ;
  setDriveBrakeModeCOAST();

  /**************************************************     第五柱     ************************************************************/
  // drive(-150, 100);
  // rotate(90, 80);
  pros::delay(200);
  // setArm(-127);
  // drive(-200, 40);
  // setArm(0);
  setArm(-127);
  setRoller(-127, -127);
  drive(-400, 90);
  pros::delay(200);
  rotate(90, 90);
  pros::delay(200);
  // setArm(-127);
  setRoller(0, 127);

  // drive(625, 90);
  // pros::delay(10);
  // drive(425, 75);
  // pros::delay(10);

  // driveTime(750, 90);
  // pros::delay(50);
  // driveTime(550, 70);

  driveTime(1300, 80) ;
  setArm(127);
  drive(250, 60);
  pros::delay(100);
  drive(-175, 60); //**************************************************     第七柱

  rotate(90, 90);
  pros::delay(100);
  // driveTime(825, -80);
  driveTime(700, -85);
  pros::delay(50);
  driveTime(225, -70); //***************************************** 8

  pros::delay(100);
  rotateWithoutCorr(-75, 90);
  brake(400);

  setDrive(90, 90, 90, 90);
  pros::delay(900);
  armMode(1, 127) ;
  setDrive(25, 25, 25, 25);
  setDriveBrakeModeBRAKE();
  setRoller(127, 0);
  pros::delay(350);
  setRoller(0, 0);
  pros::delay(10);
  setRoller(127, 127);
  pros::delay(500);
  setRoller(0, 127);
  pros::delay(100);
  armMode(1, 0) ;
  pros::delay(250);
  setDriveBrakeModeCOAST();
  setRoller(0, 0) ;

  /**************************************************     第六柱     ************************************************************/
  //drive(-800, 90) ;
  pros::delay(800);
  setArm(0);
  drive(-25, 60);
  setRoller(0, 0);
  pros::delay(50);
  setArm(-127);
  setRoller(-127, -127);
  // rollerMode(0, 0, 0) ;
  // drive(-100, 85) ;
  curve(-460, 127, 23) ;
  // setDrive(-127, -127, -23, -23);
  // pros::delay(600);
  // setDrive(0, 0, 0, 0);
  setRoller(0, 127);
  setArm(0) ;
  curve(-115, 127, 25) ;
  // setDrive(-127, -127, -25, -25);
  // pros::delay(300);
  // setDrive(0, 0, 0, 0);
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  drive(-250, 90);  //***************************************** GET 9 BALL
  setDriveBrakeModeCOAST();

  pros::delay(200);
  curve(-600, 18, 127) ;
  pros::delay(50);
  curve(-575, 20, 127) ;
  // setDrive(-20, -20, -127, -127);
  // pros::delay(1000);
  // setDrive(0, 0, 0, 0);
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  drive(-180, 100); //***************************************** GET 10 BALL
  setDriveBrakeModeCOAST();
  setRoller(0, 0);

  gyro_1 = imu_sensor.get_rotation();

  driveTime(800, 90);
  pros::delay(10);
  armMode(1, 127) ;
  driveTime(400, 60);
  pros::delay(100);
  // setDrive(25, 25, 25, 25);
  setDriveBrakeModeBRAKE();
  setRoller(127, 0);
  pros::delay(300);
  setRoller(0, 0);
  pros::delay(10);
  setRoller(127, 127);
  pros::delay(350);
  setRoller(0, 127);
  armMode(1, 0) ;
  pros::delay(200);
  rollerMode(0, 0, 0) ;
  setDriveBrakeModeCOAST();

  /**************************************************     第七柱     ************************************************************/
  pros::delay(200);
  setArm(-127);
  drive(-100, 40);

  gyro_2 = imu_sensor.get_rotation();
  fix = (gyro_1 - gyro_2);

  for (int i = 0; i < 100; i++)
  {
    if (fix != 0) {
      rotateWithoutCorr(-fix, 30);
      break;
    }
  }

  // rotateWithoutCorr(-35, 88);
  setDrive(-127, -127, 15, 15);
  pros::delay(600);
  setDrive(0, 0, 0, 0);
  pros::delay(100);
  setRoller(127, 127);
  drive(-200, 90);
  // curve(-375, 127, 26) ;
  setRoller(0, 127);
  setArm(0) ;
  // pros::delay(50);
  // curve(-125, 127, 25) ;
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  drive(-400, 100); //***************************************** GET 11 BALL
  setDriveBrakeModeCOAST();

  pros::delay(100);
  rotate(45, 90);
  // pros::delay(200);
  // curve(-475, 127, 23) ;
  // pros::delay(50);
  // curve(-125, 127, 25) ;
  driveTime(700, -90);
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  driveTime(430, -100); //***************************************** GET 12 BALL
  setDriveBrakeModeCOAST();
  setRoller(0, 0);

  pros::delay(100);
  // curve(550, 127, 1) ;
  // setDrive(127, 127, 5, 5);
  // pros::delay(1000);
  // setDrive(0, 0, 0, 0);
  rotateWithoutCorr(75, 90);
  brake(400);

  // pros::delay(100) ;
  // driveTime(600, 90);
  // pros::delay(10);
  // driveTime(200, 60);
  // curve(550, 127, 1) ;
  setDrive(90, 90, 90, 90);
  pros::delay(900);
  armMode(1, 127) ;
  setDrive(25, 25, 25, 25);
  setDriveBrakeModeBRAKE();
  setRoller(127, 0);
  pros::delay(350);
  setRoller(0, 0);
  pros::delay(10);
  setRoller(127, 127);
  pros::delay(500);
  setRoller(0, 127);
  pros::delay(100);
  armMode(1, 0) ;
  pros::delay(250);
  setDriveBrakeModeCOAST();
  setRoller(0, 0) ;

  /**************************************************     第八柱     ************************************************************/
  drive(-800, 90) ;
  pros::delay(50) ;
  setArm(-127);
  setRoller(127, 127);
  drive(-500, 70) ;
  pros::delay(50) ;
  setArm(0);
  setRoller(0, 127) ;
  pros::delay(100) ;
  curve(-475, 127, 18) ;
  pros::delay(50);
  curve(-140, 127, 20) ;
  pros::delay(200);
  setDriveBrakeModeBRAKE();
  drive(-350, 100); //***************************************** GET 13 BALL
  setDriveBrakeModeCOAST();

  driveTime(150, 40);
  pros::delay(50) ;
  rotate(105, 88);
  armMode(1, 127) ;
  driveTime(800, 90); //***************************************** GET 14 BALL
  pros::delay(10);
  driveTime(300, 60);
  pros::delay(100);
  // setDrive(25, 25, 25, 25);
  setDriveBrakeModeBRAKE();
  setRoller(127, 0);
  pros::delay(300);
  setRoller(0, 0);
  pros::delay(10);
  setRoller(127, 127);
  pros::delay(350);
  setRoller(0, 127);
  armMode(1, 0) ;
  pros::delay(200);
  rollerMode(0, 0, 0) ;
  setDriveBrakeModeCOAST();

  pros::delay(200);
  // setArm(-127);
  // drive(-200, 40);
  // setArm(0);
  setArm(-127);
  setRoller(-127, -127);
  drive(-400, 90);
  pros::delay(200);
  rotate(90, 90);
  pros::delay(200);
  // setArm(-127);
  setRoller(0, 127);

  // drive(625, 90);
  // pros::delay(10);
  // drive(425, 75);
  // pros::delay(10);

  // driveTime(750, 90);
  // pros::delay(50);
  // driveTime(550, 70); //***************************************** GET 15 BALL

  driveTime(1300, 80) ;
  setArm(127);
  drive(250, 60);
  pros::delay(100);
  drive(-175, 60);

  rotate(90, 90);
  pros::delay(100);
  // driveTime(825, -80);
  driveTime(700, -85);
  pros::delay(50);
  driveTime(225, -70); //***************************************** GET 16 BALL

  drive(1925, 100);
  pros::delay(100);
  rotate(92, 90);
  pros::delay(100);

  setArm(-127);
  driveTime(1200, 80) ;
  pros::delay(50);
  setArm(127);

  driveTime(100, -60);
  driveTime(200, 60);
  driveTime(100, 80);
  driveTime(100, 80);

  setRoller(127, 127);
  pros::delay(500);


  setRoller(0, 127);
  driveTime(300, 60);

  armTime(600, 127);
  setRoller(0, 0);
  setArm(-127);
  drive(-200, 127);
  setArm(0);
}
