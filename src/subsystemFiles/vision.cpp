#include "main.h"

//DEFINE
pros::Vision visionFront (14, pros::E_VISION_ZERO_CENTER);
pros::Vision visionUp (11, pros::E_VISION_ZERO_CENTER);
pros::Vision visionBack (4, pros::E_VISION_ZERO_CENTER);

pros::vision_signature_s_t BLUE_SIG =
pros::Vision::signature_from_utility(1, -3777, -2879, -3328, 12797, 16831, 14814, 3.100, 0);
pros::vision_signature_s_t RED_SIG =
pros::Vision::signature_from_utility(2, 7769, 9831, 8800, -833, 945, 56, 2.900, 0);
pros::vision_signature_s_t GREEN_SIG =
pros::Vision::signature_from_utility(3, -5213, -4527, -4870, -4129, -3527, -3828, 3.400, 0);

void alignObject (int vision_sersor, int sig) {
  pros::vision_object_s_t object_front_blue;
  object_front_blue = visionFront.get_by_sig(0, 1);

  pros::vision_object_s_t object_front_red;
  object_front_red = visionFront.get_by_sig(0, 2);

  pros::vision_object_s_t object_back_blue;
  object_back_blue = visionBack.get_by_sig(0, 1);

  pros::vision_object_s_t object_back_red;
  object_back_red = visionBack.get_by_sig(0, 2);

  pros::vision_object_s_t object_up_green;
  object_up_green = visionUp.get_by_sig(0, 3);

  int fb = object_front_blue.x_middle_coord;
  int fr = object_front_red.x_middle_coord;
  int bb = object_back_blue.x_middle_coord;
  int br = object_back_red.x_middle_coord;
  int ug = object_up_green.x_middle_coord;

  int speed = 30;

  if (fb > 400 || fb < -400) {
    fb = 0;
  }
  if (fr > 400 || fr < -400) {
    fb = 0;
  }
  if (bb > 400 || bb < -400) {
    fb = 0;
  }
  if (br > 400 || br < -400) {
    fb = 0;
  }
  if (ug > 400 || ug < -400) {
    fb = 0;
  }

  std::cout << " object_front_blue: " << fb <<
  " object_front_red: " << fr <<
  " object_back_blue: " << bb <<
  " object_back_red: " << br <<
  " object_up_green: " << ug  << std::endl;

  switch (vision_sersor) {
    case 1: // front vision sensor
      {
        if (sig == 1) { // blue
          if (fb != 0 || fb != 1 || fb != -1) {
            break;
          } else {
            int direction = -(abs(fb) / fb); //either 1 or -1
            rotateRPM(direction * speed);
          }
        } else if (sig == 2) { // red
          if (fr != 0 || fr != 1 || fr != -1) {
            break;
          } else {
            int direction = -(abs(fr) / fr); //either 1 or -1
            rotateRPM(direction * speed);
          }
        } else {
          break;
        }
      }
      case 2: // back vision sensor
        {
          if (sig == 1) { // blue
            if (bb != 0 || bb != 1 || bb != -1) {
              break;
            } else {
              int direction = -(abs(bb) / bb); //either 1 or -1
              rotateRPM(direction * speed);
            }
          } else if (sig == 2) { // red
            if (br != 0 || br != 1 || br != -1) {
              break;
            } else {
              int direction = -(abs(br) / br); //either 1 or -1
              rotateRPM(direction * speed);
            }
          } else {
            break;
          }
        }
        case 3: // back vision sensor
          {
            if (sig == 3) { // green
              if (ug != 0 || ug != 1 || ug != -1) {
                break;
              } else {
                int direction = -(abs(ug) / ug); //either 1 or -1
                rotateRPM(direction * speed);
              }
            } else {
              break;
            }
          }
    }
}


//HELPER FUNCTIONS
// double radtodeg(double rad) { return (double)((rad * 180) / PI); }
// double degtorad(double deg) { return (double)((deg * PI) / 180); }
// double inchtocm(double inch) { return (double)(inch * 2.54); }
// double cmtoinch(double cm) { return (double)(cm / 2.54); }
// double stob(double tickst) {
//   return (double)(tickst * (((4 * PI) / 360) / ((3.25 * PI) / 360)));
// }


// double distanceToObjectInches(pros::vision_object_s_t object, double height_mm) {
//   double focal_length_mm = 3.814;
//   double image_height_pixels = 400;
//   // https://photo.stackexchange.com/questions/12434/how-do-i-calculate-the-distance-of-an-object-in-a-photo
//   double sensor_height_mm = 260; // guessed pls change if actual value becomes availible
//   double distance_mm = 0;
//   distance_mm = (focal_length_mm * height_mm * image_height_pixels) / (object.height * sensor_height_mm);
//   return cmtoinch(distance_mm / 10); // mm to cm then to inches
// }

// double distanceToBiggestFlagInches(void) {
//   pros::vision_object_s_t object = visionFront.get_by_sig(0, frontCode);
//   //visionFront.get_by_sig(0, frontCode); // We should use color codes instead of simple sigs
//   double height_mm = 138;
//   double ret_val = 0.0;
//   ret_val = distanceToObjectInches(object, height_mm);
//   return ret_val;
// }

// void alignWithObject(int vision_sensor, double rpm) {
//   if (vision_sensor == 1) {
//     // visionFront.set_exposure(50);vision.set_auto_white_balance(true);
//     double middle = 316 / 2;
//     bool linedup = false;
//     pros::vision_object_s_t object;
//     while (!linedup) {
//       if (visionFront.get_object_count() > 0) {
//         object = visionFront.get_by_sig(0, frontCode);
//         if (object.x_middle_coord < middle - 5) {
//           setDriveBrakeModeBRAKE();
//           rotateRPM(-rpm); //-15
//         } else if (object.x_middle_coord > middle + 5) {
//           setDriveBrakeModeBRAKE();
//           rotateRPM(rpm); //15
//         } else {
//           linedup = true;
//           setDriveBrakeModeCOAST();
//           driveRPM(0);
//         }
//       } else {
//         driveRPM(0);
//       }
//     }
//   }
//   else if (vision_sensor == 2){ // = 2
//     // visionUp.set_exposure(50);
//     double middle = 316 / 2;
//     bool linedup = false;
//     pros::vision_object_s_t object;
//     while (!linedup) {
//       if (visionUp.get_object_count() > 0) {
//         object = visionUp.get_by_sig(0, 3);
//         if (object.x_middle_coord < middle - 5) {
//           setDriveBrakeModeBRAKE();
//           rotateRPM(-rpm); //-15
//         } else if (object.x_middle_coord > middle + 5) {
//           setDriveBrakeModeBRAKE();
//           rotateRPM(rpm); //15
//         } else {
//           linedup = true;
//           setDriveBrakeModeCOAST();
//           driveRPM(0);
//         }
//       } else {
//         driveRPM(0);
//       }
//     }
//   }
//   else if (vision_sensor == 3){ // = 3
//     // visionBack.set_exposure(50);
//     double middle = 316 / 2;
//     bool linedup = false;
//     pros::vision_object_s_t object;
//     while (!linedup) {
//       if (visionBack.get_object_count() > 0) {
//         object = visionBack.get_by_sig(0, backCode);
//         if (object.x_middle_coord < middle - 5) {
//           setDriveBrakeModeBRAKE();
//           rotateRPM(-rpm); //-15
//         } else if (object.x_middle_coord > middle + 5) {
//           setDriveBrakeModeBRAKE();
//           rotateRPM(rpm); //15
//         } else {
//           linedup = true;
//           setDriveBrakeModeCOAST();
//           driveRPM(0);
//         }
//       } else {
//         driveRPM(0);
//       }
//     }
//   }
// }
