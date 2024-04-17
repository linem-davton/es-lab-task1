
# Getting Started

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Building the Project](#building-the-project)
- [Usage](#usage)

## Introduction

A C++ simulator that implements PID control for an inverted pendulum system. It provides a simulation environment where the user can test and evaluate different PID controller parameters to stabilize the inverted pendulum.

The simulator also includes an HTTP server component that allows external control and monitoring of the simulation parameters via frontend requests. This enables users to interact with the simulation in real-time through a web-based interface.

## Features

- Simulates PID control of an inverted pendulum system.
- Dynamically adjustable PID controller parameters (kp, kd, ki).
- Real-time visualization and monitoring of simulation.
- HTTP server for remote control and monitoring via web interface.

## Dependencies 

- CMake - For building the project .
- Boost - For HTTP server, relase version can be downloaded from [boost website](https://www.boost.org/users/download/)
- nlohmann/json - json.hpp file  can be downloaded from [github](https://github.com/nlohmann/json/releases/tag/v3.11.3)

## Building the Project

To install the simulator, follow these steps:

1. Clone the repository to your local machine:

    ```bash
    git clone <proj-dir>
    ```

2. Navigate to the project directory:

    ```bash
    cd <proj-dir>
    ```

3. Create a build and libs directory in the project directory

    ```bash
    mkdir build
    mkdir libs
    ```

4. Place the unzipped boost dir in the *<proj-dir>/libs* directory
5. Place the json.hpp file in the *<proj-dir>/libs/nlohmann* directory

6. Navigate to the build directory:

    ```bash
    cd build
    ```

7. Configure the project with CMake:

    ```bash
    cmake ..
    ```

8. Build the project:

    ```bash
    make
    ```

If you encounter any issues during the build process, please check the dependencies and ensure that they are correctly installed and configured. Make sure CMakeLists.txt is correctly configured to include the required libraries.

## Usage

To use the simulator, follow these steps:

1. Navigate to the build directory where the project was built:

    ```bash
    cd <proj-dir>/build
    ```

2. Run the simulator binary:

    ```bash
    ./simulator
    ```

3. Download the frontend code can be from [github](https://github.com/linem-davton/inverted_pendulum_frontend/releases/tag/v1.0.0)

4. Open a web browser and navigate to the frontend server address (default: `http://localhost:3000`).

5. Use the web interface to control and monitor the simulation parameters. You can start, stop, and adjust the simulation settings as needed.

6. Interact with the simulator via the web interface to observe the behavior of the inverted pendulum system under different control conditions.

By following these steps, you can run the simulator and control it using the web interface provided by the frontend server.

