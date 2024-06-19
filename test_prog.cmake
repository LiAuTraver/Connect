add_executable(test
        Test/test.cpp
        ${HEADER_FILE}
        ${SOURCE_FILE}
        ${QT_UI_FILE}
)

target_link_libraries(test PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        Qt::Xml
        ${TARGET_LINK_PACKAGES}
)

target_include_directories(test PUBLIC
        ${CMAKE_SOURCE_DIR}
)
target_precompile_headers(test PRIVATE
        ${GLOBAL_PCH_HEADER}
)


# Ensure the build depends on the custom target
add_dependencies(test generate_qrc)
