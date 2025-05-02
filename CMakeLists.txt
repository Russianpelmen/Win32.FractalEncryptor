cmake_minimum_required(VERSION 3.8)
project("FractalEncryptor")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /O2 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /Od /DDEBUG /Zi")
else()
  set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG -g0")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")
endif()

set(SOURCE
    "src/Common.hpp"
    "src/CryptLogic.cpp"
    "src/InitWindow.cpp"
    "src/main.cpp"
    "src/CryptLib/Cryptor.cpp"
    "src/CryptLib/Cryptor.hpp"
)

set(RESOURCE
    Resource/resource.rc
    Resource/resource.h
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE} ${RESOURCE})

if (WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE YES)
endif()

set(UPX_EXECUTABLE "${CMAKE_SOURCE_DIR}/upx.exe")

if(EXISTS ${UPX_EXECUTABLE} AND CMAKE_BUILD_TYPE STREQUAL "Release")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${UPX_EXECUTABLE} --best --lzma $<TARGET_FILE:${PROJECT_NAME}>
  )
endif()
