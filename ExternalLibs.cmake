cmake_minimum_required(VERSION 3.1)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Add third party libraries
ExternalProject_Add(GLFW3
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/glfw
  CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DGLFW_INSTALL=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF
  BUILD_COMMAND cmake --build . --config MinSizeRel
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)

if(MSVC)
  set(GLFW3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/glfw/include)
  set(GLFW3_LIBRARY ${CMAKE_BINARY_DIR}/GLFW3-prefix/src/GLFW3-build/src/MinSizeRel/glfw3.lib)
else(MSVC)
  set(GLFW3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/glfw/include)
  set(GLFW3_LIBRARY ${CMAKE_BINARY_DIR}/GLFW3-prefix/src/GLFW3-build/src/libglfw3.a)
endif(MSVC)

ExternalProject_Add(ZLIB
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/zlib
  CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true
  BUILD_COMMAND cmake --build . --target zlibstatic --config MinSizeRel
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)

if(MSVC)
  set(ZLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/zlib)
  set(ZLIB_LIBRARY ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/MinSizeRel/zlibstatic.lib)
elseif(MINGW)
  set(ZLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/zlib)
  set(ZLIB_LIBRARY ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/libzlibstatic.a)
else()
  set(ZLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/zlib)
  set(ZLIB_LIBRARY ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/libz.a)
endif()

if(MSVC)
  ExternalProject_Add(LIBPNG
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/libpng
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DPNG_FRAMEWORK=OFF -DPNG_SHARED=OFF -DPNG_STATIC=ON -DPNG_TESTS=OFF -DZLIB_INCLUDE_DIR=${CMAKE_SOURCE_DIR}/libs/zlib -DCMAKE_INCLUDE_PATH=${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build -DZLIB_LIBRARY=${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/MinSizeRel/zlibstatic
    BUILD_COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/zconf.h ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build && cmake --build . --config MinSizeRel
    INSTALL_COMMAND ""
    TEST_COMMAND ""
  )
  add_dependencies(LIBPNG ZLIB)
elseif(MINGW)
  ExternalProject_Add(LIBPNG
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/libpng
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DPNG_FRAMEWORK=OFF -DPNG_SHARED=OFF -DPNG_STATIC=ON -DPNG_TESTS=OFF -DZLIB_INCLUDE_DIR=${CMAKE_SOURCE_DIR}/libs/zlib -DZLIB_LIBRARY=${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/libzlibstatic.a
    BUILD_COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/zconf.h ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build && cmake --build . --config MinSizeRel
    INSTALL_COMMAND ""
    TEST_COMMAND ""
  )
  add_dependencies(LIBPNG ZLIB)
else()
  ExternalProject_Add(LIBPNG
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/libpng
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DPNG_FRAMEWORK=OFF -DPNG_SHARED=OFF -DPNG_STATIC=ON -DPNG_TESTS=OFF -DZLIB_INCLUDE_DIR=${CMAKE_SOURCE_DIR}/libs/zlib -DZLIB_LIBRARY=${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/libz.a -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true
    BUILD_COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/zconf.h ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build && cmake --build . --config MinSizeRel
    INSTALL_COMMAND ""
    TEST_COMMAND ""
  )
  add_dependencies(LIBPNG ZLIB)
endif()

if(MSVC)
  set(LIBPNG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/libpng ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build)
  set(LIBPNG_LIBRARY ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build/MinSizeRel/libpng16_static.lib)
else(MSVC)
  set(LIBPNG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/libpng ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build)
  set(LIBPNG_LIBRARY ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build/libpng16.a)
endif(MSVC)

ExternalProject_Add(FREETYPE2
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/freetype2
  CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true
  BUILD_COMMAND cmake --build . --config MinSizeRel
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
add_dependencies(FREETYPE2 LIBPNG)

if(MSVC)
  set(FREETYPE2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/freetype2/include)
  set(FREETYPE2_LIBRARY ${CMAKE_BINARY_DIR}/FREETYPE2-prefix/src/FREETYPE2-build/MinSizeRel/freetype.lib)
else(MSVC)
  set(FREETYPE2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/freetype2/include)
  set(FREETYPE2_LIBRARY ${CMAKE_BINARY_DIR}/FREETYPE2-prefix/src/FREETYPE2-build/libfreetype.a)
endif(MSVC)

if(UNIX OR APPLE)
  ExternalProject_Add(BZIP2
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/bzip2-1.0.6
    CONFIGURE_COMMAND ""
    BUILD_COMMAND cd ${CMAKE_SOURCE_DIR}/libs && chmod +x ./make_bzip2.sh && ./make_bzip2.sh ${CMAKE_BINARY_DIR}/BZIP2-prefix/src/BZIP2-build
    INSTALL_COMMAND ""
    TEST_COMMAND ""
  )

  set(BZIP2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/bzip2-1.0.6)
  set(BZIP2_LIBRARY ${CMAKE_BINARY_DIR}/BZIP2-prefix/src/BZIP2-build/libbz2.a)
endif()

set(NANOVG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/nanovg/src)
set(TINYXML2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/tinyxml2/tinyxml2)

ExternalProject_Add(FINEGRAPHICS
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/finegraphics
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  BUILD_COMMAND cmake --build . --config $<CONFIG>
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)

set(FINEGRAPHICS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/finegraphics/include)
if(MSVC)
  set(FINEGRAPHICS_LIBRARY ${CMAKE_BINARY_DIR}/FINEGRAPHICS-prefix/src/FINEGRAPHICS-build/${CMAKE_BUILD_TYPE}/finegraphics.lib)
  set(FINEGRAPHICS_BIN ${CMAKE_BINARY_DIR}/FINEGRAPHICS-prefix/src/FINEGRAPHICS-build/${CMAKE_BUILD_TYPE}/finegraphics.dll)
elseif(MINGW)
  set(FINEGRAPHICS_LIBRARY ${CMAKE_BINARY_DIR}/FINEGRAPHICS-prefix/src/FINEGRAPHICS-build/libfinegraphics.a)
  set(FINEGRAPHICS_BIN ${CMAKE_BINARY_DIR}/FINEGRAPHICS-prefix/src/FINEGRAPHICS-build/libfinegraphics.dll)
elseif(APPLE)
  set(FINEGRAPHICS_LIBRARY ${CMAKE_BINARY_DIR}/FINEGRAPHICS-prefix/src/FINEGRAPHICS-build/libfinegraphics.dylib)
  set(FINEGRAPHICS_BIN ${CMAKE_BINARY_DIR}/FINEGRAPHICS-prefix/src/FINEGRAPHICS-build/libfinegraphics.dylib)
elseif(UNIX)
  set(FINEGRAPHICS_LIBRARY ${CMAKE_BINARY_DIR}/FINEGRAPHICS-prefix/src/FINEGRAPHICS-build/libfinegraphics.so)
  set(FINEGRAPHICS_BIN ${CMAKE_BINARY_DIR}/FINEGRAPHICS-prefix/src/FINEGRAPHICS-build/libfinegraphics.so)
endif()
