cmake_minimum_required(VERSION 4.3)
project(TwoWordPermutterCpp)

set(CMAKE_CXX_STANDARD 26)

add_executable(TwoWordPermutterCpp
        src/main.cpp
        src/io.hpp
        src/text.hpp
        src/text.cpp
        src/io.hpp
        src/console.hpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
    target_compile_options(TwoWordPermutterCpp PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wshadow
            -Wformat=2
            -Wundef
            -Wcast-align
            -Wold-style-cast
            -Wnon-virtual-dtor
            -Woverloaded-virtual
            -Werror

            -Wduplicated-cond
            -Wduplicated-branches
            -Wlogical-op
            -Wuseless-cast

            -fsanitize=address,undefined
            -fno-sanitize-recover=undefined
            -fno-omit-frame-pointer
    )

    target_link_options(TwoWordPermutterCpp PRIVATE -fsanitize=address,undefined)
endif ()
