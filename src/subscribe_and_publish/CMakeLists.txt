cmake_minimum_required(VERSION 3.8)
project(subscribe_and_publish)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


add_executable(publisher src/publisher.cpp src/xingmaicx_rostopic.cpp src/xingmaicx_rostopic_log.cpp) 
ament_target_dependencies(publisher rclcpp std_msgs geometry_msgs)
add_executable(subscribe1 src/subscribe1.cpp)
ament_target_dependencies(subscribe1 rclcpp std_msgs geometry_msgs)

install(TARGETS
  publisher
  subscribe1
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
