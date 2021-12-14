#include "main.h"

#include "autoSelect/selection.h"

#include "okapi/api.hpp"
using namespace okapi;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// pros::lcd::initialize();
	// pros::lcd::set_text(1, "7984 from Hongkong!");
	//
	// pros::lcd::register_btn1_cb(on_center_button);

  // LV_IMG_DECLARE(yeji);
	// lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	// lv_img_set_src(img1, &yeji);

	selector::init();

	//SET MOTOR BRAKE MODE
	driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rollerUp.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rollerDown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	armLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	armRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	//SENSORS
	// pros::ADIAnalogIn lineTrackerUp('H');
	// pros::ADIAnalogIn lineTrackerDown('G');

	pros::Optical opticalUp(2);
	pros::Optical opticalDown(8);
	opticalUp.disable_gesture();
	opticalDown.disable_gesture();
	opticalUp.set_led_pwm(50);
	opticalDown.set_led_pwm(50);

	pros::Vision visionFront (14, pros::E_VISION_ZERO_CENTER);
	pros::Vision visionUp (11, pros::E_VISION_ZERO_CENTER);
	pros::Vision visionBack (4, pros::E_VISION_ZERO_CENTER);

	// visionFront.set_white_balance(50);
	// visionUp.set_white_balance(100);
	// visionBack.set_white_balance(50);
	visionFront.set_auto_white_balance(true);
	visionUp.set_auto_white_balance(true);
	visionBack.set_auto_white_balance(true);

	pros::vision_signature_s_t BLUE_SIG =
	pros::Vision::signature_from_utility(1, -3777, -2879, -3328, 12797, 16831, 14814, 3.100, 0);
	pros::vision_signature_s_t RED_SIG =
	pros::Vision::signature_from_utility(2, 7769, 9831, 8800, -833, 945, 56, 2.900, 0);
	pros::vision_signature_s_t GREEN_SIG =
	pros::Vision::signature_from_utility(3, -5213, -4527, -4870, -4129, -3527, -3828, 3.400, 0);

	visionFront.set_signature(1, &BLUE_SIG);
	visionFront.set_signature(2, &RED_SIG);
	visionBack.set_signature(1, &BLUE_SIG);
	visionBack.set_signature(2, &RED_SIG);
	visionUp.set_signature(3, &GREEN_SIG);

	pros::vision_color_code_t frontCode = visionFront.create_color_code(1, 2);
	pros::vision_color_code_t backCode = visionBack.create_color_code(1, 2);

	pros::Distance distanceLeft(7);
	pros::Distance distanceRight(6);

	//ENCODER
	pros::ADIEncoder encoderBack ('C', 'D');
	pros::ADIEncoder encoderLeft ('E', 'F');
	pros::ADIEncoder encoderRight ('A', 'B');

	//GYRO
	pros::Imu imu_sensor(13);
	// imu_sensor.reset();
	// pros::ADIGyro gyro('G');
	pros::delay(5000);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	pros::Optical opticalUp(2);
	pros::Optical opticalDown(8);
	opticalUp.set_led_pwm(0);
	opticalDown.set_led_pwm(0);

	pros::Vision visionFront (14, pros::E_VISION_ZERO_CENTER);
	pros::Vision visionUp (11, pros::E_VISION_ZERO_CENTER);
	pros::Vision visionBack (4, pros::E_VISION_ZERO_CENTER);
	visionFront.set_led(COLOR_RED);
	visionUp.set_led(COLOR_RED);
	visionBack.set_led(COLOR_RED);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
	//pros::ADIGyro gyro('G');
	pros::Imu imu_sensor(13);
	pros::c::euler_s_t eu = imu_sensor.get_euler();

	pros::Optical opticalUp(2);
	pros::Optical opticalDown(8);
	opticalUp.set_led_pwm(50);
	opticalDown.set_led_pwm(50);

	pros::Vision visionFront (14, pros::E_VISION_ZERO_CENTER);
	pros::Vision visionUp (11, pros::E_VISION_ZERO_CENTER);
	pros::Vision visionBack (4, pros::E_VISION_ZERO_CENTER);
	visionFront.set_led(COLOR_PINK);
	visionUp.set_led(COLOR_PINK);
	visionBack.set_led(COLOR_PINK);

	if(selector::auton == 1){ ////////////////////////////////////////////////////////   run auton for Left Red
		//redLeft();
		/**************************************************     開機機     ************************************************************/
		setRoller(110, 110) ;
		setArm(-127) ;
		pros::delay(300) ;
		setRoller(0, 0) ;
		setArm(0) ;

		/**************************************************     第一柱     ************************************************************/
		setDrive(95, 95, 95, 95) ;
		pros::delay(125) ;
		setDrive(127, 127, 30, 30) ;
		setArm(127) ;
		pros::delay(500) ;
		setDrive(30, 30, 30, 30) ;
		setDriveBrakeModeBRAKE() ;
		setRoller(110, 110) ;
		pros::delay(200) ;
		setArm(0) ;
		pros::delay(350) ;
		setRoller(0, 110) ;
		pros::delay(200) ;

		/**************************************************     第二柱     ************************************************************/
	  setDriveBrakeModeBRAKE() ;
	  drive(-800, 127) ;
		setRoller(0, 0) ;

	  rotateWithPID(145, 95) ;
	  pros::delay(200) ;
		setDriveBrakeModeBRAKE() ;
	  driveTime(475, -90) ;
		pros::delay(150) ;
	  driveTime(300, -60) ;
	  pros::delay(400) ;
		setDriveBrakeModeBRAKE() ;
	  driveBrake(1450, 127) ;
		setDriveBrakeModeBRAKE() ;
		pros::delay(300) ;

		rotateWithPID(-90, 90) ;
		pros::delay(250) ;
		setDrive(80, 80, 80, 80) ;
		setArm(-127) ;
		pros::delay(550) ;
		setDrive(20, 20, 20, 20) ;
		setDriveBrakeModeBRAKE() ;
		setRoller(110, 110) ;
		pros::delay(500) ;
		// double A = imu_sensor.get_rotation();
		setArm(0) ;
		setRoller(0, -127) ;

		/**************************************************     第三柱     ************************************************************/
		setDriveBrakeModeBRAKE() ;
		driveTime(500, -100) ;
	  driveTime(400, -90) ;
	  driveTime(300, -80) ;
		pros::delay(400) ;
		// double B = imu_sensor.get_rotation();
		// int X = fabs(B) - fabs(A);
		// for (int i = 0; i < 50; i++)
		// {
		// 	if (X != 0) {
		// 		rotate(X, 40);
		// 		break;
		// 	}
		// 	pros::delay(1);
		// }

		/**************************************************     第四柱     ************************************************************/
		drive(200, 100) ;
		pros::delay(200) ;
		rotate(45, 80) ;
		pros::delay(200) ;
		drive(1200, 100) ;
		setDrive(80, 80, 80, 80) ;
		setArm(127) ;
		setRoller(110, 110) ;
		pros::delay(600) ;
		setDrive(30, 30, 30, 30) ;
		setDriveBrakeModeBRAKE() ;
		pros::delay(300) ;
		setArm(0) ;
		pros::delay(300) ;
		setRoller(0, 0) ;

		drive(-800, 127) ;
	  pros::delay(200) ;
		rotateWithPID(145, 90) ;
	}

	if(selector::auton == 2){ ////////////////////////////////////////////////////////   run auton for Right Red
		/**************************************************     開機機     ************************************************************/
		setRoller(0, 90) ;
		setArm(-127) ;
		pros::delay(275) ;
		setRoller(0, 0) ;
		setArm(0) ;

		/**************************************************     第一柱     ************************************************************/
		setDrive(95, 95, 95, 95) ;
		pros::delay(150) ;
		setDrive(127, 127, 30, 30) ;
		setArm(127) ;
		pros::delay(400) ;
		setDrive(30, 30, 30, 30) ;
		setDriveBrakeModeBRAKE() ;
		setRoller(127, 127) ;
		pros::delay(200) ;
		setArm(0) ;
		setRoller(127, 40) ;
		pros::delay(200) ;
		// setRoller(0, 110) ;
		setRoller(-90, 90) ;
		pros::delay(200) ;

		/**************************************************     第二柱     ************************************************************/
	  setDriveBrakeModeBRAKE() ;
	  drive(-440, 127) ;
		setRoller(0, 0) ;

		rotateWithoutCorr(90, 80) ;
	  pros::delay(200) ;
		setDriveBrakeModeBRAKE() ;
	  driveTime(600, -80) ;
	  driveTime(500, -60) ;
	  pros::delay(100) ;
		// driveBrake(1347, 127) ; red
		driveBrake(1400, 127) ;
		pros::delay(100) ;

		rotateWithPID(-89, 90) ;
		pros::delay(150) ;
		setDrive(60, 60, 60, 60) ;
		setArm(-127) ;
		pros::delay(850) ;
		setDrive(20, 20, 20, 20) ;
		setDriveBrakeModeBRAKE() ;
		setRoller(127, 127) ;
		pros::delay(500) ;
		setArm(0) ;
		setRoller(0, 0) ;
		pros::delay(450);

		/**************************************************     第三柱     ************************************************************/
		// imu_sensor.tare_rotation() ;
		setDriveBrakeModeBRAKE() ;
		driveTime(600, -90) ;
		driveTime(400, -70) ;
		driveTime(400, -60) ;
		// driveRPM(-100) ;
		// pros::delay(450) ;
		// driveRPM(-80) ;
		// pros::delay(400) ;
		// driveRPM(-60) ;
		// pros::delay(400) ;
		// driveRPM(0) ;
		pros::delay(300) ;
		setRoller(0, 5) ;
		pros::delay(50) ;
		// setDrive(20, 20, 20, 20) ;
		// pros::delay(100) ;
		drive(30, 20) ;
		pros::delay(100) ;
		setRoller(0, -127) ;
		pros::delay(400) ;

		/**************************************************     第四柱     ************************************************************/
		drive(100, 40) ;

		// double imu_rotation = imu_sensor.get_rotation();
		// printf("%f\n", imu_rotation);
		// for (int i = 0; i < 50; i++)
		// {
		// 	if (imu_rotation != 0) {
		// 		rotate(-imu_rotation, 40);
		// 		break;
		// 	}
		// 	pros::delay(10);
		// }
		// pros::delay(400) ;
		rotate(65, 80) ;
		pros::delay(300) ;
		setArm(-90) ;
		drive(1200, 127) ;
		setDrive(90, 90, 90, 90) ;
		setArm(0) ;
		pros::delay(400) ;
		setRoller(127, 0) ;
		pros::delay(500) ;
		setArm(0) ;
		setDrive(30, 30, 30, 30) ;
		setDriveBrakeModeBRAKE() ;
		pros::delay(600) ;
		setRoller(0, 0) ;
		// setArm(-100) ;
		// pros::delay(500);

		// drive(-800, 127) ;
		// setArm(0) ;
	  // pros::delay(200) ;
		// rotateWithPID(140, 95) ;
	}

	if(selector::auton == 3){ ////////////////////////////////////////////////////////   run auton for Do Nth Red
		// rotate(90, 90);
		imu_sensor.tare_rotation();
		setDriveBrakeModeBRAKE() ;
		driveRPM(-100) ;
		pros::delay(450) ;
		driveRPM(-80) ;
		pros::delay(400) ;
		driveRPM(-60) ;
		pros::delay(400) ;
		driveRPM(0) ;
		pros::delay(700) ;

		drive(200, 100) ;
		pros::delay(200) ;
		int imu_rotation = imu_sensor.get_rotation();
		printf("%i\n", imu_rotation);
		for (int i = 0; i < 50; i++)
		{
			if (imu_rotation != 0) {
				rotateWithoutCorr(imu_rotation, 30);
				break;
			}
			pros::delay(10);
		}
		driveTime(200, 127);
		/*
		rotateWithPID(45, 75) ;
		pros::delay(1000);
		double A = imu_sensor.get_rotation();
	  printf("get_rotation: %f\n", A);
		pros::delay(500);

		rotateWithPID(145, 95) ;
		pros::delay(1000);
		double X = imu_sensor.get_rotation();
	  printf("get_rotation: %f\n", X);
		pros::delay(500);

		rotateWithPID(90, 90);
		pros::delay(1000);
		double Y = imu_sensor.get_rotation();
	  printf("get_rotation: %f\n", Y);
		pros::delay(500);

		rotateWithPID(180, 100);
		pros::delay(1000);
		double Z = imu_sensor.get_rotation();
	  printf("get_rotation: %f\n", Z);
		pros::delay(500);
		*/
	}

	if(selector::auton == -1){ ////////////////////////////////////////////////////////   run auton for Left Blue
		double A = imu_sensor.get_rotation();
		/**************************************************     開機機     ************************************************************/
		rollerMode(1, 100, 127) ;
		/**************************************************     第一柱     ************************************************************/
		setDrive(127, 127, 127, 127);
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

		rotate(135, 90);
		double B = imu_sensor.get_rotation();
		printf("%f\n", B);
		pros::delay(500);
		drive(2500, 127);
		drive(250, 100);
		setDriveBrakeModeBRAKE();
		pros::delay(500);

		rotate(-45, 90);
		armMode(1, 127) ;
		pros::delay(500);
		drive(750, 70);
		setDrive(20, 20, 20, 20);
		setDriveBrakeModeBRAKE();
		rollerMode(0, 0, 110) ;
		pros::delay(900);
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
		rotate(135, 90);
	}

	if(selector::auton == -2){ ////////////////////////////////////////////////////////   run auton for Right Blue
		drive(400, 100);
		rotateWithPID(90, 90);
		// alignObject(3, 3);
		// driveTime(1000, 80);
		// pros::delay(500);
		// drive(-200, 90);
		// rotateWithoutCorr(10, 80);
		pros::delay(400);
		distanceCorr();
		drive(50, 90);
	}

	if(selector::auton == -3){ ////////////////////////////////////////////////////////   run auton for Do Nth Blue
		std::shared_ptr<OdomChassisController> chassis =
		ChassisControllerBuilder()
    .withMotors(
			{1, 15},  // Left motors are 7 & 9
			{-5, -20}) // Right motors are 8 & 10
    // .withGains(
    //     {0.001, 0, 0.0001}, // distance controller gains
    //     {0.001, 0, 0.0001}, // turn controller gains
    //     {0.001, 0, 0.0001}  // angle controller gains (helps drive straight)
    // )
		// green gearset, 4 inch wheel diameter, 11.5 inch wheel track
		.withDimensions(AbstractMotor::gearset::green, {{3.25_in, 26.5_cm}, imev5GreenTPR})
    .withSensors(
        ADIEncoder{'E', 'F', true}, // left encoder in ADI ports A & B
        ADIEncoder{'A', 'B'},  // right encoder in ADI ports C & D (reversed)
        ADIEncoder{'C', 'D'}  // middle encoder in ADI ports E & F
    )
		// specify the tracking wheels diameter (2.75 in), track (7 in), and TPR (360)
    .withOdometry({{2.75_in, 41_cm}, quadEncoderTPR}, StateMode::FRAME_TRANSFORMATION)
    .buildOdometry(); // build an odometry chassis

		// set the state to zero
		chassis->setState({0_in, 0_in, 0_deg});
		// turn 45 degrees and drive approximately 1.4 ft
		chassis->driveToPoint({30_cm, 0_cm});
		// turn approximately 45 degrees to end up at 90 degrees
		//chassis->turnToAngle(90_deg);
		// turn approximately -90 degrees to face {5_ft, 0_ft} which is to the north of the robot
		//chassis->turnToPoint({5_ft, 0_ft});
	}

	if(selector::auton == 0){ ////////////////////////////////////////////////////////   run auton for Skills
		//skills();
		/**************************************************     開機機     ************************************************************/
		setRoller(127, 127) ;
		pros::delay(1000);
		pros::c::euler_s_t eu0 = imu_sensor.get_euler();
		int yaw0 = eu0.yaw;
		printf("yaw0: %i\n", yaw0);

		/**************************************************     第一柱     ************************************************************/
		setDrive(-110, -110, -110, -110);
		pros::delay(100) ;
		setDrive(-80, -80, -100, -100); //**************************************************     GET 1 BALL
		setRoller(0, 127) ;
		setArm(-127) ;
		pros::delay(600) ;
		setDrive(-85, -85, -95, -95);
		setArm(0) ;
		pros::delay(650) ;
		setDrive(-45, -45, -75, -75);  //**************************************************     GET 2 BALL
		pros::delay(450) ;
		pros::c::euler_s_t eu1 = imu_sensor.get_euler();
		int yaw1 = eu1.yaw;
		printf("yaw1: %i\n", yaw1);
		setRoller(0, 0) ;

		rotateWithoutCorr(-70, 90);
		brake(150);
		pros::c::euler_s_t eu1_1 = imu_sensor.get_euler();
		int yaw1_1 = eu1_1.yaw;
		printf("yaw1_1: %i\n", yaw1_1);

		setDrive(127, 127, 127, 127);
		setArm(127);
	  pros::delay(850);
		rotateWithoutCorr(7, 50) ;
		// driveTime(125, 127) ;
		setDrive(50, 50, 100, 100) ;
		pros::delay(150) ;
	  setDrive(30, 30, 30, 30);
	  setDriveBrakeModeBRAKE();
	  setRoller(127, 0);
	  pros::delay(300);
	  setRoller(127, 127);
	  pros::delay(400);
	  setRoller(0, 90);
	  pros::delay(350);
		setArm(0);
	  pros::delay(300);
	  setDriveBrakeModeCOAST();
		pros::c::euler_s_t eu1_2 = imu_sensor.get_euler();
		int yaw1_2 = eu1_2.yaw;
		printf("yaw1_2: %i\n", yaw1_2);
	  setRoller(-100, -127) ;
		setArm(-90);

		/**************************************************     第二柱     ************************************************************/
		drive(-850, 90);
		setArm(0);
		setRoller(0, 127) ;
		curve(-450, 127, 14) ;
		pros::delay(200);
		drive(-500, 100); //**************************************************     GET 3 BALL
		// setRoller(0, 0) ;
		pros::c::euler_s_t eu1_3 = imu_sensor.get_euler();
		int yaw1_3 = eu1_3.yaw;
		printf("yaw1_3: %i\n", yaw1_3);
		driveTime(150, 40) ;
		pros::delay(200);
		rotateWithPID(84, 90);

	  driveTime(400, 90);
		driveTime(700, 60);
		driveTime(200, 40);
	  pros::delay(10);
		setArm(127);
	  setDrive(25, 25, 25, 25);
	  setDriveBrakeModeBRAKE();
	  setRoller(127, 0);
	  pros::delay(200);
	  setRoller(127, 127);
	  pros::delay(350);
	  setRoller(0, 90);
		setArm(0);
	  pros::delay(300);
	  setDriveBrakeModeCOAST();
		pros::c::euler_s_t eu1_4 = imu_sensor.get_euler();
		int yaw1_4 = eu1_4.yaw;
		printf("yaw1_4: %i\n", yaw1_4);
	  setRoller(0, 0) ;

	  /**************************************************     第三柱     ************************************************************/
	  pros::delay(200);
	  setArm(-127);
	  drive(-150, 50);
		setArm(0);
		pros::delay(200);

		rotateWithPID(-93, 90);
		// distanceCorr();
		pros::c::euler_s_t eu2 = imu_sensor.get_euler();
		int yaw2 = eu2.yaw;
		printf("yaw2: %i\n", yaw2);
		int yawA = yaw1 - 180;
		printf("yawA: %i\n", yawA);
		if (yaw2 > yawA) {
			int yawA1 = yaw2 - yawA;
			printf("yawA1: %i\n", yawA1);
			if (yawA1 <= 2) {
				pros::delay(1);
			}
			else {
				// rotate(-yawA1 , 30);
				rotateWithoutCorr(-(yawA1 - 2) , 30) ;
			}
		} else if (yaw2 < yawA) {
			int yawA2 = yaw2 - yawA;
			printf("yawA2: %i\n", yawA2);
			if (yawA2 >= -2) {
				pros::delay(1);
			}
			else {
				// rotate(-yawA2 , 30);
				rotateWithoutCorr(-(yawA2 + 2) , 30) ;
			}
		}

	  // setDrive(-127, -127, 15, 15);
	  // pros::delay(600);
	  // setDrive(0, 0, 0, 0);
	  // pros::delay(100);
	  setRoller(127, 127);
		setArm(-127);
	  drive(-300, 90);
		setArm(0);
	  setRoller(0, 127);
	  pros::delay(200);
	  setDriveBrakeModeBRAKE();
	  drive(-400, 100); //**************************************************     GET 4 BALL
	  setDriveBrakeModeCOAST();

	  pros::delay(100);
	  rotate(35, 70);
	  driveTime(350, -90);
	  pros::delay(200);
	  setDriveBrakeModeBRAKE();
	  setDrive(-75, -75, -50, -50); //**************************************************     GET 5 BALL
		pros::delay(550);
		driveTime(300, -70);
		setDriveBrakeModeCOAST();
		pros::c::euler_s_t eu3 = imu_sensor.get_euler();
		int yaw3 = eu3.yaw;
		printf("yaw3: %i\n", yaw3);
	  setRoller(0, 0);

		rotateWithoutCorr(60, 95);
		// brake(400);

	  setDrive(127, 127, 127, 127);
		setArm(90);
	  pros::delay(850);
		driveTime(100, -127) ;
		rotateWithoutCorr(9, 80) ;
		// pros::delay(50);
		// rotateWithoutCorr(10, 127) ;
		driveTime(175, 127) ;
		pros::delay(50);
	  setDrive(30, 30, 30, 30);
	  setDriveBrakeModeBRAKE();
	  setRoller(127, 0);
	  pros::delay(300);
	  setRoller(127, 127);
	  pros::delay(400);
	  setRoller(0, 90);
	  pros::delay(350);
		setArm(0);
	  pros::delay(300);
	  setDriveBrakeModeCOAST();
		setArm(-90);
		setRoller(-90, -127) ;

	  /**************************************************     第四柱     ************************************************************/
		drive(-950, 90);
		setArm(0);
		setRoller(0, 127) ;
		curve(-425, 127, 14) ;
		pros::delay(200);
		drive(-500, 100); //**************************************************     GET 6 BALL
		// setRoller(0, 0) ;
		driveTime(100, 40) ;
		pros::delay(200);
		// rotateWithPID(84, 90);

	  driveTime(175, 40);
	  pros::delay(50) ;
		rotateWithPID(90, 95);
		setArm(127);
	  driveTime(800, 90); //**************************************************     GET 7 BALL
	  pros::delay(10);
	  driveTime(300, 60);
	  pros::delay(100);
		setDriveBrakeModeBRAKE();
	  setRoller(127, 0);
	  pros::delay(100);
	  setRoller(127, 90);
	  pros::delay(700);
	  setRoller(0, 90);
		setArm(0);
	  pros::delay(300);
	  setDriveBrakeModeCOAST();
	  setRoller(0, 0) ;

	  /**************************************************     第五柱     ************************************************************/
	  pros::delay(200);
	  setArm(-127);
	  setRoller(-127, -127);
	  drive(-400, 90);
		setArm(0);
	  pros::delay(200);
		rotateWithPID(90, 95);
	  pros::delay(200);

		pros::c::euler_s_t eu4 = imu_sensor.get_euler();
		int yaw4 = eu4.yaw;
		printf("yaw4: %i\n", yaw4);
		int yawB = yaw3 + 270;
		printf("yawB: %i\n", yawB);
		if (yaw3 > yawB) {
			int yawB1 = yaw4 - yawB;
			printf("yawB1: %i\n", yawB1);
			if (yawB1 <= 2) {
				pros::delay(1);
			}
			else {
				rotateWithoutCorr(yawB1 - 3, 30) ;
			}
		} else if (yaw4 < yawB) {
			int yawB2 = yaw4 - yawB;
			printf("yawB2: %i\n", yawB2);
			if (yawB2 >= -2) {
				pros::delay(1);
			}
			else {
				rotateWithoutCorr(-(yawB2) - 3 , 30) ;
			}
		}
		pros::delay(100);
	  setRoller(0, 127);
		setArm(-90);

	  driveTime(1250, 90) ;
	  setArm(127);
	  drive(250, 60);
	  pros::delay(100);
	  drive(-175, 60); //**************************************************     GET 8 BALL

	  rotate(80, 70);
	  pros::delay(100);
	  driveTime(750, -90);
	  pros::delay(50);
	  driveTime(350, -75); //*****************************************     GET 9 BALL
		pros::delay(150);
		pros::c::euler_s_t eu5 = imu_sensor.get_euler();
		int yaw5 = eu5.yaw;
		printf("yaw5: %i\n", yaw5);

		rotateWithoutCorr(-65, 95);
		// brake(400);

		setDrive(127, 127, 127, 127);
		setArm(90);
	  pros::delay(850);
		// driveTime(100, -127) ;
		// rotateWithoutCorr(-9, 80) ;
		// driveTime(125, 127) ;
		// pros::delay(50);
	  setDrive(30, 30, 30, 30);
	  setDriveBrakeModeBRAKE();
	  setRoller(127, 0);
	  pros::delay(300);
	  setRoller(127, 127);
	  pros::delay(400);
	  setRoller(0, 90);
	  pros::delay(350);
		setArm(0);
	  pros::delay(300);
	  setDriveBrakeModeCOAST();
		setArm(-90);
		setRoller(-90, -127) ;

	  /**************************************************     第六柱     ************************************************************/
		drive(-1150, 90);
		setArm(0);
		setRoller(0, 127) ;
		curve(-400, 127, 14) ;
		pros::delay(200);
		drive(-250, 100); //**************************************************     GET 10 BALL
		// setRoller(0, 0) ;
		driveTime(150, 40) ;
		pros::delay(200);
		rotateWithPID(90, 95);

		driveTime(400, 90);
		driveTime(700, 60);
		driveTime(200, 40);
		pros::delay(10);
		setArm(127);
		setDrive(25, 25, 25, 25);
		setDriveBrakeModeBRAKE();
		setRoller(127, 0);
		pros::delay(200);
		setRoller(127, 127);
		pros::delay(350);
		setRoller(0, 90);
		setArm(0);
		pros::delay(300);
		setDriveBrakeModeCOAST();
		setRoller(0, 0) ;

	  /**************************************************     第七柱     ************************************************************/
		pros::delay(200);
	  setArm(-127);
	  drive(-150, 50);
		setArm(0);
		pros::delay(200);

		rotateWithPID(-93, 90);
		// distanceCorr();
		pros::c::euler_s_t eu6 = imu_sensor.get_euler();
		int yaw6 = eu6.yaw;
		printf("yaw6: %i\n", yaw6);
		int yawC = yaw5 + 180;
		printf("yawC: %i\n", yawC);
		if (yaw6 > yawC) {
			int yawC1 = yaw6 - yawC;
			printf("yawC1: %i\n", yawC1);
			if (yawC1 <= 2) {
				pros::delay(1);
			}
			else {
				rotateWithoutCorr(-(yawC1 - 2) , 30) ;
			}
		} else if (yaw6 < yawC) {
			int yawC2 = yaw6 - yawC;
			printf("yawC2: %i\n", yawC2);
			if (yawC2 >= -2) {
				pros::delay(1);
			}
			else {
				rotateWithoutCorr(-(yawC2 + 2) , 30) ;
			}
		}

		setRoller(127, 127);
	  drive(-300, 90);
	  setRoller(0, 127);
	  pros::delay(200);
	  setDriveBrakeModeBRAKE();
	  drive(-400, 100); //**************************************************     GET 11 BALL
	  setDriveBrakeModeCOAST();

	  pros::delay(100);
	  rotate(35, 70);
		driveTime(750, -90);
	  pros::delay(50);
	  driveTime(350, -75); //*****************************************     GET 12 BALL
		pros::delay(150);
		pros::c::euler_s_t eu7 = imu_sensor.get_euler();
		int yaw7 = eu7.yaw;
		printf("yaw7: %i\n", yaw7);
	  setRoller(0, 0);

		rotateWithoutCorr(65, 95);
		// brake(400);

	  setDrive(110, 110, 110, 110);
		setArm(90);
	  pros::delay(750);
		// setDrive(-127, -127, -127, -127);
		// pros::delay(150);
		rotateWithoutCorr(15, 90) ;
		// pros::delay(50);
		// rotateWithoutCorr(10, 127) ;
		driveTime(150, 95) ;
		pros::delay(50);
	  setDrive(30, 30, 30, 30);
	  setDriveBrakeModeBRAKE();
	  setRoller(127, 0);
	  pros::delay(300);
	  setRoller(127, 127);
	  pros::delay(400);
	  setRoller(0, 90);
	  pros::delay(350);
		setArm(0);
	  pros::delay(300);
	  setDriveBrakeModeCOAST();
		setArm(-90);
		setRoller(-90, -127) ;

	  /**************************************************     第八柱     ************************************************************/
		drive(-350, 90);
		setArm(0);
		setRoller(0, 127) ;
		// curve(-425, 127, 14) ;
		rotate(-45, 70);
		pros::delay(200);
		drive(-1000, 100); //**************************************************     GET 13 BALL
		// setRoller(0, 0) ;
		driveTime(100, 40) ;
		pros::delay(200);
		// rotateWithPID(84, 90);

	  // driveTime(175, 40);
	  // pros::delay(50) ;
		rotateWithPID(90, 95);
		// setArm(127);
	  // driveTime(800, 90); //**************************************************     GET 14 BALL
		driveTime(325, 90);
	  pros::delay(10);
	  driveTime(300, 60);
	  pros::delay(100);
		setDriveBrakeModeBRAKE();
	  setRoller(127, 0);
	  pros::delay(100);
	  setRoller(127, 90);
	  pros::delay(400);
	  setRoller(0, 90);
		setArm(0);
	  pros::delay(300);
	  setDriveBrakeModeCOAST();
	  setRoller(0, 0) ;

		drive(-200 , 110);
		pros::delay(200);
		rotateWithPID(180, 120);
		pros::c::euler_s_t eu8 = imu_sensor.get_euler();
		int yaw8 = eu8.yaw;
		printf("yaw8: %i\n", yaw8);
		int yawD = yaw7 - yaw8;
		printf("yawD: %i\n", yawD);
		if (yaw7 > yaw8) {
			if (yawD <= 2) {
				pros::delay(1);
			}
			else {
				rotateWithoutCorr(yawD , 30) ;
			}
		} else if (yaw7 < yaw8) {
			if (yawD >= -2) {
				pros::delay(1);
			}
			else {
				rotateWithoutCorr(yawD , 30) ;
			}
		}

		pros::delay(200);
		setArm(-127);

	  driveTime(1700, 90) ;
	  pros::delay(50);
	  setArm(127);
		pros::c::euler_s_t eu9 = imu_sensor.get_euler();
		int yaw9 = eu9.yaw;
		printf("yaw9: %i\n", yaw9);
		int yawE = yaw7 - yaw9;
		printf("yawE: %i\n", yawE);
		if (yaw7 > yaw9) {
			if (yawE <= 2) {
				pros::delay(1);
			}
			else {
				rotateWithoutCorr(yawE , 30) ;
			}
		} else if (yaw7 < yaw9) {
			if (yawE >= -2) {
				pros::delay(1);
			}
			else {
				rotateWithoutCorr(yawE , 30) ;
			}
		}

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
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Imu imu_sensor(13);

	pros::Optical opticalUp(2);
	pros::Optical opticalDown(8);
	opticalUp.set_led_pwm(0);
	opticalDown.set_led_pwm(0);

	pros::Vision visionFront (14, pros::E_VISION_ZERO_CENTER);
	pros::Vision visionUp (11, pros::E_VISION_ZERO_CENTER);
	pros::Vision visionBack (4, pros::E_VISION_ZERO_CENTER);
	visionFront.set_led(COLOR_GREEN);
	visionUp.set_led(COLOR_GREEN);
	visionBack.set_led(COLOR_GREEN);

	visionFront.set_auto_white_balance(true);
	visionUp.set_auto_white_balance(true);
	visionBack.set_auto_white_balance(true);

	pros::vision_signature_s_t BLUE_SIG =
	pros::Vision::signature_from_utility(1, -3777, -2879, -3328, 12797, 16831, 14814, 3.100, 0);
	pros::vision_signature_s_t RED_SIG =
	pros::Vision::signature_from_utility(2, 7769, 9831, 8800, -833, 945, 56, 2.900, 0);
	pros::vision_signature_s_t GREEN_SIG =
	pros::Vision::signature_from_utility(3, -5213, -4527, -4870, -4129, -3527, -3828, 3.400, 0);

	visionFront.set_signature(1, &BLUE_SIG);
	visionFront.set_signature(2, &RED_SIG);
	visionBack.set_signature(1, &BLUE_SIG);
	visionBack.set_signature(2, &RED_SIG);
	visionUp.set_signature(3, &GREEN_SIG);

	pros::vision_color_code_t frontCode = visionFront.create_color_code(1, 2);
	pros::vision_color_code_t backCode = visionBack.create_color_code(1, 2);


	while(true) {
		// int leftJoystickY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		// int leftJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		// int LF = (leftJoystickY + leftJoystickX) ;
		// int LB = (leftJoystickY + leftJoystickX) ;
		// int RF = (leftJoystickY - leftJoystickX) ;
		// int RB = (leftJoystickY - leftJoystickX) ;
		// printf("LF %i\n", LF);
		// printf("LB %i\n", LB);
		// printf("RF %i\n", RF);
		// printf("RB %i\n", RB);

		// pros::vision_object_s_t rtn = visionUp.get_by_size(0);
		// std::cout << "sig: " << rtn.signature;

		// visionFront.read_by_sig(0, 1, 3, object_arr);
		// std::cout << "sig: " << object_arr[0].signature;

		// NTH = 30 - 45
		// BLUE = 49-250
		// RED = < 35
		// printf("Hue value: %lf \n", optical_sensor.get_hue());
		// std::cout << "opticalUp: " << opticalUp.get_hue() << " opticalDown:" << opticalDown.get_hue() << std::endl;

		// if (opticalUp.get_hue() < 34) {
		// 	std::cout << "opticalUp: RED" << std::endl;
		// } else if (opticalUp.get_hue() > 46 && opticalUp.get_hue() < 250 ) {
		// 	std::cout << "opticalUp: BLUE" << std::endl;
		// } else if (opticalUp.get_hue() > 30 && opticalUp.get_hue() < 45 ) {
		// 	std::cout << "opticalUp: NTH" << std::endl;
		// } else {
		// 	std::cout << "opticalUp: N/A " << opticalUp.get_hue() << std::endl;
		// }
		//
		// if (opticalDown.get_hue() < 34) {
		// 	std::cout << "opticalDown: RED" << std::endl;
		// } else if (opticalDown.get_hue() > 46 && opticalDown.get_hue() < 250 ) {
		// 	std::cout << "opticalDown: BLUE" << std::endl;
		// } else if (opticalDown.get_hue() > 30 && opticalDown.get_hue() < 45 ) {
		// 	std::cout << "opticalDown: NTH" << std::endl;
		// } else {
		// 	std::cout << "opticalDown: N/A " << opticalDown.get_hue() << std::endl;
		// }

		// int DigitalA = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
		//
		// if (DigitalA > 0) {
		// 	imu_sensor.tare_rotation();
		// }
		//
		// double A = imu_sensor.get_rotation();
		// printf("get_rotation: %f\n", A);

		pros::vision_object_s_t object;
		object = visionFront.get_by_sig(0, 1);
		// std::cout << " x_middle_coord: " << object.x_middle_coord << " y_middle_coord: " << object.y_middle_coord << std::endl;

		int DigitalY = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
		int DigitalA = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

		// pros::c::quaternion_s_t qt = imu_sensor.get_quaternion();
    // printf("IMU quaternion: {x: %f, y: %f, z: %f, w: %f}\n", qt.x, qt.y, qt.z, qt.w);
		// std::cout << "IMU quaternion: {x: " << qt.x << ", y: " << qt.y << ", z: " << qt.z << ", w: " << qt.w << std::endl;

		// pros::c::euler_s_t eu = imu_sensor.get_euler();
    // printf("IMU euler angles: {pitch: %f, roll: %f, yaw: %f}\n", eu.pitch, eu.roll, eu.yaw);
		// std::cout << "IMU euler angles: {pitch: " << eu.pitch << ", roll: " << eu.roll << ", yaw: " << eu.yaw << std::endl;

		// pros::c::imu_gyro_s_t gyro = imu_sensor.get_gyro_rate();
    // printf("IMU gyro values: {x: %f, y: %f, z: %f}\n", gyro.x, gyro.y, gyro.z);

		if (DigitalA == 1) {
			imu_sensor.tare_rotation();
		}

		// if (DigitalA == 1) {
		// 	ball_sorting(true);
		// } else if (DigitalY == 1) {
		// 	ball_sorting(false);
		// } else if (DigitalA == 1 && DigitalY == 1) {
		// 	alignObject(1, 2);
		// }

		setDriveMotors();
		setRollerMotors();
		//setRollerCaseMotors();
		setArmMotors();
		pros::delay(5);
	}
}
