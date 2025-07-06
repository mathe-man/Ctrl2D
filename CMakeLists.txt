#CMakeLists.txt
cmake_minimum_required(VERSION 3.31)
project(Ctrl2D)

# Set Cmake variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set output directory
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/Release")
else()
    set(OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/Other")
endif()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH})



# Set project directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CORE_DIR ${SRC_DIR}/Core)
set(APP_DIR ${SRC_DIR}/Application)
set(ECS_DIR ${SRC_DIR}/ECS)
set(COMPS_DIR ${ECS_DIR}/Components)


# Compile extern code-libraries
add_subdirectory(extern)


add_executable(Ctrl2D
        # Main - Entry point
        ${SRC_DIR}/main.cpp

        # Application classes
        ${APP_DIR}/Ctrl2DApp.h          ${APP_DIR}/Ctrl2DApp.cpp


        # Core classes
        ${CORE_DIR}/Scene.h             ${CORE_DIR}/Scene.cpp
        ${CORE_DIR}/Event.h

        # ECS main classes
        ${ECS_DIR}/GameObject.h         ${ECS_DIR}/GameObject.cpp
        ${ECS_DIR}/Component.h

        # ECS additional components
        ${COMPS_DIR}/Transform2D.h      ${COMPS_DIR}/Transform2D.cpp
        ${COMPS_DIR}/Rectangle.h        ${COMPS_DIR}/Rectangle.cpp
        ${COMPS_DIR}/Ellipse.h          ${COMPS_DIR}/Ellipse.cpp

        # Additional files
        ${SRC_DIR}/Utils.h              ${SRC_DIR}/Utils.cpp
)


# Link libraries
target_link_libraries(Ctrl2D PRIVATE raylib rlImGui)
# Resolve includes
include_directories(
        ${SRC_DIR}
        ${APP_DIR}      ${CORE_DIR}
        ${ECS_DIR}      ${COMPS_DIR}
)



# Windows-specific system libs
if (WIN32)
    target_link_libraries(Ctrl2D PRIVATE opengl32 gdi32 winmm)
endif()



