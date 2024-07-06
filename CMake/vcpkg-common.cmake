#set(CMAKE_TOOLCHAIN_FILE "C:/Users/LiAu/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")
if (NOT DEFINED VCPKG_CMAKE_PATH)
    set(VCPKG_CMAKE_PATH "M:/vcpkg/installed/x64-windows")
endif ()
# if failed, use `"M:/vcpkg/installed/x64-windows/share"`
list(APPEND CMAKE_PREFIX_PATH ${VCPKG_CMAKE_PATH})
#include("C:/Users/LiAu/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")
