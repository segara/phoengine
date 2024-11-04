# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/git_project/OpenglProj/build/dep-spdlog-prefix/src/dep-spdlog"
  "C:/git_project/OpenglProj/build/dep-spdlog-prefix/src/dep-spdlog-build"
  "C:/git_project/OpenglProj/build/dep-spdlog-prefix"
  "C:/git_project/OpenglProj/build/dep-spdlog-prefix/tmp"
  "C:/git_project/OpenglProj/build/dep-spdlog-prefix/src/dep-spdlog-stamp"
  "C:/git_project/OpenglProj/build/dep-spdlog-prefix/src"
  "C:/git_project/OpenglProj/build/dep-spdlog-prefix/src/dep-spdlog-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/git_project/OpenglProj/build/dep-spdlog-prefix/src/dep-spdlog-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/git_project/OpenglProj/build/dep-spdlog-prefix/src/dep-spdlog-stamp${cfgdir}") # cfgdir has leading slash
endif()
