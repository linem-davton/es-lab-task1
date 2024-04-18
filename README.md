
# Getting Started

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Building the Project](#building-the-project)
- [Usage](#usage)

## Introduction

A C++ simulator that implements PID control for an inverted pendulum system.
It provides a simulation environment where the user can test and evaluate
different PID controller parameters to stabilize the inverted pendulum.

The simulator also includes an HTTP server component that allows
external control and monitoring of the simulation parameters via frontend requests.
This enables users to interact with the simulation
in real-time through a web-based interface.

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
    git clone git@github.com:linem-davton/es-lab-task1.git
    ```

2. Navigate to the project directory:

    ```bash
    cd es-lab-task1
    ```

3. Create a build and libs directory in the project directory

    ```bash
    mkdir build
    mkdir libs
    mkdir libs/nlohmann
    ```

4. Rename the unzipped boost library folder to boost
  and place it in es-lab-task1/libs directory
5. Place the json.hpp file in the es-lab-task1/libs/nlohmann directory

6. Navigate to the build directory:

    ```bash
    cd build
    ```

7. Configure the project with CMake:

    ```bash
    cmake ..
    ```

8. Build the project:

Linux:

```bash
    make
```

Windows:
    - Use Visual Studio to open the project and build the solution.

If you encounter any issues during the build process,
please check the dependencies and ensure that they are correctly installed and configured.
Make sure CMakeLists.txt is correctly configured to include the required libraries.

## Usage

To use the simulator, follow these steps:

1. Navigate to the build directory where the project was built:

    ```bash
    cd es-lab-task1/build
    ```

2. Run the simulator binary:

    ```bash
    ./simulator
    ```

3. Go to [eslab1.pages.dev](https://eslab1.pages.dev)

4. Use the web interface to control and monitor the simulation parameters.
  You can start, stop, and adjust the simulation settings as needed.

5. Interact with the simulator via the web interface
  to observe the behavior of the inverted pendulum system
  under different control conditions.

Alternatively, you can run the simulator with the frontend server locally
to control and monitor the simulation via a web interface:

1. Download the frontend  from [github](https://github.com/linem-davton/inverted_pendulum_frontend/releases)

2. Follow the instructions in the frontend README to start the frontend server.

- Install npm and serve package and run the serve command in the dist directory

```BASH
      npm install -g serve
      serve
```

- On Windows, runinng `serve` in powsershell may require
  the following command to be run first

```BASH
    Set-ExecutionPolicy -ExecutionPolicy Unrestricted -Scope CurrentUser
```

3. Open a web browser and navigate to the frontend server address (default: `http://localhost:3000`).

By following these steps, you can run the simulator and control it
using the web interface provided by the frontend server.
## Documentation

Code documentation can be found at [eslab1doc](https://eslab1docs.pages.dev/)
