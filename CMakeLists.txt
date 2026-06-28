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
