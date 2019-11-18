cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_MAIN "Build main" ON)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
        SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)

project(FTPFilesAnalyzer)

hunter_add_package(Boost COMPONENTS filesystem)
find_package(Boost CONFIG REQUIRED filesystem)
find_package(Threads)

if (BUILD_MAIN)
    set(ADDSOURCES ${PROJECT_NAME}Sources)
    set(MAIN_NAME ${PROJECT_NAME}Main)

    add_library(
            ${ADDSOURCES}
            STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/sources/FTPFilesAnalyzer.cpp
    )
    target_include_directories(
            ${ADDSOURCES}
            PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(
            ${ADDSOURCES}
            Boost::filesystem
    )

    add_executable(${CMAKE_PROJECT_NAME}Main ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)
    target_include_directories(${MAIN_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${MAIN_NAME} ${ADDSOURCES})
endif()