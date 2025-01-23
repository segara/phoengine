cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME cmake_phoengine_example)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Hello, OpenGL!")
set(WINDOW_WIDTH 640)
set(WINDOW_HEIGHT 480)

IF (WIN32)
set(API_OPTION "" CACHE STRING "Choose API in Windows")
set_property(CACHE API_OPTION PROPERTY STRINGS "OpenGL" "DirectX11")
ENDIF()


project(${PROJECT_NAME})

set(ALL_HEADERS "")

IF (WIN32)
    if(API_OPTION STREQUAL "OpenGL")
        file(GLOB SOURCES "src/Opengl_win/source/Window/*.cpp" "src/Opengl_win/source/Graphic/*.cpp" "src/Opengl_win/source/Core/*.cpp" "src/main.cpp")
    elseif(API_OPTION STREQUAL "DirectX11")
        file(GLOB_RECURSE SOURCES "src/DirectX11_win/source/*.cpp" "src/main.cpp")
    endif()

    if(API_OPTION STREQUAL "OpenGL")
        file(GLOB_RECURSE ALL_HEADERS "src/Opengl_win/include/*")
    elseif(API_OPTION STREQUAL "DirectX11")
        file(GLOB_RECURSE ALL_HEADERS "src/DirectX11_win/include/*")
    endif()

ELSEIF(APPLE)
file(GLOB SOURCES "src/Metal_osx/source/Window/*.mm" "src/Metal_osx/source/Graphic/*.mm" "src/Metal_osx/source/Core/*.mm" "src/main.mm")
ENDIF()



# add_executable 프로젝트 타겟으로 지정 : visual studio 의 project
add_executable(${PROJECT_NAME} ${SOURCES} ${ALL_HEADERS})

IF (WIN32)
    # 중복 제거를 위한 set
    set(HEADER_DIRS "")

    # 디렉토리 경로 추출
    foreach(header ${ALL_HEADERS})
        get_filename_component(dir ${header} DIRECTORY)
        list(APPEND HEADER_DIRS ${dir})
    endforeach()

    # 중복 제거
    list(REMOVE_DUPLICATES HEADER_DIRS)
    target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER_DIRS})
ELSEIF(APPLE)
target_include_directories(${PROJECT_NAME} PUBLIC "src" "src/Metal_osx/include" "src/Metal_osx/include" "src/Metal_osx/include/Window" "src/Metal_osx/include/Graphic" "src/Metal_osx/include/Core")
find_library(FOUNDATION_FRAMEWORK Foundation)
find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
find_library(QUARTZCORE_FRAMEWORK QuartzCore)
find_library(APPKIT_FRAMEWORK AppKit)
find_library(METAL_FRAMEWORK Metal)
find_library(METALKIT_FRAMEWORK MetalKit)
SET(XCODE_FRAMEWORK ${FOUNDATION_FRAMEWORK} ${CORE_FOUNDATION_FRAMEWORK} ${APPKIT_FRAMEWORK} ${METAL_FRAMEWORK} ${METALKIT_FRAMEWORK} ${QUARTZCORE_FRAMEWORK})
ENDIF()

#dependency 기능 사용
include(Dependency.cmake)

# 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
IF (WIN32)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})
# Dependency들이 먼저 build 될 수 있게 관계 설정
    if(DEP_LIST)
        add_dependencies(${PROJECT_NAME} ${DEP_LIST})
    endif()
ELSEIF(APPLE)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS} ${XCODE_FRAMEWORK})
ENDIF()

# 라이브러리 서브 디렉토리 추가
add_subdirectory(demo)
# TestLibrary에서 메인 프로젝트 헤더를 사용할 수 있도록 include 경로 추가
target_include_directories(TriangleTest PUBLIC ${HEADER_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE TriangleTest)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
    )

