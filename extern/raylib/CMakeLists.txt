# extern/raylib/CMakeLists.txt

set(RAYLIB_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(RAYLIB_LIB_FILE ${CMAKE_CURRENT_LIST_DIR}/lib/libraylib.a)

add_library(raylib IMPORTED STATIC GLOBAL
        ../../src/Component.cpp
        ../../src/Core/Component.h)

set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION "${RAYLIB_LIB_FILE}"
        INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_INCLUDE_DIR}"
)

include_directories(RAYLIB_INCLUDE_DIR)