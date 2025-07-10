####
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2025 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
####

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

project(MiracastPlayerHal VERSION 1.0.0 LANGUAGES CXX)

# set LIBNAME matching to project name
set(LIBNAME ${PROJECT_NAME})
set(SRCS SoC_MiracastPlayer.cpp halLogger.cpp)
set(DEFAULT_BUILD_TYPE "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Add GIT version to the compile flags
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_SHA
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (NOT GIT_SHA STREQUAL "")
    message(STATUS "GIT_SHA is set to ${GIT_SHA}")
    set(GIT_SHA_DEF "GIT_SHA=\"${GIT_SHA}\"")
else()
    message(STATUS "GIT_SHA is not set")
    set(GIT_SHA_DEF "GIT_SHA=\"unknown\"")
endif()

include(GNUInstallDirs)

add_library(${LIBNAME} SHARED ${SRCS})

target_compile_definitions(${LIBNAME} PRIVATE ${GIT_SHA_DEF})

# Set C++ standard
set_target_properties(${LIBNAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
)

# Add GStreamer include directories and link libraries
if(GSTREAMER_FOUND)
    target_include_directories(${LIBNAME} PRIVATE ${GSTREAMER_INCLUDE_DIRS})
    target_link_libraries(${LIBNAME} PRIVATE ${GSTREAMER_LIBRARIES})
endif()

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/clean.cmake
)

# Install the library
install(TARGETS ${LIBNAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install public header for development package; exclude the private halLogger.h
install(FILES SoC_MiracastPlayer.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Define package configuration variables
set(PACKAGE_NAME ${LIBNAME})
set(PACKAGE_VERSION ${PROJECT_VERSION})
set(PACKAGE_DESCRIPTION "RPI-4 RDKV Miracast HAL Library")
set(PACKAGE_LIBS "-L${CMAKE_INSTALL_PREFIX}/lib -l${LIBNAME}")
set(PACKAGE_CFLAGS "-I${CMAKE_INSTALL_PREFIX}/include")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${PACKAGE_NAME}.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}.pc
    @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
