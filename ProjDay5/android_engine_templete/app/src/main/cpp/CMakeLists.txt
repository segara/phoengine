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
set(ENGINE_DIR "D:/git/phoengine/OpenglProjDay5/engine")

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