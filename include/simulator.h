/**
 * @file simulator.h
 * @brief Header file for Simulator class, SimParams and Cart.
 *
 * This file contains declarations for the simulation parameters struct, Cart
 * Struct and the Simulator class, which are used for simulating the behavior of
 * an inverted pendulum system. It also includes declarations for related data
 * structures and synchronization primitives used in the simulation.
 *
 * @author Utkarsh Raj
 * @date 10-April-2024
 */

#pragma once

#include "controller.h"
#include <array>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <memory>
#include <mutex>

/**
 * @brief Struct containing parameters for simulation.
 */
struct SimParams {
  double simulation_time = 1000; ///< Duration of simulation in seconds
  double delta_t = 0.0001;       ///< Time step for simulation
  double g = 9.81;               ///< Acceleration due to gravity
  double ref_angle =
      M_PI_4 /
      8; ///< Reference angle (0 is vertical, must be between -pi and pi)
  int delay = 0;  ///< Delay in microseconds
  int jitter = 0; ///< Jitter in microseconds
};

/**
 * @brief Struct containing parameters for the cart.
 */
struct Cart {
  double M = 5;             ///< Mass of cart
  double m = 0.5;           ///< Mass of pendulum
  double len = 1;           ///< Pendum center of mass to pivot point
  double I = m * len * len; ///< Moment of inertia of pendulum
};

/**
 * @brief Simulator class for simulating the inverted pendulum.
 */
class Simulator {

public:
  std::unique_ptr<Controller> m_controller; ///< Controller object
  SimParams m_params;                       ///< Simulation Parameters
  Cart m_cart;                              ///< Cart object

  // Synchronization variables between simulator and comm server
  std::atomic<bool> g_start{false}; ///< Flag to start the simulation
  std::atomic<bool> g_reset{false}; ///< Flag to reset the simulation
  std::atomic<bool> g_pause{true};  ///< Flag to pause the simulation
  std::condition_variable
      g_pause_cv; ///< Condition variable for pausing the simulation
  std::condition_variable
      g_start_cv;           ///< Condition variable for starting the simulation
  std::mutex g_start_mutex; ///< Mutex for Synchronization of simulation start
                            ///< between simulator and comm server
  std::mutex g_pause_mutex; ///< Mutex for Synchronization of simulation pause
                            ///< between simulator and comm server

  // run time variables
  double T = 0; ///< Current simulation time
  double F = 0; ///< External force on the cart

  // State of the pendulum
  const int buffer_size =
      100; ///< Size of the circular buffer for storing theta values
  std::array<double, 100> theta; ///< Circular buffer to store values of theta
  std::array<double, 2> theta_dot{
      0, 0}; ///< Last two angular velocities of the pendulum
  std::array<double, 2> theta_dot_dot{
      0, 0}; ///< Last two angular accelerations of the pendulum

  // State of the cart
  std::array<double, 2> x{0, 0};         ///< Last two positions of the cart
  std::array<double, 2> x_dot{0, 0};     ///< Last two velocities of the cart
  std::array<double, 2> x_dot_dot{0, 0}; ///< Last two accelerations of the cart

  // Generic solution to system of two equations
  const double c_ml = m_cart.m * m_cart.len; ///< Constant term
  const double B = m_cart.M + m_cart.m;      ///< Constant term
  const double a =
      m_cart.I + m_cart.m * std::pow(m_cart.len, 2); ///< Constant term

  // updates every time step
  double A = 0;     ///< State variable
  double b = 0;     ///< State variable
  double C = 0;     ///< State variable
  double c = 0;     ///< State variable
  double E = 0;     ///< Total energy of the system
  double error = 0; ///< Difference between reference angle and current angle
  int i = 0;        ///< Index in circular buffer for theta values

  /**
   * @brief Deleted default constructor.
   */
  Simulator() : m_controller(std::make_unique<PIDController>()) {
    theta.fill(0);
    theta.at(0) = M_PI_4 / 8;
  };

  /**
   * @brief Constructs a Simulator object with the specified controller,
   * simulation parameters, and cart parameters.
   *
   * @param controller Reference to the controller
   * @param params Reference to the simulation parameters
   * @param cart Reference to the cart parameters
   */
  Simulator(std::unique_ptr<Controller> controller, const SimParams &params,
            const Cart &cart)
      : m_controller(std::move(controller)), m_params(params), m_cart(cart) {}
  /**
   * @brief Runs the simulator.
   *
   * This function starts the simulation loop, updating the state of the system
   * at each time step based on the controller output and simulation parameters.
   */
  void run_simulator();

  /**
   * @brief Updates the simulation parameters.
   * Function is called by the communication server to update the simulation
   * parameters, once the client sends the new parameters.
   * @param ref Reference angle for the inverted pendulum.
   * @param delay Delay in microseconds for synchronization with the
   * communication server.
   * @param jitter Jitter in microseconds for synchronization with the
   * communication server.
   */
  void update_params(double ref, int delay, int jitter);

  /**
   * @brief Resets the simulator to its initial state.
   * Function is called by the communication server to reset the simulator, once
   * the client sends the reset command. This function resets the state
   * variables of the simulator, allowing for a fresh start of the simulation.
   */
  void reset_simulator();
};
