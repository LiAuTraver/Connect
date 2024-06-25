set(CMAKE_SYSTEM_NAME Windows)
cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(QRC_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)
set(QRC_PYTHON_SCRIPT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Helpers/generate_qrc.py)
set(PROJECT_NAME Connect)
project(${PROJECT_NAME})
set(QT_VERSION_MAJOR "6")

if (WIN32)
    message(STATUS "Windows")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Using MSVC.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /Zc:__cplusplus /Zc:inline /Zc:wchar_t /EHsc")
        set(CMAKE_PREFIX_PATH "C:/Qt/6.6.3/msvc2019_64/lib/cmake/Qt6")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Using MinGW g++.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
        set(CMAKE_PREFIX_PATH "C:/Qt/6.6.3/mingw_64/lib/cmake/Qt6")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Using llvm clang++.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++latest")
        set(CMAKE_PREFIX_PATH "C:/Qt/6.6.3/msvc2019_64/lib/cmake/Qt6")
    endif ()
elseif (UNIX)
    message(STATUS "Linux, using g++.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
endif ()

# if failed, use `"M:/vcpkg/installed/x64-windows/share"`
list(APPEND CMAKE_PREFIX_PATH "M:/vcpkg/installed/x64-windows")
#include("C:/Users/LiAu/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
find_package(Qt6
        REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        Xml
        Qml
        Quick
        QuickWidgets
        REQUIRED
)


# Find Python 3 interpreter
find_package(Python3 REQUIRED)
if (NOT Python3_EXECUTABLE)
    message(FATAL_ERROR "Python 3 interpreter not found")
endif ()
# Custom command to generate the .qrc file
add_custom_command(
        OUTPUT ${QRC_FILE_PATH}
        COMMAND ${Python3_EXECUTABLE} ${QRC_PYTHON_SCRIPT_PATH} ${CMAKE_CURRENT_SOURCE_DIR} ${QRC_FILE_PATH}
        DEPENDS ${QRC_PYTHON_SCRIPT_PATH}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating resources.qrc..."
)

# Custom target that depends on the .qrc file
add_custom_target(generate_qrc ALL DEPENDS ${QRC_FILE_PATH})


find_package(fmt CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
set(TARGET_LINK_PACKAGES
        fmt::fmt
        absl::base
        absl::log
        absl::any
        nlohmann_json::nlohmann_json
        magic_enum::magic_enum
)

set(PCH ${CMAKE_SOURCE_DIR}/pch)
file(GLOB GLOBAL_PCH_HEADER "${PCH}/*.hh")
# Define a function to collect and filter files
function(collect_and_filter_files out_var file_extension)
    file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/*.${file_extension}")
    list(FILTER files EXCLUDE REGEX "/build/")
    list(FILTER files EXCLUDE REGEX "/cmake-build-debug-visual-studio/")
    list(FILTER files EXCLUDE REGEX "/cmake-vscode-build/")
    list(FILTER files EXCLUDE REGEX "/Test/")
    set(${out_var} ${files} PARENT_SCOPE)
endfunction()

# Collect and filter the files
#collect_and_filter_files(SOURCE_FILE cpp)
#collect_and_filter_files(QT_UI_FILE ui)
#collect_and_filter_files(HEADER_FILE hpp)
#
#message(STATUS "SOURCE_FILE: ${SOURCE_FILE}")
#message(STATUS "HEADER_FILE: ${HEADER_FILE}")
#message(STATUS "QT_UI_FILE: ${QT_UI_FILE}")

set(SOURCE_FILE
        Models/Block.cpp
        Services/Blocks.cpp
        Views/game.cpp
        Views/menu.cpp
        Views/mainwindow.cpp
        ViewModels/blockswidget.cpp
        ViewModels/statuswidget.cpp
        Views/leaderboard.cpp
        Views/about.cpp
        Services/Records.cpp
)
set(UI_FILE
        Views/game.ui
        Views/menu.ui
        Views/mainwindow.ui
        ViewModels/blockswidget.ui
        ViewModels/statuswidget.ui
        Views/leaderboard.ui
        Views/about.ui
)
set(HEADER_FILE
        Helpers/RecordSerializer.hpp
        Models/Block.hpp
        Models/Point.hpp
        Services/Blocks.hpp
        Views/game.hpp
        Views/menu.hpp
        include/config.hpp
        Views/mainwindow.hpp
        ViewModels/blockswidget.hpp
        ViewModels/statuswidget.hpp
        Helpers/Animation.hpp
        Helpers/Actions.hpp
        Helpers/Sound.hpp
        Models/BlockButton.hpp
        Views/leaderboard.hpp
        Models/Record.hpp
        Services/Records.hpp
        Helpers/RecordComparator.hpp
        Views/about.hpp
        Contracts/ISerializer.hpp
)


add_executable(${PROJECT_NAME}
        main.cpp
        ${HEADER_FILE}
        ${SOURCE_FILE}
        ${QT_UI_FILE}
        ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        Qt::Xml
        Qt::Qml
        Qt::Quick
        ${TARGET_LINK_PACKAGES}
)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}
)
target_precompile_headers(${PROJECT_NAME} PRIVATE
        ${GLOBAL_PCH_HEADER}
)


# Ensure the build depends on the custom target
add_dependencies(${PROJECT_NAME} generate_qrc)

include(${CMAKE_CURRENT_SOURCE_DIR}/test_prog.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/clion_gen.cmake)
