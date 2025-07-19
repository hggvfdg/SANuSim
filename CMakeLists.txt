cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(NuMain)

find_package(Geant4 REQUIRED ui_all vis_all)

# Locate sources and headers for this project
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)

# Add executable
add_executable(NuMain NuMain.cc ${sources} ${headers})
target_include_directories(NuMain PRIVATE include)
target_link_libraries(NuMain ${Geant4_LIBRARIES})
