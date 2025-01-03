cmake_minimum_required(VERSION 3.13)

if(ANDROID)

set(PROJECT_NAME engine_android_lib)
# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Android 플랫폼 설정
#set(CMAKE_SYSTEM_NAME Android)
#set(CMAKE_ANDROID_ARCH_ABI arm64-v8a) # 타겟 ABI 설정 (armeabi-v7a, arm64-v8a 등 가능)
#set(CMAKE_ANDROID_NDK ${ANDROID_NDK}) # Android NDK 경로
#set(CMAKE_ANDROID_STL_TYPE c++_shared) # C++ 런타임 라이브러리 설정

file(GLOB SOURCES 
"${ENGINE_DIR}/src/gles_android/source/Window/*.cpp" 
"${ENGINE_DIR}/src/gles_android/source/Graphic/*.cpp" 
"${ENGINE_DIR}/src/gles_android/source/Core/*.cpp")


message("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
message(${SOURCES})
message("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
add_library(engine-lib SHARED ${SOURCES}
 )

# 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(engine-lib  PUBLIC 
 ${ANDROID_NDK}/sources/android/native_app_glue
"${ENGINE_DIR}/src/gles_android/include" 
"${ENGINE_DIR}/src/gles_android/include/Window" 
"${ENGINE_DIR}/src/gles_android/include/Graphic" 
"${ENGINE_DIR}/src/gles_android/include/Core"
)

target_link_libraries(engine-lib
    android
    EGL
    GLESv1_CM
    log
)

set(ENGINE_HEADER_DIR_LIST ${ENGINE_HEADER_DIR_LIST}
"${ENGINE_DIR}/src/gles_android/include" 
"${ENGINE_DIR}/src/gles_android/include/Window" 
"${ENGINE_DIR}/src/gles_android/include/Graphic" 
"${ENGINE_DIR}/src/gles_android/include/Core"
)

endif()



