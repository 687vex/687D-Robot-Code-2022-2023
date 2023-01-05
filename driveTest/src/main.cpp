#include "main.h"
#include "pros/misc.h"
#include <string>

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
	
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Good luck, have fun!");
	pros::lcd::register_btn1_cb(on_center_button);	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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
	pros::Motor left_mtr1(11, true);
	pros::Motor left_mtr2(12, false);
	pros::Motor left_mtr3(13, true);
	pros::Motor right_mtr1(18, false);
	pros::Motor right_mtr2(19, true);
	pros::Motor right_mtr3(20, false);
	pros::Motor string(15, false);
	pros::Motor roller(14, false);
	//red
	left_mtr1.move(50);
	left_mtr2.move(50);
	left_mtr3.move(50);

	right_mtr1.move(10);
	right_mtr2.move(10);
	right_mtr3.move(1.0);
	roller.move(120);
	pros::delay(3500);
	left_mtr1.move(50);                                                                                            
	left_mtr2.move(50);
	left_mtr3.move(50);

	right_mtr1.move(50);
	right_mtr2.move(50);        
	right_mtr3.move (50); 
	// roller.move(120);
	roller.move(-120);
	pros::delay(500);


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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor right_mtr1(11, false);
	pros::Motor right_mtr2(12, false);
	pros::Motor right_mtr3(13, false);
	pros::Motor left_mtr1(17, true);
	pros::Motor left_mtr2(18, true);
	pros::Motor left_mtr3(19, true);
	pros::Motor flywheel(9, false);
	pros::Motor string(15, false);
	pros::Motor roller(14, false);
	//red
	// left_mtr1.move(5);
	// left_mtr2.move(5);
	// left_mtr3.move(5);

	// right_mtr1.move(50);
	// right_mtr2.move(50);
	// right_mtr3.move(50);

	// left_mtr1.move(10);
	// left_mtr2.move(10);
	// left_mtr3.move(10);

	// right_mtr1.move(50);
	// right_mtr2.move(50);
	// right_mtr3.move(50);
	
	// roller.move(120);

	// pros::delay(3500);
	// left_mtr1.move(50);                                                                                            
	// left_mtr2.move(50);
	// left_mtr3.move(50);

	// right_mtr1.move(50);
	// right_mtr2.move(50);
	// right_mtr3.move(50);
	// roller.move(120);
	// roller.move(-120);
	// pros::delay(1000);
	bool endgame = false;
	while (true) {
		int right = -master.get_analog(ANALOG_LEFT_Y);
   		int left = -master.get_analog(ANALOG_RIGHT_Y);
		bool OverrideRoller = false;
		bool OverrideString = false;
		
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			endgame = false;
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			endgame = true;
		}

		// if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			// roller.move(120);
		// } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			// roller.move(-120);
		// } else {
			// roller.brake();
		// }

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && endgame) {
			string.move(50);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && endgame) {
				string.move(-50);
		} else {
			string.brake();
		}
		

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			flywheel.move(128);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			flywheel.move(-128);
		} else {
			flywheel.brake();
		}
		

		if(left < 10 && left > -10){
			left = 0;
		}

		left_mtr1.move(left);
		left_mtr2.move(left);
		left_mtr3.move(left);


		if(right < 10 && right > -10){
			right = 0;
		}
		right_mtr1.move(right);
		right_mtr2.move(right);
		right_mtr3.move(right);
		pros::delay(20);


		pros::lcd::set_text(1, std::to_string(right_mtr1.get_voltage()));
		pros::lcd::set_text(2, std::to_string(right_mtr2.get_voltage()));
		pros::lcd::set_text(3, std::to_string(right_mtr3.get_voltage()));
		pros::lcd::set_text(4, std::to_string(left_mtr1.get_voltage()));
		pros::lcd::set_text(5, std::to_string(left_mtr2.get_voltage()));
		pros::lcd::set_text(6, std::to_string(left_mtr3.get_voltage()));
	}
}
