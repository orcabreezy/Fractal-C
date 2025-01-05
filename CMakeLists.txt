cmake_minimum_required(VERSION 3.15)

project(
  EnvironmentTest
  DESCRIPTION "This is the solution for exercise0.11"
  LANGUAGES CXX)

# We include some common default settings (release type...) and other cmake
# flags that can be set to optimize or speed up the build if the required tools
# can be found.
include(cmake/project_settings.cmake)
include_directories(include)
# We use the `project_options` library declarations to define some compile time
# options.
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# warning specifications are defined in the `project_warnings` library.
add_library(project_warnings INTERFACE)
include(cmake/compiler_warnings.cmake)
set_project_warnings(project_warnings)

# Define the library that is compiled from src
add_library(src SHARED src/benchmark.cpp
                       src/image.cpp
                       src/bmp.cpp)

target_link_libraries(src PRIVATE project_options project_warnings)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
  target_link_libraries(src PRIVATE OpenMP::OpenMP_CXX)
endif()

# define the executable
add_executable(exercise0 main.cpp)
# link the src library
target_link_libraries(exercise0 PRIVATE src)
target_link_libraries(exercise0 PRIVATE project_options project_warnings)