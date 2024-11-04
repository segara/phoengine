cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME cmake_opengl_example)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Hello, OpenGL!")
set(WINDOW_WIDTH 640)
set(WINDOW_HEIGHT 480)

project(${PROJECT_NAME})

# 소스 파일 자동 포함
file(GLOB_RECURSE SOURCES "src/*.cpp")

#add_executable 프로젝트 타겟으로 지정
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "src/Opengl3d_win/include")

#dependency 기능 사용
include(Dependency.cmake)

# 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
    )

# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST})