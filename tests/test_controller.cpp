#include "controller.h"
#include <gtest/gtest.h>

TEST(ControllerTest, BasicTest) {
  // Zero output when all gains are zero and error is zero
  PIDController controller;
  controller.update_params(0, 0, 0);
  double output = controller.output(0.0);
  EXPECT_NEAR(output, 0.0, 1e-6);
}

TEST(ControllerTest, IntegralTest) {
  // Integral term should accumulate error
  PIDController controller;
  controller.update_params(0, 0, 1.0);
  double output = controller.output(10.0);
  output = controller.output(10.0);
  output = controller.output(0.0);
  EXPECT_GT(output, 0);
}

TEST(ControllerTest, ProportionalTest) {
  // Proportiona term should respond to  magnitude of error
  PIDController controller;
  controller.update_params(1, 0, 0);
  double output = controller.output(0.0);
  EXPECT_NEAR(output, 0, 1e-6);
}
TEST(ControllerTest, ProportionalTest2) {
  // Proportional should respond to error
  PIDController controller;
  controller.update_params(2.0, 0, 0);
  double output1 = controller.output(10.0);
  double output2 = controller.output(20.0);
  EXPECT_GT(output2, output1);
}

TEST(ControllerTest, DerivativeTest) {
  // Derivative term should respond to change in error
  PIDController controller;
  controller.update_params(0, 1, 0);
  double output = controller.output(10.0);
  output = controller.output(10.0);
  output = controller.output(0.0);
  EXPECT_NE(output, 0);
}

TEST(ControllerTest, OutputTest) {
  PIDController controller;
  controller.update_params(1.0, 2.0, 3.0);
  double output = controller.output(10.0);
  EXPECT_NEAR(output, 1000.0, 1e-6);
}

TEST(ControllerTest, ResetTest) {
  PIDController controller;
  controller.update_params(1.0, 2.0, 3.0);
  double output = controller.output(20);
  output = controller.output(30);
  controller.reset();
  output = controller.output(0.0);
  EXPECT_NEAR(output, 0.0, 1e-6);
}
