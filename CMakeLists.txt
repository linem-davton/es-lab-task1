
# Always start with these two
cmake_minimum_required(VERSION 3.0)
project(Inverted_Pendulum)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setting C++ standard and Forcing
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

# Add include directories if there are any
include_directories(include)
include_directories(libs/boost libs/nlohmann)

# Adding Executables
add_executable (simulator src/main.cpp src/simulator.cpp src/controller.cpp src/server.cpp)

# Include Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)
