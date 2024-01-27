cmake_minimum_required(VERSION 3.8)
project(tugas2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# add executable and link libraries
add_executable(talker1 src/cpppub1.cpp)
ament_target_dependencies(talker1 rclcpp std_msgs)

add_executable(talker2 src/cpppub2.cpp)
ament_target_dependencies(talker2 rclcpp std_msgs)

add_executable(listener src/cppsub.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

# install executables
install(TARGETS
  talker1
  talker2
  listener
  DESTINATION lib/${PROJECT_NAME})

ament_package()
