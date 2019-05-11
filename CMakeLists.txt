cmake_minimum_required(VERSION 2.8)
project( ImageProcessing )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(prog_2 src/prog_2.cpp )
target_link_libraries( prog_2 ${OpenCV_LIBS} )

add_executable(prog3 src/prog3.cpp )
target_link_libraries( prog3 ${OpenCV_LIBS} )
