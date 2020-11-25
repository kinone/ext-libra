cmake_minimum_required(VERSION 3.17)
project(ext-libra)

set(CMAKE_CXX_STANDARD 98)

include_directories(. src include)

set(GLOBAL_INCLUDE /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include)
set(PHP_INCLUDE /usr/local/include/php)

include_directories(
        ${GLOBAL_INCLUDE}
        ${PHP_INCLUDE}
        ${PHP_INCLUDE}/main
        ${PHP_INCLUDE}/Zend
        ${PHP_INCLUDE}/TSRM
        /opt/apps/opencv/include
        /opt/apps/libwebp/include
)

link_directories(/opt/apps/libwebp/lib /opt/apps/opencv/lib)

link_libraries(webp webpmux opencv_core opencv_imgproc opencv_imgcodecs)

add_library(libra SHARED
        src/Image.cpp
        src/Utils.cpp
        src/Kaleido.cpp
        src/Logger.cpp
        src/Sequence.cpp
        src/Container.cpp
        src/Animate.cpp
        libra.cpp
        php_libra.h
        libra_image.cpp
        libra_image.h
        libra_kaleido.cpp
        libra_kaleido.h
        libra_sequence.cpp
        libra_sequence.h
        libra_interface.h
        libra_interface.cpp
        libra_container.cpp
        libra_container.h)