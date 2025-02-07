################################################################################
# If not stated otherwise in this file or this component's Licenses.txt file the
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
################################################################################
cmake_minimum_required(VERSION 3.3)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GSTREAMERBASE REQUIRED gstreamer-app-1.0)


# Build system miracast player platform library
set(Platform_SOURCES src/SoC_MiracastPlayer.cpp)
add_library(MiracastPlayerHal SHARED ${Platform_SOURCES})

target_include_directories(MiracastPlayerHal PRIVATE ${GSTREAMER_INCLUDES})
target_include_directories(MiracastPlayerHal PRIVATE ${GSTREAMERBASE_INCLUDE_DIRS})

target_link_libraries(MiracastPlayerHal PRIVATE ${GSTREAMER_LIBRARIES})
target_link_libraries(MiracastPlayerHal PRIVATE ${GSTREAMERBASE_LIBRARIES})

install(TARGETS MiracastPlayerHal LIBRARY DESTINATION lib)
install(FILES src/SoC_MiracastPlayer.h DESTINATION include)
