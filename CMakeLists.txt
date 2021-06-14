
cmake_minimum_required(VERSION 3.4)

project(DEVS-complimentary-filter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(DIVISIBLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(DIVISIBLE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

set(DIVISION_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/division)

include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})
include_directories(${DIVISION_HEADERS_DIR})

FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.0
)

# find_package( Boost REQUIRED )
# include_directories( ${Boost_INCLUDE_DIR} )
# link_directories( ${Boost_LIBRARY_DIRS} )
# set( Boost_USE_STATIC_LIBS        OFF )
# set( Boost_USE_MULTITHREADED      ON )
# set( Boost_USE_STATIC_RUNTIME     OFF )
# set( BOOST_ALL_DYN_LINK           ON )

# add_executable( ${PROJECT_NAME} main.cpp )
# target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} )