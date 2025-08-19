cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(NuMain)

find_package(Geant4 REQUIRED ui_all vis_all)

# Locate sources and headers for this project
file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh" "/home/jimmyma/Software/crmc/crmc-geant4-build/src/*.hh")

add_executable(NuMain NuMain.cc ${sources} ${headers})
target_include_directories(NuMain PRIVATE include "/home/jimmyma/Software/crmc/crmc-v2.2.1/src/geant4/")
target_link_libraries(NuMain PRIVATE ${Geant4_LIBRARIES})

# crmc shared libraries
target_link_libraries(NuMain PRIVATE "/home/jimmyma/Software/crmc/crmc-geant4-build/lib/libCrmc.so"
    "/home/jimmyma/Software/crmc/crmc-geant4-build/lib/libCrmcBasic.so"
    "/home/jimmyma/Software/crmc/crmc-geant4-build/lib/libEpos.so"
    "/home/jimmyma/Software/crmc/crmc-geant4-build/lib/libGeantCrmc.so"
    "/home/jimmyma/Software/crmc/crmc-geant4-build/lib/libSibyll.so")
