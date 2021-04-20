cmake_minimum_required(VERSION 3.0.2)
project(ruckig_state_msgs)

find_package(catkin REQUIRED
  COMPONENTS
    message_generation
    std_msgs
)

add_message_files(
  DIRECTORY
    msg
  FILES
    DurationDiscretization.msg
    Interface.msg
    InternalState.msg
    Result.msg
    Synchronization.msg
)

generate_messages(
  DEPENDENCIES
    std_msgs
)

catkin_package(
  CATKIN_DEPENDS
    message_runtime
    std_msgs
  INCLUDE_DIRS
    include
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
