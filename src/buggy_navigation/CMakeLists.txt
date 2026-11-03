cmake_minimum_required(VERSION 3.20)
project(buggy_navigation)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(ackermann_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

# ==============================================================================
# 1. Define Library Targets
# ==============================================================================
add_library(gps_utils SHARED
  src/gps_utils.cpp
)

target_include_directories(gps_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# ==============================================================================
# 2. Define Executable Targets
# ==============================================================================
# Target: waypoint_manager
add_executable(waypoint_manager
  src/waypoint_manager.cpp
)

target_link_libraries(waypoint_manager PRIVATE
  rclcpp::rclcpp
  nav_msgs::nav_msgs
  geometry_msgs::geometry_msgs
  ackermann_msgs::ackermann_msgs
  tf2::tf2
  tf2_geometry_msgs::tf2_geometry_msgs
)

target_include_directories(waypoint_manager PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Target: test_gps
add_executable(test_gps
  src/test_gps.cpp
)

target_link_libraries(test_gps PRIVATE
  gps_utils
)

target_include_directories(test_gps PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# ==============================================================================
# 3. Install Rules (Fixed Library Destination)
# ==============================================================================
# Fix: Install the library target into the global 'lib' directory
install(TARGETS gps_utils
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install executable targets into package-specific directory
install(TARGETS test_gps waypoint_manager
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

# ==============================================================================
# 4. Testing & Package Export
# ==============================================================================
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
