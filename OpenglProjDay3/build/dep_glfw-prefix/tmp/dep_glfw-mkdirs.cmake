# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/git/phoengine/phoengine/OpenglProjDay3/build/dep_glfw-prefix/src/dep_glfw"
  "E:/git/phoengine/phoengine/OpenglProjDay3/build/dep_glfw-prefix/src/dep_glfw-build"
  "E:/git/phoengine/phoengine/OpenglProjDay3/build/dep_glfw-prefix"
  "E:/git/phoengine/phoengine/OpenglProjDay3/build/dep_glfw-prefix/tmp"
  "E:/git/phoengine/phoengine/OpenglProjDay3/build/dep_glfw-prefix/src/dep_glfw-stamp"
  "E:/git/phoengine/phoengine/OpenglProjDay3/build/dep_glfw-prefix/src"
  "E:/git/phoengine/phoengine/OpenglProjDay3/build/dep_glfw-prefix/src/dep_glfw-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/git/phoengine/phoengine/OpenglProjDay3/build/dep_glfw-prefix/src/dep_glfw-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/git/phoengine/phoengine/OpenglProjDay3/build/dep_glfw-prefix/src/dep_glfw-stamp${cfgdir}") # cfgdir has leading slash
endif()
