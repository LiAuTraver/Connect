add_executable(test
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/textedit.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/test/textedit.cpp
        ${HEADER_FILE}
        ${SOURCE_FILE}
        ${QT_UI_FILE}
        ${resources}
)

target_link_libraries(test PRIVATE
        ${TARGET_QT_LINK_PACKAGES}
        ${TARGET_LINK_PACKAGES}
)

target_include_directories(test PUBLIC
        ${CMAKE_SOURCE_DIR}
)
target_precompile_headers(test PRIVATE
        ${GLOBAL_PCH_HEADER}
)


# Ensure the build depends on the custom target
#add_dependencies(test generate_qrc)
