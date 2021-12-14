#include "main.h"

//RED:36 GREEN:18 BLUE:6

//MOTORS
pros::Motor armLeft(17, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor armRight(12, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rollerUp(16, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rollerDown(18, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftFront(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(7, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//SENSOR
//pros::Imu imu_sensor(12);
//pros::ADIGyro gyro('G');
//pros::ADIAnalogIn lineTrackerUp('H');
//pros::ADIAnalogIn lineTrackerDown('G');

//ENCODER
//pros::ADIEncoder encoderLeft ('C', 'D');
//pros::ADIEncoder encoderRight ('E', 'F');
//pros::ADIEncoder encoderBack ('A', 'B');

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);
