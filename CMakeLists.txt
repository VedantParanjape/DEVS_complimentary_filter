# cmake minimum version
cmake_minimum_required(VERSION 3.4)

# Make sure that it is not built in root directory, build inside /build folder
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

# CMake project description and project specific settings
project(DEVS-complimentary-filter
        VERSION ${CMAKE_PROJECT_VERSION}
        DESCRIPTION "DEVS Model for complimentary filter"
        HOMEPAGE_URL "https://github.com/VedantParanjape/DEVS_complimentary_filter")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Check for required packages

# Specify Build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

######## SOURCES ########
# Add source files and header files
file(GLOB PROJECT_HEADERS include/*.hpp deps/cadmium/include/)
file(GLOB PROJECT_SOURCES src/*.cpp)
set(PROJECT_FILES
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES})

######## TARGETS ########
# Add executables
add_executable(${PROJECT_NAME} ${PROJECT_FILES})
target_compile_definitions(${PROJECT_NAME}-${CMAKE_PROJECT_VERSION} PRIVATE INSTALL_PATH=${CMAKE_INSTALL_PREFIX} VERSION_NUMBER=${CMAKE_PROJECT_VERSION})
target_include_directories(${PROJECT_NAME}-${CMAKE_PROJECT_VERSION} PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

# include_directories( ${Boost_INCLUDE_DIR} )
# link_directories( ${Boost_LIBRARY_DIRS} )
# set( Boost_USE_STATIC_LIBS        OFF )
# set( Boost_USE_MULTITHREADED      ON )
# set( Boost_USE_STATIC_RUNTIME     OFF )
# set( BOOST_ALL_DYN_LINK           ON )

# add_executable( ${PROJECT_NAME} main.cpp )
# target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} )