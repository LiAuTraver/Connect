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
file(GLOB_RECURSE SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE QT_UI_FILE "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
file(GLOB_RECURSE HEADER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

# Exclude specific directories from SOURCE_FILES
list(FILTER SOURCE_FILE EXCLUDE REGEX "/build/")
list(FILTER SOURCE_FILE EXCLUDE REGEX "/cmake-build-debug-visual-studio/")
list(FILTER SOURCE_FILE EXCLUDE REGEX "/cmake-vscode-build/")

list(FILTER HEADER_FILE EXCLUDE REGEX "/build/")
list(FILTER HEADER_FILE EXCLUDE REGEX "/cmake-build-debug-visual-studio/")
list(FILTER HEADER_FILE EXCLUDE REGEX "/cmake-vscode-build/")

list(FILTER QT_UI_FILE EXCLUDE REGEX "/build/")
list(FILTER QT_UI_FILE EXCLUDE REGEX "/cmake-build-debug-visual-studio/")
list(FILTER QT_UI_FILE EXCLUDE REGEX "/cmake-vscode-build/")

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
