cmake_minimum_required(VERSION 2.8)
project(Read_Binary)

find_package(Boost REQUIRED
  COMPONENTS
  filesystem
  system
)
find_package(OpenCV REQUIRED)

########### The main executable ###########
add_executable(${PROJECT_NAME} read.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${OpenCV_LIBS})