cmake_minimum_required(VERSION 3.16)
project(EverythingIsFine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# --- C++ standard ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Fetch SFML (requires git) ---
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b   # SFML 2.6.1 commit
)
FetchContent_MakeAvailable(SFML)

# --- Paths ---
set(SRC_DIR     "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR     "${PROJECT_SOURCE_DIR}/include")
set(ASSETS_DIR  "${PROJECT_SOURCE_DIR}/assets")

# --- Collect sources/headers across subfolders ---
# This updates automatically when you add/remove files (requires CMake 3.12+).
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${SRC_DIR}/*.cpp"
)

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
    "${INC_DIR}/*.h"
    "${INC_DIR}/*.hpp"
)

add_executable(EverythingIsFine
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# If you use include/HorrorHallway/... style includes:
#   #include <HorrorHallway/ui/Menu.h>
target_include_directories(EverythingIsFine PRIVATE "${INC_DIR}")

target_link_libraries(EverythingIsFine PRIVATE
    sfml-graphics sfml-window sfml-system sfml-network sfml-audio
)

# --- Copy assets next to the executable after build ---
add_custom_command(TARGET EverythingIsFine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${ASSETS_DIR}"
            "$<TARGET_FILE_DIR:EverythingIsFine>/assets"
    COMMENT "Copying assets to output directory"
)

# --- Windows: copy OpenAL runtime next to exe (SFML audio dependency) ---
if(WIN32)
    add_custom_command(TARGET EverythingIsFine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll"
            "$<TARGET_FILE_DIR:EverythingIsFine>"
        COMMENT "Copying openal32.dll to output directory"
    )
endif()