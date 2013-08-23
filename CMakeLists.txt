#要求CMake程序版本不小于2.8 
cmake_minimum_required(VERSION 2.8)   
#设置项目名称 
PROJECT( SparseFakeFingerVerify ) 
#要求必须能够找到OpenCV库的路径 
FIND_PACKAGE( OpenCV REQUIRED )
find_package(Eigen3 REQUIRED)
#添加boost库
set(EIGEN3_INCLUDE_DIR "D:/Program Files/eigen")
set(BOOST_DIR "D:/Program Files/boost_1_54_0") 
set(BOOST_INCLUDEDIR "D:/Program Files/boost_1_54_0") 
set(BOOST_LIBRARYDIR "D:/Program Files/boost_1_54_0/stage/lib") 
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.54.0 COMPONENTS thread timer date_time system chrono regex)
#将源码加入项目中 
ADD_EXECUTABLE( SparseFakeFingerVerify main.cpp build/FeatureExtract.h build/FeatureExtract.cpp )
include_directories(EIGEN3_INCLUDE_DIR)
#将OpenCV库作为项目的链接库 
TARGET_LINK_LIBRARIES( SparseFakeFingerVerify ${OpenCV_LIBS} ) 
#将boost库加入项目的链接库
if(Boost_FOUND)
   message(${Boost_LIBRARIES})
   INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#   LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
   target_link_libraries( SparseFakeFingerVerify ${Boost_LIBRARIES})
endif()