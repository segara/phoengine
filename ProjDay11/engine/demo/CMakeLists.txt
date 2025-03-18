# TestLibrary/CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(TriangleTest)

# 라이브러리 소스 파일
file(GLOB_RECURSE SOURCE_FILES Triangle.cpp)
if(APPLE OR CMAKE_SYSTEM_NAME STREQUAL "iOS")
set_source_files_properties(${SOURCE_FILES} PROPERTIES
        COMPILE_FLAGS "-x objective-c++")
endif()
add_library(TriangleTest STATIC Triangle.cpp)

# 헤더 파일 디렉토리 포함
target_include_directories(TriangleTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_property (TARGET TriangleTest APPEND_STRING PROPERTY
        COMPILE_FLAGS "-fobjc-arc")
        
# shader.metal 파일을 빌드 디렉토리로 복사
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.metal
    ${CMAKE_CURRENT_BINARY_DIR}/shader.metal
    COPYONLY
)