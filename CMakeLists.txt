
# Always start with these two
cmake_minimum_required(VERSION 3.0)
project(Inverted_Pendulum)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setting C++ standard and Forcing
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# For third party libaries in code, required flag tells cmake to rasie error is not found
# find_package (cppzmq REQUIRED)

# Add include directories if there are any
include_directories(include)
include_directories(libs/boost libs/nlohmann)

# Adding Executables
add_executable (simulator src/main.cpp src/simulator.cpp src/controller.cpp src/server.cpp)



