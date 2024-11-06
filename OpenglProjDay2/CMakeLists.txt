cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME cmake_opengl_example)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Hello, OpenGL!")
set(WINDOW_WIDTH 640)
set(WINDOW_HEIGHT 480)

project(${PROJECT_NAME})

IF (WIN32)
file(GLOB SOURCES "src/Opengl3d_win/source/Window/*.cpp" "src/main.cpp" "src/Game.cpp")
ELSEIF(APPLE)
file(GLOB SOURCES "src/Opengl3d_osx/source/Window/*.mm" "src/main.mm" "src/Game.mm")
ENDIF()

# add_executable 프로젝트 타겟으로 지정 : visual studio 의 project
add_executable(${PROJECT_NAME} ${SOURCES})

IF (WIN32)
target_include_directories(${PROJECT_NAME} PUBLIC "src/Opengl3d_win/include")
ELSEIF(APPLE)
target_include_directories(${PROJECT_NAME} PUBLIC "src/Opengl3d_osx/include")
find_library(FOUNDATION_FRAMEWORK Foundation)
find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
find_library(APPKIT_FRAMEWORK AppKit)
SET(XCODE_FRAMEWORK ${FOUNDATION_FRAMEWORK} ${CORE_FOUNDATION_FRAMEWORK} ${APPKIT_FRAMEWORK})
ENDIF()
#dependency 기능 사용
include(Dependency.cmake)

# 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})

IF (WIN32)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})
# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST})
ELSEIF(APPLE)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS} ${XCODE_FRAMEWORK})
ENDIF()

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
    )

