# TestLibrary/CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(TriangleTest)

# 라이브러리 소스 파일
add_library(TriangleTest STATIC Triangle.cpp)

# 헤더 파일 디렉토리 포함
target_include_directories(TriangleTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 타겟 아키텍처 설정
