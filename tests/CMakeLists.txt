# first test
add_executable(test_controller test_controller.cpp ../src/controller.cpp)
target_link_libraries(test_controller PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_controller)
