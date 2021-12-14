#include "main.h"

//HELPER FUNCTIONS
void setDrive(int LF, int LB, int RF, int RB);
void resetDriveEncoders();
void resetQuadEncoders();
double avgDriveEncoderValue();
double avgQuadEncoderValue();
void setDriveBrakeModeCOAST();
void setDriveBrakeModeBRAKE();
//inline int power127(int t);

//DRIVER CONTROL FUNCTIONS
void setDriveMotors();

//AUTONOMOUS FUNCTIONS
void drive(int units, int voltage);
void driveBrake(int units, int voltage);
void driveRPM(int voltage);
void driveTime(int milliseconds, int voltage);
void rotate(int degrees, int voltage);
void rotateRPM(int voltage);
void rotateWithPID(int degrees, int voltage);
void rotateWithoutCorr(int degrees, int voltage);
void curve(int units, int leftVoltage, int rightVoltage);
void sideway(int units, int voltage);
void brake(int milliseconds);
