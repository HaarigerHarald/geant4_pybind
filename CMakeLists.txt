cmake_minimum_required(VERSION 3.16...3.22)
project(geant4_pybind)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W3" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long")
endif()

find_package(Geant4 11.0 REQUIRED)
find_package(Geant4 OPTIONAL_COMPONENTS gdml ui_tcsh motif vis_raytracer_x11 vis_opengl_x11 vis_opengl_win32 qt)

set(PYBIND11_PYTHON_VERSION 3.5)
add_subdirectory(pybind11)

add_subdirectory(source)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
