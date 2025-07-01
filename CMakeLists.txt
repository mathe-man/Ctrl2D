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
set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Core)
set(COMPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Components)


# Compile extern code-libraries
add_subdirectory(extern)


add_executable(Ctrl2D
        # Main - Entry point
        ${SRC_DIR}/main.cpp

        # Core classes
        ${CORE_DIR}/Component.h
        ${CORE_DIR}/GameObject.h    ${CORE_DIR}/GameObject.cpp


        # Transform
        ${COMPS_DIR}/Transform2D.h    ${COMPS_DIR}/Transform2D.cpp
        src/Components/EllipseOutline.cpp
        src/Components/EllipseOutline.h
        src/Components/EllipseFill.h
        src/Components/Components.h
        src/Components/RectangleOutline.cpp
        src/Components/RectangleOutline.h
        src/Core/Scene.cpp
        src/Core/Scene.h
        src/Core/Event.h
        src/Components/RectangleFill.h
        src/Components/EllipseFill.cpp
        src/Components/RectangleFill.cpp
)

# Link libraries
target_link_libraries(Ctrl2D PRIVATE raylib rlImGui)
# Resolve includes
include_directories(
        ${SRC_DIR}
        ${CORE_DIR}
        ${COMPS_DIR}
)



# Windows-specific system libs
if (WIN32)
    target_link_libraries(Ctrl2D PRIVATE opengl32 gdi32 winmm)
endif()



