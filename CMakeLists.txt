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
list(APPEND CMAKE_PREFIX_PATH "M:/vcpkg/installed/x64-windows")
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

find_package(Qt6
        REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        Xml
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
set(TARGET_LINK_PACKAGES
        fmt::fmt
        absl::base
        absl::log
        absl::any
        nlohmann_json::nlohmann_json
)

set(PCH ${CMAKE_SOURCE_DIR}/pch)
file(GLOB GLOBAL_PCH_HEADER "${PCH}/*.hh")
# Define a function to collect and filter files
function(collect_and_filter_files out_var fileext)
    file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/*.${fileext}")
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Contracts/IFileService.cpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers/NotImplementedException.cpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers/Parser.cpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Models/Block.cpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Models/Point.cpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Services/Blocks.cpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/game.cpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/menu.cpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/mainwindow.cpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
set(UI_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/game.ui;
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/menu.ui;
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/mainwindow.ui
)
set(HEADER_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/Contracts/IFileService.hpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers/NotImplementedException.hpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers/Parser.hpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Models/Block.hpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Models/Point.hpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Services/Blocks.hpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/game.hpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/menu.hpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/mainwindow.hpp;
        ${CMAKE_CURRENT_SOURCE_DIR}/include/config.hpp
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
