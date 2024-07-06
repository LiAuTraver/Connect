cmake_minimum_required(VERSION 3.26)
project(Connect)

include(${CMAKE_SOURCE_DIR}/CMake/Qt-common.cmake)
include(${CMAKE_SOURCE_DIR}/CMake/vcpkg-common.cmake)
include(${CMAKE_SOURCE_DIR}/CMake/common.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/Qt-import-dlls.cmake)

# Set project-specific settings
set(PROJECT_NAME Connect)
set(QRC_FILE_PATH resources.qrc)
set(QRC_PYTHON_SCRIPT_PATH generate_qrc.py)
set(QRC_JSON_FILE_PATH resources.json)

find_package(Python3 REQUIRED)

if (NOT Python3_EXECUTABLE)
    message(FATAL_ERROR "Python 3 interpreter not found")
endif ()
# Custom command to generate the .qrc file
add_custom_command(
        OUTPUT ${QRC_FILE_PATH} ${QRC_JSON_FILE_PATH}
        COMMAND ${Python3_EXECUTABLE} ${QRC_PYTHON_SCRIPT_PATH} ${CMAKE_CURRENT_SOURCE_DIR} ${QRC_FILE_PATH} ${QRC_JSON_FILE_PATH}
        DEPENDS ${QRC_PYTHON_SCRIPT_PATH}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating resources.qrc and resources.json..."
)
# Include necessary packages
find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED
)
find_package(fmt CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

set(TARGET_QT_LINK_PACKAGES
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia
)

set(TARGET_LINK_PACKAGES
        fmt::fmt
        absl::base
        absl::log
        absl::any
        absl::status
        magic_enum::magic_enum
)

# `resource` now is the name when we use `Q_INIT_RESOURCE()`
# connot forget to add this to the target
qt_add_resources(resources ${QRC_FILE_PATH})


# Include PCH
set(PCH ${CMAKE_CURRENT_SOURCE_DIR}/pch)
file(GLOB GLOBAL_PCH_HEADER "${PCH}/*.hh")

# Define UI files
set(UI_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/game.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/menu.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/mainwindow.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/blockswidget.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/statuswidget.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/leaderboard.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/about.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/pastgamewidget.ui
)

# Define source files
set(SOURCE_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/Services/Blocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/menu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/blockswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/statuswidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/leaderboard.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/about.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Services/Records.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/addrecorddialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/pastgamewidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Services/Sound.cpp
)

# Define header files
set(HEADER_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers/RecordSerializer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Models/Point.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Services/Blocks.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/game.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/menu.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/config.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/mainwindow.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/blockswidget.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/statuswidget.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Services/Animation.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/details.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Services/Sound.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Models/BlockButton.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/leaderboard.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Models/Record.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Services/Records.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Views/about.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/addrecorddialog.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers/ButtonComparator.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewModels/pastgamewidget.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers/ResourcesSerializer.hpp
)

# Add executable
add_executable(${PROJECT_NAME}
        main.cpp
        ${resources}
        ${HEADER_FILE}
        ${SOURCE_FILE}
        ${UI_FILE}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${TARGET_QT_LINK_PACKAGES}
        ${TARGET_LINK_PACKAGES}
)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)
target_precompile_headers(${PROJECT_NAME} PRIVATE
        ${GLOBAL_PCH_HEADER}
)


# Add custom target
add_custom_target(generate_qrc ALL DEPENDS ${QRC_FILE_PATH} ${QRC_JSON_FILE_PATH})

# Ensure the build depends on the custom target, temporarily disable it because it runs every time as a dependency.
# add_dependencies(${PROJECT_NAME} generate_qrc)
# ^^^^^^ run it via cmake --build .(build dir) --target generate_qrc

include(CMake/unit_test.cmake)
