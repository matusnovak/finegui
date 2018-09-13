# FineGui

|         | CircleCI | TravisCI | AppVeyor |
|---------|----------|----------|----------|
| master  | [![CircleCI](https://circleci.com/gh/matusnovak/finegui/tree/master.svg?style=svg)](https://circleci.com/gh/matusnovak/finegui/tree/master) | [![Build Status](https://travis-ci.org/matusnovak/finegui.svg?branch=master)](https://travis-ci.org/matusnovak/finegui) | [![Build status](https://ci.appveyor.com/api/projects/status/7ptts9y3grin6jqs/branch/master?svg=true)](https://ci.appveyor.com/project/matusnovak/finegui/branch/master) |
| devel  | [![CircleCI](https://circleci.com/gh/matusnovak/finegui/tree/devel.svg?style=svg)](https://circleci.com/gh/matusnovak/finegui/tree/devel) | [![Build Status](https://travis-ci.org/matusnovak/finegui.svg?branch=devel)](https://travis-ci.org/matusnovak/finegui) | [![Build status](https://ci.appveyor.com/api/projects/status/7ptts9y3grin6jqs/branch/devel?svg=true)](https://ci.appveyor.com/project/matusnovak/finegui/branch/devel) |

*The following compilers are tested in the CI above: Visual Studio 2013, Visual Studio 2013 Win64, Visual Studio 2015, Visual Studio 2015 Win64, Visual Studio 2017, Visual Studio 2017 Win64, MinGW-w64 i686, MinGW-w64 x86_64, Linux GCC 5.5.0, Linux GCC 6.4.0, Linux GCC 5.5.0, Linux GCC 7.3.0, and OSX Clang 3.7*

## Introduction 

The FineGui is a standalone library that provides a simple utf8 enabled graphical user interface with a linear layout system similar to Android GUI development. The library also offers experimental XML parser that generates GUI structure for you. This library is not meant to be the best GUI library in the world. Instead, it offers a simple backend API that can be integrated into any renderer you want. The purpose of this abstract backend is to enable embeding this library into IoT devices that, for example, do not use hardware acceleration. The backend would be your custom CPU based renderer that writes pixels directly into, for example, an LCD. However, there is FineGraphics and NanoVG backends included. See the example folder for more. 

This library uses only header only utfcpp library and tinyxml2, all other libraries are only needed to run the examples. The third party libraries are optional, can be disabled through cmake `-DBUILD_EXAMPLES:BOOL=OFF` and are compiled automatically though cmake. 

**API Documentation is provided at <http://matusnovak.github.io/finegui/>**

## Dependencies

All dependencies listed here are already included as a git submodule and will be statically linked to the examples. Therefore, no need to compile them manually, nor link them manually! Everything is automated via CMake.

* [utfcpp](https://github.com/ledger/utfcpp) - For handling utf8 strings (header only library)
* [tinyxml2](https://github.com/leethomason/tinyxml2.git) - For parsing XML files (included directly)
* [freetype2](https://www.freetype.org/) - Examples only
* [glfw](https://www.glfw.org/) - Examples only
* [libpng](https://github.com/glennrp/libpng) - Examples only
* [nanovg](https://github.com/memononen/nanovg) - Examples only
* [tinyobjloader](https://github.com/syoyo/tinyobjloader.git) - Examples only
* [zlib](https://github.com/madler/zlib) - Examples only
* [bzip2](https://github.com/enthought/bzip2-1.0.6) - Examples only

## TODO

* More examples, documentation, and tutorials
* More unit tests
* More backends such as a simple CPU pixel renderer

## Quick example

TODO

## Requirements

One of the following compilers:

* (Windows) Visual Studio 2013 32-bit or 64-bit
* (Windows) Visual Studio 2015 32-bit or 64-bit
* (Windows) Visual Studio 2017 32-bit or 64-bit
* (Windows) MinGW-w64 i686
* (Windows) MinGW-w64 x86_64
* (Linux) GCC 4.9 or newer
* (OSX) Clang 3.7 or newer

## Compiling FineGui

You can [use one of the automatically built releases from GitHub Releases](https://github.com/matusnovak/finegui/releases) or compile it manually by following the [Install Guide](./INSTALL.md) (Don't worry, it's easy). 

## Using FineGui

### Windows

First, compile the library (see section above), next to use the finegui in your project, simply include the `C:/path/to/finegui/include` and link the `finegui.lib`. You will also need the `finegui.dll` in order to run the application. Simply copy the DLL into the executable folder. You can find the `.lib` and `.dll` files in the cmake build folder.

### Linux/OSX

First, compile the library (see section above), next to use the finegui in your project, simply include the `~/finegui/include` (or `/usr/local/include` if you have installed it) and link the `finegui.so`. You can find the `.so` files in the cmake build folder (or at the installed path provided by CMAKE_INSTALL_PREFIX).

If you are planning to distribute your application with FineGui, you will need to copy the `finegui.so` and include it within your application. For example, the most simple way, copy it into the executable folder (same as in Windows).

## Documentation

Documentation can be found at <http://matusnovak.github.io/finegui/>

## Examples

All examples are located in the [examples folder](examples/README.md).

## Alternatives

Looking for alternative library or framework? Try OpenFrameworks, SFML, or Cinder (be warned, they are much more bigger, but feature rich).

## Contributing

Feel free to post a question in GitHub issues. Pull requests are welcome! 

## Contact

Feel free to contact me on my email (see my GitHub profile).

## License

<https://en.wikipedia.org/wiki/MIT_License>

```
The MIT License (MIT)

Copyright (c) 2018 Matus Novak

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```