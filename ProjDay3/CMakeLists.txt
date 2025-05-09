cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME cmake_opengl_example)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Hello")


project(${PROJECT_NAME})
IF (WIN32)
    # 소스 및 헤더 파일 명시적 추가
    set(ENGINE_SOURCES
        src/Opengl_win/source/Window/Window.cpp
        src/Opengl_win/source/Graphic/GraphicEngine.cpp
        # 추가 엔진 소스 파일들...
    )
    set(ENGINE_HEADERS
        src/Opengl_win/include/Window/Window.h
        src/Opengl_win/include/Graphic/GraphicEngine.h
        src/Math/Vec4.h
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
ELSEIF(APPLE)
    set(ENGINE_SOURCES
        src/Metal_osx/source/Window/Window.mm
        src/Metal_osx/source/Graphic/GraphicEngine.mm
        # 추가 엔진 소스 파일들...
    )
    set(ENGINE_HEADERS
        src/Metal_osx/include/Window/Window.h
        src/Metal_osx/include/Graphic/GraphicEngine.h
        src/Math/Vec4.h
        # 추가 엔진 헤더 파일들...
    )
    set(APP_SOURCES
        src/Game.mm
        src/main.mm
        # 추가 애플리케이션 소스 파일들...
    )
    set(APP_HEADERS
        src/Game.h
        # 추가 애플리케이션 헤더 파일들...
    )
ENDIF()

# 디렉토리 구조에 따라 소스 그룹 설정
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
    ${ENGINE_SOURCES} 
    ${ENGINE_HEADERS}
    ${APP_SOURCES}
    ${APP_HEADERS}
)

# add_executable 프로젝트 타겟으로 지정 : visual studio 의 project
add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${APP_SOURCES} ${ENGINE_HEADERS} ${APP_HEADERS})

IF (WIN32)
target_include_directories(${PROJECT_NAME} PUBLIC  
${CMAKE_CURRENT_SOURCE_DIR}/src 
${CMAKE_CURRENT_SOURCE_DIR}/src/Opengl_win/source 
${CMAKE_CURRENT_SOURCE_DIR}/src/Opengl_win/include)
ELSEIF(APPLE)
target_include_directories(${PROJECT_NAME} PUBLIC  
${CMAKE_CURRENT_SOURCE_DIR}/src 
${CMAKE_CURRENT_SOURCE_DIR}/src/Metal_osx/source 
${CMAKE_CURRENT_SOURCE_DIR}/src/Metal_osx/include)
find_library(FOUNDATION_FRAMEWORK Foundation)
find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
find_library(APPKIT_FRAMEWORK AppKit)
find_library(QUARTZCORE_FRAMEWORK QuartzCore)
find_library(METAL_FRAMEWORK Metal)
find_library(METALKIT_FRAMEWORK MetalKit)
SET(XCODE_FRAMEWORK ${FOUNDATION_FRAMEWORK} ${CORE_FOUNDATION_FRAMEWORK} ${APPKIT_FRAMEWORK} ${METAL_FRAMEWORK} ${METALKIT_FRAMEWORK} ${QUARTZCORE_FRAMEWORK})
ENDIF()


#dependency 기능 사용
include(Dependency.cmake)

# 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})

IF (WIN32)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
# add_dependencies(${PROJECT_NAME} ${DEP_LIST}) # Dependency들이 먼저 build 될 수 있게 관계 설정
ELSEIF(APPLE)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS} ${XCODE_FRAMEWORK})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
ENDIF()


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

