# specify the min cmake required
cmake_minimum_required(VERSION 3.11.4)

# project name
project("<%= appname %>")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Compiler options: warning and C++ 11
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER MATCHES ".*clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11 -lstdc++")
endif()

find_package(Boost 1.53.0 REQUIRED system date_time chrono timer filesystem thread log log_setup locale regex)
find_package(Qt5 5.1 QUIET COMPONENTS Core Gui Widgets PrintSupport)

find_package(terralib 5.4 REQUIRED)

if(terralib_FOUND)
  message(STATUS "Found terralib: ${terralib_INCLUDE_DIRS}")
endif()

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")
file(GLOB UI_FILES "src/ui/*.ui")

QT5_WRAP_UI(PLUGIN_EXAMPLE_GEN_HDR_FILES ${UI_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${terralib_INCLUDE_DIRS})

add_library(<%= appname %> SHARED ${SOURCES} ${PLUGIN_EXAMPLE_GEN_HDR_FILES})

set_property(SOURCE ${PLUGIN_EXAMPLE_GEN_HDR_FILES} PROPERTY SKIP_AUTOMOC ON)

target_link_libraries(<%= appname %> terralib_mod_qt_apf)

qt5_use_modules(<%= appname %> Core Gui Widgets)

install(TARGETS <%= appname %>
        EXPORT ${CMAKE_PROJECT_NAME}-targets
        RUNTIME DESTINATION bin COMPONENT runtime
        LIBRARY DESTINATION lib COMPONENT runtime
        ARCHIVE DESTINATION lib COMPONENT runtime)
