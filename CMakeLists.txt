cmake_minimum_required(VERSION 3.21)
project(marshmallow CXX C ASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

add_compile_options(--target=aarch64-none-elf)
add_compile_options(-mcpu=cortex-a57+fp+simd+crypto+crc)
add_compile_options(-mno-implicit-float)
add_compile_options(-stdlib=libc++)
add_compile_options(-fPIC)
add_compile_options(-fstandalone-debug)
add_compile_options(-v -Wall -O3 -nodefaultlibs -nostdlib -ffunction-sections -fdata-sections)
add_compile_options(-Werror=return-type)
add_compile_options(-fno-rtti -fno-asynchronous-unwind-tables -fno-unwind-tables)
add_compile_definitions(ARDUINOJSON_ENABLE_COMMENTS SWITCH)
add_link_options(-shared -ffunction-sections -fdata-sections)
add_link_options(-stdlib=libc++ -nodefaultlibs -nostdlib)

include(cmake/Helpers.cmake)
include(cmake/genClangd.cmake)

# Change this depending on the SDK version you are targeting
set(NN_SDK_MAJOR 3)
set(NN_SDK_MINOR 5)
set(NN_SDK_PATCH 1)
set(NN_SDK_TYPE "Release")

add_subdirectory(libs/exlaunch)
add_subdirectory(libs/ArduinoJson)
add_subdirectory(libs/marshmallow)

target_compile_definitions(marshmallow PUBLIC NNSDK=1)

include_directories(${PROJECT_SOURCE_DIR}/libs/custom/)
include_directories(${PROJECT_SOURCE_DIR}/libs/custom/al)
include_directories(${PROJECT_SOURCE_DIR}/libs/custom/game)
include_directories(${PROJECT_SOURCE_DIR}/libs/custom/sead)
include_directories(${PROJECT_SOURCE_DIR}/libs/smo/al)
include_directories(${PROJECT_SOURCE_DIR}/libs/smo/agl)
include_directories(${PROJECT_SOURCE_DIR}/libs/smo/game)
include_directories(${PROJECT_SOURCE_DIR}/libs/smo/NintendoSDK)
include_directories(${PROJECT_SOURCE_DIR}/libs/smo/sead)

add_executable(subsdk9)
add_subdirectory(user)

target_link_libraries(subsdk9 PUBLIC marshmallow
        -T ${CMAKE_SOURCE_DIR}/cmake/linker.ld
        -Wl,--whole-archive
        -Wl,--export-dynamic
        -Wl,--hash-style=sysv
        -Wl,--build-id=uuid
        -Wl,-init,rtldInit
)
generate_npdm(subsdk9 ${CMAKE_SOURCE_DIR}/user/subsdk9.json)
make_nso_target(subsdk9)
set(FTP_TITLE_ID 0100000000010000 CACHE STRING "FTP Title ID")
deploy_nso_ftp(subsdk9 ${FTP_TITLE_ID})

set(INCLUDE_DIRS
 ${CMAKE_SOURCE_DIR}/tools/clang/bin/../lib/clang-runtimes/aarch64-none-elf/aarch64/include/c++/v1
 ${CMAKE_SOURCE_DIR}/tools/clang/lib/clang/17/include
 ${CMAKE_SOURCE_DIR}/tools/clang/bin/../lib/clang-runtimes/aarch64-none-elf/aarch64/include
)

generate_clangd_file("${CMAKE_SOURCE_DIR}/.clangd" "${INCLUDE_DIRS}")
