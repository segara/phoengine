# ExternalProject 관련 명령어 셋 추가
include(ExternalProject)
#glad 설치시 python 필요
find_package(Python COMPONENTS Interpreter REQUIRED)

message(STATUS "Python executable: ${Python_EXECUTABLE}")
message(STATUS "Python version: ${Python_VERSION}")

#jinja2 가 없다고 나오면 다음 명령 실행:pip install Jinja2

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/fetch_contents)
# Visual Studio 프로젝트 : Debug로 설정
IF (WIN32)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
ENDIF()
IF (WIN32)
if(API_OPTION STREQUAL "OpenGL")
    ##### GLAD START ######

    include(FetchContent)
 
    FetchContent_Declare(
        glad
        GIT_REPOSITORY	https://github.com/Dav1dde/glad.git
        GIT_TAG			v2.0.4
        GIT_SHALLOW		TRUE
        SOURCE_SUBDIR	cmake
    )
    FetchContent_MakeAvailable(glad)
    # Path to glad directory
    set(GLAD_SOURCES_DIR ${FETCHCONTENT_BASE_DIR}/glad-src)
    # Path to glad cmake files
    add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
    glad_add_library(glad STATIC
        API gl:core=3.3 wgl=1.0
        EXTENSIONS WGL_ARB_extensions_string
        WGL_ARB_pixel_format
        WGL_ARB_create_context
        WGL_ARB_create_context_profile
        WGL_EXT_extensions_string
        WGL_EXT_swap_control
        LANGUAGE c
        OPTIONS LOADER 
        )

    # # 상위 프로젝트에 헤더 파일 경로 추가
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/gladsources/glad/include)

    ##### GLAD END ######

    # HLSLcc 다운로드 및 설정
     # cmake gui 에서 HLSLCC_LIBRARY_SHARED 옵션 끌것 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    FetchContent_Declare(
        hlslcc
        GIT_REPOSITORY https://github.com/Unity-Technologies/HLSLcc
    )
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/fetch_contents/hlslcc-src/include)

    # HLSLcc 다운로드 및 준비
    FetchContent_MakeAvailable(hlslcc)


    set(DEP_LIST ${DEP_LIST} glad)
    set(DEP_LIBS ${DEP_LIBS} glad)
    set(DEP_LIBS ${DEP_LIBS} opengl32)
    set(DEP_LIBS ${DEP_LIBS} d3d11)       #hlsl shader compile용
    set(DEP_LIBS ${DEP_LIBS} d3dcompiler) #hlsl shader compile용
    set(DEP_LIST ${DEP_LIST} hlslcc)
    set(DEP_LIBS ${DEP_LIBS} hlslcc) 

    message(STATUS ${CMAKE_BUILD_TYPE})
    message(STATUS ${CMAKE_BINARY_DIR})
    message(STATUS ${DEP_INSTALL_DIR})
    message(STATUS ${CMAKE_INSTALL_PREFIX})
    message(STATUS ${PROJECT_SOURCE_DIR})


    # # glfw
    # ExternalProject_Add(
    #     dep_glfw
    #     GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    #     GIT_TAG "3.3.2"
    #     GIT_SHALLOW 1
    #     UPDATE_COMMAND ""
    #     PATCH_COMMAND ""
    #     CMAKE_ARGS
    #         -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
    #         -DGLFW_BUILD_EXAMPLES=OFF
    #         -DGLFW_BUILD_TESTS=OFF
    #         -DGLFW_BUILD_DOCS=OFF
    #     TEST_COMMAND ""
    #     )
    # set(DEP_LIST ${DEP_LIST} dep_glfw)
    # set(DEP_LIBS ${DEP_LIBS} glfw3)

elseif(API_OPTION STREQUAL "DirectX11")
# Link DirectX libraries
set(DEP_LIBS ${DEP_LIBS} d3d11 dxgi dxguid d3dcompiler)
endif()
ENDIF()

IF (APPLE)
# include(FetchContent)

# ##########brew install cmake First###########
# FetchContent_Declare(
#         ios_cmake
#         GIT_REPOSITORY	https://github.com/sheldonth/ios-cmake.git
# )
# FetchContent_MakeAvailable(ios_cmake)
ENDIF()