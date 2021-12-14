#include "main.h"

//DEFINE
pros::ADIEncoder encoderBack ('C', 'D');
pros::ADIEncoder encoderLeft ('E', 'F');
pros::ADIEncoder encoderRight ('A', 'B');
pros::Imu imu_sensor(13);
//pros::ADIGyro gyro('G');

//bool held = false;

//HELPER FUNCTIONS
void setDrive(int LF, int LB, int RF, int RB) {
  driveLeftFront = LF;
  driveLeftBack = LB;
  driveRightFront = RF;
  driveRightBack = RB;
}

void resetDriveEncoders() {
  driveLeftFront.tare_position();
  driveLeftBack.tare_position();
  driveRightFront.tare_position();
  driveRightBack.tare_position();
}

void resetQuadEncoders() {
  encoderLeft.reset();
  encoderRight.reset();
}

void setDriveBrakeModeCOAST() {
  driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void setDriveBrakeModeBRAKE() {
  driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

double avgDriveEncoderValue() {
  int DLF = driveLeftFront.get_position();
  int DLB = driveLeftBack.get_position();
  int DRF = driveRightFront.get_position();
  int DRB = driveRightBack.get_position();

  return (fabs(DLF) + fabs(DLB) + fabs(DRF) + fabs(DRB)) / 4;
}

double avgQuadEncoderValue() {
  int ER = encoderRight.get_value();
  int EL = encoderLeft.get_value();

  return (fabs(ER) + fabs(EL)) / 2;
}

/*inline int power127(int t) {
  return t > 127 ? 127 : t < -127 ? -127 : t;
}*/

//DRIVER CONTROL FUNCTIONS
void setDriveMotors() {
  int leftJoystickY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int leftJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  //int rightJoystickY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  //int rightJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  int DigitalUp = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
  int DigitalDown = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  int DigitalLeft = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
  int DigitalRight = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
  int DigitalA = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

  pros::Distance distanceLeft(7);
  pros::Distance distanceRight(6);
  int fixspeed = 30;

  if(abs(leftJoystickY) < 10)
    leftJoystickY = 0;
  if(abs(leftJoystickX) < 10)
    leftJoystickX = 0;
  /*
  if(abs(rightJoystickY) < 10)
    rightJoystickY = 0;
  if(abs(rightJoystickX) < 10)
    rightJoystickX = 0;
  */

  int r1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
  int r2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

  int hold = r1 && r2;

  int LF = 0;
  int LB = 0;
  int RF = 0;
  int RB = 0;
  /*int left1 = power127(leftJoystickY + leftJoystickX);
  int right1 = power127(leftJoystickY - leftJoystickX);

  int leftf = left1 + rightJoystickX;
  int leftb = left1 - rightJoystickX;
  int rightf = right1 - rightJoystickX;
  int rightb = right1 + rightJoystickX;*/

/*  if (hold && abs(left1) < 20 && abs(right1) < 20)
  {
    if (!held)
    {
      held = true;
      setDrive(0, 0);
    }
  }
  else if (leftJoystickY || leftJoystickX || rightJoystickX != 0)
  {
    driveLeftFront = power127(leftf);
    driveRightFront = power127(rightf);
    driveLeftBack = power127(leftb);
    driveRightBack = power127(rightb);
  }
  else
  {
    held = false;
    if (abs(DigitalUp) > 0)
    {
      driveR = 127;
      driveL = 127;
    }
    else if (abs(DigitalDown) > 0)
    {
      driveR = -127;
      driveL = -127;
    }
  }

  setDrive(driveL, driveR);*/

  //reset drive brake mode to COAST
  setDriveBrakeModeCOAST();

  if (hold > 0) {
    setDriveBrakeModeBRAKE();
    LF = 0;
    LB = 0;
    RF = 0;
    RB = 0;
//    if (leftJoystickY > 0 || leftJoystickX > 0) {
//      setDrive(leftJoystickY + leftJoystickX, leftJoystickY + leftJoystickX, leftJoystickY - leftJoystickX, leftJoystickY - leftJoystickX);
//    }
  }
  else if(abs(DigitalUp) > 0 && hold < 1) {
    LF = 127;
    LB = 127;
    RF = 127;
    RB = 127;
  }
  else if (abs(DigitalDown) > 0 && hold < 1) {
    LF = -127;
    LB = -127;
    RF = -127;
    RB = -127;
  }
  else if (abs(DigitalLeft) > 0 && hold < 1) {
    LF = -127;
    LB = -127;
    RF = 127;
    RB = 127;
  }
  else if (abs(DigitalRight) > 0 && hold < 1) {
    LF = 127;
    LB = 127;
    RF = -127;
    RB = -127;
  }
  else
  if(abs(DigitalA) > 0 && hold < 1) {
    if (distanceLeft.get() == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 1 || distanceLeft.get() + 1 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 2 || distanceLeft.get() + 2 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 3 || distanceLeft.get() + 3 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 4 || distanceLeft.get() + 4 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 5 || distanceLeft.get() + 5 == distanceRight.get() || distanceLeft.get() == distanceRight.get() + 6 || distanceLeft.get() + 6 == distanceRight.get()) {
      LF = 0;
      LB = 0;
      RF = 0;
      RB = 0;
    }
    else if (distanceLeft.get() > distanceRight.get()) {
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
  }
  else {
    LF = (leftJoystickY + leftJoystickX) ;
    LB = (leftJoystickY + leftJoystickX) ;
    RF = (leftJoystickY - leftJoystickX) ;
    RB = (leftJoystickY - leftJoystickX) ;
  }

  setDrive(LF, LB, RF, RB);

/*  int leftJoystickY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int leftJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

  if(abs(leftJoystickY) < 10)
    leftJoystickY = 0;
  if(abs(leftJoystickX) < 10)
    leftJoystickX = 0;

  int driveR = (leftJoystickY - leftJoystickX);
  int driveL = (leftJoystickY + leftJoystickX);
  setDrive(driveL, driveR);*/

/*  int drivePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
  setDrive(drivePower, drivePower);*/
}

//AUTONOMOUS FUNCTIONS
void drive(int units, int voltage) {
  pros::Imu imu_sensor(13);
  int driveL = 0;
  int driveR = 0;
  //define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset all encoders and gyro
  resetDriveEncoders();
  resetQuadEncoders();
  imu_sensor.tare_rotation();
  //gyro.reset();

  //drive until units are reached
  while(avgQuadEncoderValue() < abs(units)) {
    // driveL = voltage * direction ;
    // driveR = voltage * direction ;
    driveL = voltage * direction - imu_sensor.get_rotation();
    driveR = voltage * direction + imu_sensor.get_rotation();
    setDrive(driveL, driveL, driveR, driveR);
    pros::delay(10);
  }

  //brief brake
  if(voltage > 50) {
  setDrive(-10 * direction, -10 * direction, -10 * direction, -10 * direction);
  pros::delay(50);
  }

  //set drive back to neutral
  setDrive(0, 0, 0, 0);
}

void driveBrake(int units, int voltage) {
  setDriveBrakeModeBRAKE();
  pros::Imu imu_sensor(13);
  int driveL = 0;
  int driveR = 0;
  //define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset all encoders and gyro
  resetDriveEncoders();
  resetQuadEncoders();
  imu_sensor.tare_rotation();
  //gyro.reset();

  //drive until units are reached
  while(avgQuadEncoderValue() < abs(units)) {
    // driveL = voltage * direction ;
    // driveR = voltage * direction ;
    driveL = voltage * direction - imu_sensor.get_rotation();
    driveR = voltage * direction + imu_sensor.get_rotation();
    setDrive(driveL, driveL, driveR, driveR);
    pros::delay(10);
  }

  //brief brake
  if(voltage > 50) {
  setDrive(-10 * direction, -10 * direction, -10 * direction, -10 * direction);
  pros::delay(50);
  }

  //set drive back to neutral
  setDrive(0, 0, 0, 0);
  pros::delay(350);
  setDriveBrakeModeCOAST();
}

void driveRPM(int voltage) {
  //drive
  setDrive(voltage, voltage , voltage , voltage);
}

void driveTime(int milliseconds, int voltage) {
  int driveL = 0;
  int driveR = 0;
  //define a direction based on units provided
  int direction = abs(voltage) / voltage; //either 1 or -1

  //reset all encoders and gyro
  resetDriveEncoders();
  resetQuadEncoders();
  imu_sensor.tare_rotation();
  //gyro.reset();

  //drive until times are reached
  driveL = voltage - imu_sensor.get_rotation();
  driveR = voltage + imu_sensor.get_rotation();
  setDrive(driveL, driveL, driveR, driveR);
  for (int i = 0; i < milliseconds; i++)
  {
    if (i > milliseconds)
    {
      break;
    }
    pros::delay(1);
  }

  //brief brake
  if(voltage > 50) {
  setDrive(-10 * direction, -10 * direction, -10 * direction, -10 * direction);
  pros::delay(70);
  }

  //set drive back to neutral
  setDrive(0, 0, 0, 0);
}

/*void drive(int leftFrontUnits, int leftBackUnits, int rightFrontUnits, int rightBackUnits, int leftFrontVoltage, int leftBackVoltage, int rightFrontVoltage, int rightBackVoltage) {
  int leftFrontDirection = abs(leftFrontUnits) / leftFrontUnits; //either 1 or -1
  int leftBackDirection = abs(leftBackUnits) / leftBackUnits; //either 1 or -1
  int rightFrontDirection = abs(rightFrontUnits) / rightFrontUnits; //either 1 or -1
  int rightBackDirection = abs(rightBackUnits) / rightBackUnits; //either 1 or -1

  //reset all encoders and gyro
  resetDriveEncoders();

  //drive until units are reached
  while(driveLeftFront.get_position() < abs(leftFrontUnits)) {

  }
}*/

void rotate(int degrees, int voltage) {
  //define a direction based on units provided
  int direction = abs(degrees) / degrees; //either 1 or -1

  //reset gyro
  imu_sensor.tare_rotation();
  //gyro.reset();

  //rotate until units degree are reached
  setDriveBrakeModeBRAKE();
  setDrive(voltage * direction, voltage * direction, -voltage * direction, -voltage * direction);
  while(fabs(imu_sensor.get_rotation()) < abs(degrees)) {
    pros::delay(10);
  }

  setDrive(0, 0, 0, 0);

  //wait for the robot to totally stop
  pros::delay(100);

  //self-correcting
  if(fabs(imu_sensor.get_rotation()) > abs(degrees)) {
    setDrive(0.4 * -voltage * direction, 0.4 * -voltage * direction, 0.4 * voltage * direction, 0.4 * voltage * direction);
    while(fabs(imu_sensor.get_rotation()) > abs(degrees)) {
      pros::delay(10);
    }
  }
  else if (fabs(imu_sensor.get_rotation()) < abs(degrees)) {
    setDrive(0.3 * voltage * direction, 0.3 * voltage * direction, 0.3 * -voltage * direction, 0.3 * -voltage * direction);
    while(fabs(imu_sensor.get_rotation()) < abs(degrees)) {
      pros::delay(10);
    }
  }

  //brief brake
/*  setDrive(10 * direction, -10 * direction);
  pros::delay(50);*/

  //set drive back to neutral
  setDrive(0, 0, 0, 0);
  setDriveBrakeModeCOAST();
}

void rotateRPM(int voltage) {
  //rotate
  setDrive(voltage, voltage , -voltage , -voltage);

}

void rotateWithPID(int degrees, int voltage) {
  //define values based on units provided
  int direction = abs(degrees) / degrees; //either 1 or -1

  //reset gyro
  imu_sensor.tare_rotation();
  //gyro.reset();

  //rotate until units degree are reached
  setDriveBrakeModeBRAKE();

  //Fast, Normal, Slow
  // setDrive(voltage * direction, voltage * direction, -voltage * direction, -voltage * direction);
  // while(fabs(imu_sensor.get_rotation()) < 0.25 * abs(degrees)) {
  //   pros::delay(5);
  // }
  //
  // setDrive(0.5 * voltage * direction, 0.5 * voltage * direction, 0.5 * -voltage * direction, 0.5 * -voltage * direction);
  // while(fabs(imu_sensor.get_rotation()) < 0.8 * abs(degrees)) {
  //   pros::delay(5);
  // }
  //
  // setDrive(0.4 * voltage * direction, 0.4 * voltage * direction, 0.4 * -voltage * direction, 0.4 * -voltage * direction);
  // while(fabs(imu_sensor.get_rotation()) < abs(degrees)) {
  //   pros::delay(5);
  // }

  //Normal , Fast, Slow (180 deg)
  setDrive(0.7 * voltage * direction, 0.7 * voltage * direction, 0.7 * -voltage * direction, 0.7 * -voltage * direction);
  while(fabs(imu_sensor.get_rotation()) < 0.25 * abs(degrees)) {
    pros::delay(5);
  }

  setDrive(voltage * direction, voltage * direction, -voltage * direction, -voltage * direction);
  while(fabs(imu_sensor.get_rotation()) < 0.45 * abs(degrees)) {
    pros::delay(5);
  }

  setDrive(0.35 * voltage * direction, 0.35 * voltage * direction, 0.35 * -voltage * direction, 0.35 * -voltage * direction);
  while(fabs(imu_sensor.get_rotation()) < (abs(degrees) - 1.5)) {
    pros::delay(5);
  }

  //set drive back to neutral
  setDrive(0, 0, 0, 0);
  setDriveBrakeModeCOAST();
}

void rotateWithoutCorr(int degrees, int voltage) {
  //define a direction based on units provided
  int direction = abs(degrees) / degrees; //either 1 or -1

  //reset gyro
  imu_sensor.tare_rotation();
  //gyro.reset();

  //rotate until units degree are reached
  setDriveBrakeModeBRAKE();
  setDrive(voltage * direction, voltage * direction, -voltage * direction, -voltage * direction);
  while(fabs(imu_sensor.get_rotation()) < abs(degrees)) {
    pros::delay(10);
  }

  //set drive back to neutral
  setDrive(0, 0, 0, 0);
  setDriveBrakeModeCOAST();
}

void curve(int units, int leftVoltage, int rightVoltage) {
  //define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset all encoders and gyro
  resetDriveEncoders();
  resetQuadEncoders();
  imu_sensor.tare_rotation();
  //gyro.reset();

  setDriveBrakeModeBRAKE();

  int driveL = 0;
  int driveR = 0;

  //drive until units are reached
  while(avgQuadEncoderValue() < abs(units)) {
    driveL = leftVoltage * direction - imu_sensor.get_rotation();
    driveR = rightVoltage * direction + imu_sensor.get_rotation();
    setDrive(driveL, driveL, driveR, driveR);
    pros::delay(10);
  }

  //set drive back to neutral
  setDrive(0, 0, 0, 0);

  setDriveBrakeModeCOAST();
}

void sideway(int units, int voltage) {
  int LF = 0;
  int LB = 0;
  int RF = 0;
  int RB = 0;
  //define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset all encoders and gyro
  encoderBack.reset();

  //drive until units are reached
  //setDriveBrakeModeBRAKE();
  while(encoderBack.get_value() < abs(units)) {
    LF = -(voltage * direction) ;
    LB = voltage * direction ;
    RF = voltage * direction ;
    RB = -(voltage * direction) ;
    //LF = -(voltage * direction) - gyro.get_value();
    //LB = voltage * direction - gyro.get_value();
    //RF = voltage * direction + gyro.get_value();
    //RB = -(voltage * direction) + gyro.get_value();
    setDrive(LF, LB, RF, RB);
    pros::delay(10);
  }
  //setDriveBrakeModeCOAST();

  //brief brake
  /*setDrive(-10 * direction, -10 * direction, -10 * direction, -10 * direction);
  pros::delay(50);*/

  //set drive back to neutral
  setDrive(0, 0, 0, 0);
}

void brake(int milliseconds) {
  driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

  pros::delay(milliseconds);

  setDriveBrakeModeCOAST();
}
