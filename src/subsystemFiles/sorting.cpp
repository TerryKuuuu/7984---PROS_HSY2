#include "main.h"

bool optical = false;

void ball_sorting(bool optical) {
  pros::Optical opticalUp(2);
  pros::Optical opticalDown(8);

  pros::Vision visionFront (14, pros::E_VISION_ZERO_CENTER);
  pros::Vision visionUp (11, pros::E_VISION_ZERO_CENTER);
  pros::Vision visionBack (4, pros::E_VISION_ZERO_CENTER);

  pros::vision_signature_s_t BLUE_SIG =
  pros::Vision::signature_from_utility(1, -3777, -2879, -3328, 12797, 16831, 14814, 3.100, 0);
  pros::vision_signature_s_t RED_SIG =
  pros::Vision::signature_from_utility(2, 7769, 9831, 8800, -833, 945, 56, 2.900, 0);
  pros::vision_signature_s_t GREEN_SIG =
  pros::Vision::signature_from_utility(3, -5213, -4527, -4870, -4129, -3527, -3828, 3.400, 0);

  pros::vision_object_s_t object_front_blue;
  object_front_blue = visionFront.get_by_sig(0, 1);

  pros::vision_object_s_t object_front_red;
  object_front_red = visionFront.get_by_sig(0, 2);

  int fb = object_front_blue.x_middle_coord;
  int fr = object_front_red.x_middle_coord;

  if (fb > 400 || fb < -400) {
    fb = 0;
  }
  if (fr > 400 || fr < -400) {
    fb = 0;
  }

  if (optical == false) {
    // opticalUp.set_led_pwm(0);
    // opticalDown.set_led_pwm(0);
    setRoller(0, 0);
  } else if (optical == true) {
    // opticalUp.set_led_pwm(50);
    // opticalDown.set_led_pwm(50);
    setRoller(0, 127);
    setArm(127);
    if (fb != 0) {
      while (opticalUp.get_hue() > 85 || opticalUp.get_hue() > 65) {
        pros::delay(10);
      }
      setRoller(0, 0);
      setArm(0);
    } else if (fr != 0) {
      while (opticalUp.get_hue() > 85 || opticalUp.get_hue() > 65) {
        pros::delay(10);
      }
      setRoller(127, 90);
    }
  }
}
