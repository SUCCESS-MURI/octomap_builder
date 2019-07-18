cmake_minimum_required(VERSION 2.8.3)
project(octomap_builder)

find_package(catkin REQUIRED COMPONENTS
  pcl_ros
  roscpp
)

find_package(PCL REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES octomap_builder
  CATKIN_DEPENDS pcl_ros roscpp
  DEPENDS PCL
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/OctomapBuilder.cpp
)

add_executable(octomap_builder_test_fetch src/test/octomap_builder_test.cpp src/OctomapBuilder.cpp)

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
target_link_libraries(octomap_builder_test_fetch ${catkin_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
