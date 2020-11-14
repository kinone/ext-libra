cmake_minimum_required(VERSION 3.17)
project(ext_libra)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)
include_directories(src)
include_directories(include /usr/include/php /usr/include/php/main /usr/include/php/Zend /usr/include/php/TSRM/)
include_directories(/opt/apps/libwebp/include /opt/apps/opencv/include)

link_directories(/opt/apps/libwebp/lib /opt/apps/opencv/lib)

link_libraries(webp webpmux opencv_core opencv_imgproc opencv_imgcodecs)

add_library(libra SHARED
        src/Image.cpp
        src/Image.h
        src/Kaleido.cpp
        src/Kaleido.h
        src/Utils.cpp
        src/Utils.h
        src/Sequence.cpp
        src/Sequence.h
        libra.cpp
        libra_kaleido.cpp
        libra_kaleido.h
        libra_image.cpp
        libra_image.h
        libra_sequence.cpp
        libra_sequence.h
        php_libra.h)
