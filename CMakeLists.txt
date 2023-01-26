cmake_minimum_required(VERSION 3.0.0)
project(boids VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_options(
  /std:c++17
)

add_library(raylib::raylib SHARED IMPORTED)
set_target_properties(
  raylib::raylib
  PROPERTIES
  IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/lib/raylib.lib"
  IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/raylib.dll"
  IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/lib/raylibdll.lib"
  IMPORTED_NO_SONAME "TRUE"
  INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/lib"
)

add_executable(boids
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

target_link_libraries(boids PRIVATE raylib::raylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
