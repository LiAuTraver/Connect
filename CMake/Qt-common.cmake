#set(QT_VERSION_MAJOR "6") # defined in presets
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

if (WIN32)
    message(STATUS "Windows")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Using MSVC.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /Zc:__cplusplus /Zc:inline /Zc:wchar_t /EHsc")
        #        if (NOT DEFINED CMAKE_PREFIX_PATH)
        #            set(CMAKE_PREFIX_PATH ${Qt6MSVC})
        # ^^^^^ if Qt6MSVC is not in the path, append it
        set(TEMP ${CMAKE_PREFIX_PATH})
        LIST(FILTER TEMP INCLUDE REGEX "Qt6")
        if (NOT TEMP)
            LIST(APPEND CMAKE_PREFIX_PATH ${Qt6MSVC})
        endif ()
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Using MinGW g++.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
        set(TEMP ${CMAKE_PREFIX_PATH})
        LIST(FILTER TEMP INCLUDE REGEX "Qt6")
        if (NOT TEMP)
            LIST(APPEND CMAKE_PREFIX_PATH ${Qt6MinGW})
        endif ()
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Using llvm clang++.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++latest")
        set(TEMP ${CMAKE_PREFIX_PATH})
        LIST(FILTER TEMP INCLUDE REGEX "Qt6")
        if (NOT TEMP)
            LIST(APPEND CMAKE_PREFIX_PATH ${Qt6Clang})
        endif ()
    endif ()
elseif (UNIX)
    message(WARNING "Linux is not configured.")
    message(STATUS "Linux, using g++.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
endif ()
