cmake_minimum_required(VERSION 3.16)

project(NetworkMonitoringSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)

include_directories(include)

add_executable(network_scanner
    src/main.cpp
    src/json_parser.cpp
    src/port_scanner.cpp
)

target_link_libraries(network_scanner
    PRIVATE
    nlohmann_json::nlohmann_json
)

find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE)

    file(GLOB_RECURSE PROJECT_SOURCES
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/*.h"
    )

    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE}
            -i
            -style=file
            ${PROJECT_SOURCES}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Formatting project..."
    )

endif()