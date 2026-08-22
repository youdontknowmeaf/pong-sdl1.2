cmake_minimum_required(VERSION 3.13)
set(CMAKE_TOOLCHAIN_FILE "$ENV{DEVKITPRO}/wut/share/wut.toolchain.cmake")
project(pong_u C CXX)
include("/opt/devkitpro/cmake/WiiU.cmake" REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT DEFINED ENV{DEVKITPRO})
    set(ENV{DEVKITPRO} "/opt/devkitpro")
    message(FATAL_ERROR "DEVKITPRO environment variable not set")
endif()
set(DEVKITPRO $ENV{DEVKITPRO})
#include(${DEVKITPRO}/wut/share/wut.cmake OPTIONAL)
set(SDL2_DIR     ${DEVKITPRO}/portlibs/wiiu)
set(SDL2_INC     ${SDL2_DIR}/include/SDL2)
set(SDL2_LIB     ${SDL2_DIR}/lib)
set(PORTLIBS_PPC ${DEVKITPRO}/portlibs/ppc)
file(GLOB_RECURSE SOURCES
    source/*.cpp
    source/*.c
)
add_executable(pong_u ${SOURCES})
target_include_directories(pong_u PRIVATE
    source
    ${SDL2_DIR}/include
    ${SDL2_INC}
    ${DEVKITPRO}/wut/include
    ${PORTLIBS_PPC}/include
)
target_link_directories(pong_u PRIVATE
    ${SDL2_LIB}
    ${PORTLIBS_PPC}/lib
    ${DEVKITPRO}/wut/lib
    ${DEVKITPRO}/portlibs/wiiu/lib
)
target_link_libraries(pong_u PRIVATE
    #SDL2_mixer
    #vorbisfile
    #vorbis
    #ogg
    #mpg123
    #modplug
    SDL2
    #SDL2_ttf
    #SDL2_image
    #freetype
    #png
    z
    m
    #harfbuzz
    #brotlidec
    #brotlicommon
    #bz2
    #curl
    #pthread
    #mbedtls
    #mbedx509
    #mbedcrypto
    #webp
    wut
)
wut_create_rpx(pong_u)
wut_create_wuhb(pong_u
    NAME "Pong U (WiiU Pong)"
    AUTHOR "SpookScoop93"
    ICON  ${CMAKE_SOURCE_DIR}/meta/icon.png
)

if(BUILD_MODE STREQUAL "hw")
    target_compile_definitions(pong_u PRIVATE BUILD_HW=1)
else()
    target_compile_definitions(pong_u PRIVATE BUILD_HW=0)
endif()

if(NOT DEFINED APP_VERSION)
    set(APP_VERSION "dev")
endif()
target_compile_definitions(pong_u PRIVATE APP_VERSION="${APP_VERSION}")
