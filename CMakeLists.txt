cmake_minimum_required(VERSION 3.20)
project(dosyaci CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include(FetchContent)
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG v5.0.0
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(ftxui)

file(GLOB_RECURSE DOSYACI_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(dosyaci ${DOSYACI_SOURCES})

target_include_directories(dosyaci PRIVATE include)

target_link_libraries(dosyaci
    PRIVATE
        ftxui::screen
        ftxui::dom
        ftxui::component
)
