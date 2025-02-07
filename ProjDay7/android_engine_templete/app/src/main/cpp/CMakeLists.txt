#
# Copyright (C) The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_VERBOSE_MAKEFILE ON)
if(ANDROID)

# build native_app_glue as a static lib
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
# 심볼을 링크에 꼭 포함시키도록 함.android_native_app_glue.h 에 있음
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

#!!!!!!!!!!!!ENGINE DIR SETTING!!!!!!!!!!!!!!!!!!!!!!
#현재 프로젝트 경로를 얻어와서 수정해야 한다. 왜냐하면 현재 cmakelists의 자식경로가 아니기 때문이다.
set(ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Original Path: ${ENGINE_DIR}")
#android_engine_templete폴더위치가 변경되지 않는다는 가정하에 android_engine_templete/app/src/main/cpp 문자열 지움
string(REPLACE "/android_engine_templete/app/src/main/cpp" "" ENGINE_DIR "${ENGINE_DIR}/engine")
message(STATUS "Modified Path: ${ENGINE_DIR}")

#!!!!!!!!!!!!여기에서 android쪽 cmakelists 로드!!!!!!!!!!!!!!!!!!!!!!
include(${ENGINE_DIR}/src/gles_android/CMakeLists.txt)

add_library(native-activity SHARED main.cpp)

#target_include_directories : Add header include
target_include_directories(native-activity PRIVATE
    ${ENGINE_HEADER_DIR_LIST})
target_include_directories(native-activity PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)

# add lib dependencies
target_link_libraries(native-activity
native_app_glue
engine-lib
)

endif()