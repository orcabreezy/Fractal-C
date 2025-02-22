cmake_minimum_required(VERSION 3.15)

project(
  EnvironmentTest
  DESCRIPTION "Image File library"
  LANGUAGES CXX
)


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
src/PureImage.cpp
src/BmpImage.cpp
src/Pixel.cpp

src/fractal/FractalImage.cpp
src/fractal/Mandelbrot.cpp
src/fractal/Julia.cpp
src/fractal/fractalUtils.cpp
src/fractal/ModularMandelbrot.cpp

src/gradient/SimpleGradient.cpp
src/gradient/LookupGradient.cpp
src/gradient/FunctionalGradient.cpp
)

target_link_libraries(src PRIVATE project_options project_warnings)


## Main
add_executable(
  imlib main.cpp
)
target_link_libraries(imlib PRIVATE src)
target_link_libraries(imlib PRIVATE project_options project_warnings)

## GTest
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include)

# define the executable
add_executable(
  test01 tests/test.cpp
)

target_link_libraries(
  test01
  PRIVATE src
  PRIVATE GTest::gtest_main
  PRIVATE project_options
  PRIVATE project_warnings
)
include(GoogleTest)
gtest_discover_tests(test01)
