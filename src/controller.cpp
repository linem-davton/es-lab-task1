/**
 * @file controller.cpp
 * @brief Implementation file for the PIDController class.
 *
 * This file contains the implementation of the PIDController class,
 * which implements a PID (Proportional-Integral-Derivative) controller
 * for controlling the inverted pendulum system.
 *
 * @author [Your Name]
 * @date [Date]
 */

#include "controller.h"
#include <iostream>

PIDController::PIDController() { update_params(kp, kd, ki); }

void PIDController::setClamp(double max, double min) {
  ///@todo Implement setClamp for setting the output limits
}

double PIDController::output(double error) {
  ///@todo Implement the PID controller output calculation
}

void PIDController::update_params(double kp_, double kd_, double ki_) {
  ///@todo Implement the update_params function for PID controller
}
