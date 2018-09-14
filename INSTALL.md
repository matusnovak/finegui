# Installing

You can compile the FineGui from the source code (see below), or [use one of the automatically built releases from GitHub Releases](https://github.com/matusnovak/finegui/releases).

## Windows

```bash
# Clone the repository
git clone https://github.com/matusnovak/finegui
cd finegui

# Download the dependencies
git submodule init
git submodule update

# Create build folder and run cmake
mkdir build
cd build

# You can replace the "Visual Studio 15 2017" with 
# "Visual Studio 15 2017 Win64" to compile for 64-bit applications.
# You can also replace it with -G "MinGW Makefiles"
cmake .. -G "Visual Studio 15 2017" -DCMAKE_INSTALL_PREFIX=C:/...

# Build using cmake (or open it in Visual Studio IDE)
cmake --build . --target ALL_BUILD --config MinSizeRel

# Optionally run the INSTALL
cmake --build . --target INSTALL --config MinSizeRel
```

### Usage example

To use in your project in Visual Studio, follow these instructions below.

Please note that if you have downloaded the finegui from the GitHub releases, the lib (and the bin) folder contains both the Release and Debug version of the library. The Debug version ends in `_d.lib` and `_.dll`. When compiling it manually, use the `--config MinSizeRel` or `--config Debug` to compile your desired configuration. When compiling your project in Debug mode, you must use the Debug version of the `.lib` and `.dll`. Otherwise compilation errors will appear.

1. In the Solution Explorer, right click on your project and select Properties.
2. Select Release or Debug in the Configuration at the top. **Make sure to select the correct configuration!.**
3. In Configuration Properties -> C++ -> General -> Additional Include Directories add `C:\path\to\finegui\install\include`.
4. In Configuration Properties -> Linker -> General -> Additional Library Directories add  `C:\path\to\finegui\install\lib`.
5. In Configuration Properties -> Linker -> Input -> Additional Dependencies add `finegui.lib`.
6. Copy the `finegui.dll` from `C:\path\to\finegui\install\bin` to your project build directory (where your project exe will be generated). This is not needed during the compilation, but you will need it to distribute or run the program. Otherwise you will get "The program can't start because finegui.dll is missing from your computer. Alternatively, put it in your PATH variable.

## Linux

Install this packages before compiling. These are needed for git, cmake, g++, OpenGL, and X11. 
When distributing an application linked with FineGui, these packages are not required for the users.

```bash
sudo apt install build-essential git cmake xorg-dev libgl1-mesa-glx libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

Then, compile from the source code:

```bash
# Clone the repository
git clone https://github.com/matusnovak/finegui
cd finegui

# Download the dependencies
git submodule init
git submodule update

# Create build folder and run cmake
mkdir build
cd build

# You can add -G "Unix Makefiles" right after .. if you wish
cmake ..  -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=MinSizeRel

# Build
make all

# Optionally run the INSTALL step
sudo make install
```

### Usage example

Now, you will be able to use FineGui the following way:

```
$ g++ -c example.cpp -o example.o -std=c++11 -I/usr/local/include
$ g++ -o example example.o -L/usr/local/lib -lGL -lfinegraphics
$ ./example
```

If you want your executable to be portable (for example, distributing it on other systems) you might want to add `-Wl,-rpath='${ORIGIN}'` after `g++ -o example example.o`. Then, simply copy the necessary `libfinegui.so` file into the executable folder.

## Mac OS X

You will need XCode, cmake, and Clang LLVM toolchain installed.

```
$ brew install --with-clang llvm
$ brew install cmake
```

Make sure your clang is 3.6 or newer:

```
$ clang++ --version
```

Then, compile from the source code:

```bash
# Clone the repository
git clone https://github.com/matusnovak/finegui
cd finegui

# Download the dependencies
git submodule init
git submodule update

# Create build folder and run cmake
mkdir build
cd build

# You can add -G "Unix Makefiles" right after .. if you wish
cmake ..  -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=MinSizeRel

# Build
make all

# Optionally run the INSTALL step
sudo make install
```

### Usage example

```
$ clang++ -c example.cpp -o example.o -std=c++11 -I/usr/local/include
$ clang++ -o example example.o -L/System/Library/Frameworks -L/usr/local/lib -framework OpenGL -lfinegraphics 
$ ./example
```

Don't forget to point to `-I/usr/local/include` for header files and `-L/usr/local/lib` for library files! You can change the `/usr/local/include` to any other location you want by changing the `CMAKE_INSTALL_PREFIX` during cmake configuration. Alternatively point the `-L...` and `-I...` to the cmake build folder.
