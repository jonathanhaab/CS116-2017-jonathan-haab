project(Neuron_Test)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-W  -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(neuron_unittest
	neuron.cpp
	neuron_unittest.cpp
)

add_executable(Neurons
	neuronMain.cpp
	neuron.cpp
	neuron.hpp
)

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest neuron_unittest)
