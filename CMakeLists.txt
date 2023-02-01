cmake_minimum_required(VERSION 3.8)

add_library(mast)
add_library(mast::mast ALIAS mast)
target_compile_features(mast PUBLIC cxx_std_20)

# ---Add source files---
target_include_directories(mast PUBLIC include)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
target_sources(mast PRIVATE ${SRC_FILES})

# ---Set warning level---
if(MSVC)
    target_compile_options(mast PRIVATE /W4)
else()
    target_compile_options(mast PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# ---Maybe enable warnings as errors---
set(WARNINGS_AS_ERRORS_FOR_MAST OFF CACHE BOOL "ON iff you want to treat warnings as errors")
if(WARNINGS_AS_ERRORS_FOR_MAST)
    if(MSVC)
        target_compile_options(mast PRIVATE /WX)
    else()
        target_compile_options(mast PRIVATE -Werror)
    endif()
endif()
