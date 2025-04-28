cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME phoengine)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Hello, OpenGL!")
set(WINDOW_WIDTH 640)
set(WINDOW_HEIGHT 480)

project(${PROJECT_NAME})

# 소스 및 헤더 파일 명시적 추가
set(ENGINE_SOURCES
    src/Opengl3d_win/source/Window/Window.cpp
    # 추가 엔진 소스 파일들...
)

set(ENGINE_HEADERS
    src/Opengl3d_win/include/Window/Window.h
    # 추가 엔진 헤더 파일들...
)

set(APP_SOURCES
    src/Game.cpp
    src/main.cpp
    # 추가 애플리케이션 소스 파일들...
)

set(APP_HEADERS
    src/Game.h
    # 추가 애플리케이션 헤더 파일들...
)
# 디렉토리 구조에 따라 소스 그룹 설정
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
    ${ENGINE_SOURCES} 
    ${ENGINE_HEADERS}
    ${APP_SOURCES}
    ${APP_HEADERS}
)

#add_executable 프로젝트 타겟으로 지정
add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${APP_SOURCES} ${ENGINE_HEADERS} ${APP_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC  
${CMAKE_CURRENT_SOURCE_DIR}/src 
${CMAKE_CURRENT_SOURCE_DIR}/src/Opengl3d_win/source 
${CMAKE_CURRENT_SOURCE_DIR}/src/Opengl3d_win/include)

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

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})