(window.webpackJsonp=window.webpackJsonp||[]).push([[256],{451:function(e,t,a){"use strict";a.r(t);var n=a(0),s=Object(n.a)({},function(){var e=this,t=e.$createElement,a=e._self._c||t;return a("div",{staticClass:"content"},[e._m(0),e._v(" "),a("p",[e._v("You can compile the FineGraphics from the source code (see below), or "),a("a",{attrs:{href:"https://github.com/matusnovak/finegraphics/releases",target:"_blank",rel:"noopener noreferrer"}},[e._v("use one of the automatically built releases from GitHub Releases"),a("OutboundLink")],1),e._v(".")]),e._v(" "),e._m(1),e._v(" "),e._m(2),e._m(3),e._v(" "),a("p",[e._v("To use in your project in Visual Studio, follow these instructions below.")]),e._v(" "),e._m(4),e._v(" "),e._m(5),e._v(" "),e._m(6),e._v(" "),a("p",[e._v("Install this packages before compiling. These are needed for git, cmake, g++, OpenGL, and X11.\nWhen distributing an application linked with FineGraphics, these packages are not required for the users.")]),e._v(" "),e._m(7),a("p",[e._v("Then, compile from the source code:")]),e._v(" "),e._m(8),e._m(9),e._v(" "),a("p",[e._v("Now, you will be able to use FineGraphics the following way:")]),e._v(" "),e._m(10),e._m(11),e._v(" "),e._m(12),e._v(" "),a("p",[e._v("You will need XCode, cmake, and Clang LLVM toolchain installed.")]),e._v(" "),e._m(13),a("p",[e._v("Make sure your clang is 3.6 or newer:")]),e._v(" "),e._m(14),a("p",[e._v("Then, compile from the source code:")]),e._v(" "),e._m(15),e._m(16),e._v(" "),e._m(17),e._m(18)])},[function(){var e=this.$createElement,t=this._self._c||e;return t("h1",{attrs:{id:"installing"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#installing","aria-hidden":"true"}},[this._v("#")]),this._v(" Installing")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"windows"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#windows","aria-hidden":"true"}},[this._v("#")]),this._v(" Windows")])},function(){var e=this,t=e.$createElement,a=e._self._c||t;return a("div",{staticClass:"language-bash extra-class"},[a("pre",{pre:!0,attrs:{class:"language-bash"}},[a("code",[a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Clone the repository")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("git")]),e._v(" clone https://github.com/matusnovak/finegraphics\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("cd")]),e._v(" finegraphics\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Download the dependencies")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("git")]),e._v(" submodule init\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("git")]),e._v(" submodule update\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Create build folder and run cmake")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("mkdir")]),e._v(" build\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("cd")]),e._v(" build\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v('# You can replace the "Visual Studio 15 2017" with ')]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v('# "Visual Studio 15 2017 Win64" to compile for 64-bit applications.')]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v('# You can also replace it with -G "MinGW Makefiles"')]),e._v("\ncmake "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[e._v("..")]),e._v(" -G "),a("span",{pre:!0,attrs:{class:"token string"}},[e._v('"Visual Studio 15 2017"')]),e._v(" -DCMAKE_INSTALL_PREFIX"),a("span",{pre:!0,attrs:{class:"token operator"}},[e._v("=")]),e._v("C:/"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[e._v("..")]),e._v(".\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Build using cmake (or open it in Visual Studio IDE)")]),e._v("\ncmake --build "),a("span",{pre:!0,attrs:{class:"token keyword"}},[e._v(".")]),e._v(" --target ALL_BUILD --config MinSizeRel\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Optionally run the INSTALL")]),e._v("\ncmake --build "),a("span",{pre:!0,attrs:{class:"token keyword"}},[e._v(".")]),e._v(" --target INSTALL --config MinSizeRel\n")])])])},function(){var e=this.$createElement,t=this._self._c||e;return t("h3",{attrs:{id:"usage-example"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#usage-example","aria-hidden":"true"}},[this._v("#")]),this._v(" Usage example")])},function(){var e=this,t=e.$createElement,a=e._self._c||t;return a("p",[e._v("Please note that if you have downloaded the finegraphics from the GitHub releases, the lib (and the bin) folder contains both the Release and Debug version of the library. The Debug version ends in "),a("code",[e._v("_d.lib")]),e._v(" and "),a("code",[e._v("_.dll")]),e._v(". When compiling it manually, use the "),a("code",[e._v("--config MinSizeRel")]),e._v(" or "),a("code",[e._v("--config Debug")]),e._v(" to compile your desired configuration. When compiling your project in Debug mode, you must use the Debug version of the "),a("code",[e._v(".lib")]),e._v(" and "),a("code",[e._v(".dll")]),e._v(". Otherwise compilation errors will appear.")])},function(){var e=this,t=e.$createElement,a=e._self._c||t;return a("ol",[a("li",[e._v("In the Solution Explorer, right click on your project and select Properties.")]),e._v(" "),a("li",[e._v("Select Release or Debug in the Configuration at the top. "),a("strong",[e._v("Make sure to select the correct configuration!.")])]),e._v(" "),a("li",[e._v("In Configuration Properties -> C++ -> General -> Additional Include Directories add "),a("code",[e._v("C:\\path\\to\\finegraphics\\install\\include")]),e._v(".")]),e._v(" "),a("li",[e._v("In Configuration Properties -> Linker -> General -> Additional Library Directories add  "),a("code",[e._v("C:\\path\\to\\finegraphics\\install\\lib")]),e._v(".")]),e._v(" "),a("li",[e._v("In Configuration Properties -> Linker -> Input -> Additional Dependencies add "),a("code",[e._v("finegraphics.lib")]),e._v(".")]),e._v(" "),a("li",[e._v("Copy the "),a("code",[e._v("fineframework.dll")]),e._v(" from "),a("code",[e._v("C:\\path\\to\\finegraphics\\install\\bin")]),e._v(" to your project build directory (where your project exe will be generated). This is not needed during the compilation, but you will need it to distribute or run the program. Otherwise you will get \"The program can't start because finegraphics.dll is missing from your computer. Alternatively, put it in your PATH variable.")])])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"linux"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#linux","aria-hidden":"true"}},[this._v("#")]),this._v(" Linux")])},function(){var e=this.$createElement,t=this._self._c||e;return t("div",{staticClass:"language-bash extra-class"},[t("pre",{pre:!0,attrs:{class:"language-bash"}},[t("code",[t("span",{pre:!0,attrs:{class:"token function"}},[this._v("sudo")]),this._v(" apt "),t("span",{pre:!0,attrs:{class:"token function"}},[this._v("install")]),this._v(" build-essential "),t("span",{pre:!0,attrs:{class:"token function"}},[this._v("git")]),this._v(" cmake xorg-dev libgl1-mesa-glx libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev\n")])])])},function(){var e=this,t=e.$createElement,a=e._self._c||t;return a("div",{staticClass:"language-bash extra-class"},[a("pre",{pre:!0,attrs:{class:"language-bash"}},[a("code",[a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Clone the repository")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("git")]),e._v(" clone https://github.com/matusnovak/finegraphics\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("cd")]),e._v(" finegraphics\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Download the dependencies")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("git")]),e._v(" submodule init\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("git")]),e._v(" submodule update\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Create build folder and run cmake")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("mkdir")]),e._v(" build\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("cd")]),e._v(" build\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v('# You can add -G "Unix Makefiles" right after .. if you wish')]),e._v("\ncmake "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[e._v("..")]),e._v("  -DCMAKE_INSTALL_PREFIX"),a("span",{pre:!0,attrs:{class:"token operator"}},[e._v("=")]),e._v("/usr/local -DCMAKE_BUILD_TYPE"),a("span",{pre:!0,attrs:{class:"token operator"}},[e._v("=")]),e._v("MinSizeRel\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Build")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("make")]),e._v(" all\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Optionally run the INSTALL step")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("sudo")]),e._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("make")]),e._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("install")]),e._v("\n")])])])},function(){var e=this.$createElement,t=this._self._c||e;return t("h3",{attrs:{id:"usage-example-2"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#usage-example-2","aria-hidden":"true"}},[this._v("#")]),this._v(" Usage example")])},function(){var e=this.$createElement,t=this._self._c||e;return t("div",{staticClass:"language- extra-class"},[t("pre",{pre:!0,attrs:{class:"language-text"}},[t("code",[this._v("$ g++ -c example.cpp -o example.o -std=c++11 -I/usr/local/include\n$ g++ -o example example.o -L/usr/local/lib -lGL -lfinegraphics\n$ ./example\n")])])])},function(){var e=this.$createElement,t=this._self._c||e;return t("p",[this._v("If you want your executable to be portable (for example, distributing it on other systems) you might want to add "),t("code",[this._v("-Wl,-rpath='${ORIGIN}'")]),this._v(" after "),t("code",[this._v("g++ -o example example.o")]),this._v(". Then, simply copy the necessary "),t("code",[this._v("libfinegraphics.so")]),this._v(" file into the executable folder.")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"mac-os-x"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#mac-os-x","aria-hidden":"true"}},[this._v("#")]),this._v(" Mac OS X")])},function(){var e=this.$createElement,t=this._self._c||e;return t("div",{staticClass:"language- extra-class"},[t("pre",{pre:!0,attrs:{class:"language-text"}},[t("code",[this._v("$ brew install --with-clang llvm\n$ brew install cmake\n")])])])},function(){var e=this.$createElement,t=this._self._c||e;return t("div",{staticClass:"language- extra-class"},[t("pre",{pre:!0,attrs:{class:"language-text"}},[t("code",[this._v("$ clang++ --version\n")])])])},function(){var e=this,t=e.$createElement,a=e._self._c||t;return a("div",{staticClass:"language-bash extra-class"},[a("pre",{pre:!0,attrs:{class:"language-bash"}},[a("code",[a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Clone the repository")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("git")]),e._v(" clone https://github.com/matusnovak/finegraphics\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("cd")]),e._v(" finegraphics\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Download the dependencies")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("git")]),e._v(" submodule init\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("git")]),e._v(" submodule update\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Create build folder and run cmake")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("mkdir")]),e._v(" build\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("cd")]),e._v(" build\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v('# You can add -G "Unix Makefiles" right after .. if you wish')]),e._v("\ncmake "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[e._v("..")]),e._v("  -DCMAKE_INSTALL_PREFIX"),a("span",{pre:!0,attrs:{class:"token operator"}},[e._v("=")]),e._v("/usr/local -DCMAKE_BUILD_TYPE"),a("span",{pre:!0,attrs:{class:"token operator"}},[e._v("=")]),e._v("MinSizeRel\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Build")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("make")]),e._v(" all\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[e._v("# Optionally run the INSTALL step")]),e._v("\n"),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("sudo")]),e._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("make")]),e._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[e._v("install")]),e._v("\n")])])])},function(){var e=this.$createElement,t=this._self._c||e;return t("h3",{attrs:{id:"usage-example-3"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#usage-example-3","aria-hidden":"true"}},[this._v("#")]),this._v(" Usage example")])},function(){var e=this.$createElement,t=this._self._c||e;return t("div",{staticClass:"language- extra-class"},[t("pre",{pre:!0,attrs:{class:"language-text"}},[t("code",[this._v("$ clang++ -c example.cpp -o example.o -std=c++11 -I/usr/local/include\n$ clang++ -o example example.o -L/System/Library/Frameworks -L/usr/local/lib -framework OpenGL -lfinegraphics \n$ ./example\n")])])])},function(){var e=this,t=e.$createElement,a=e._self._c||t;return a("p",[e._v("Don't forget to point to "),a("code",[e._v("-I/usr/local/include")]),e._v(" for header files and "),a("code",[e._v("-L/usr/local/lib")]),e._v(" for library files! You can change the "),a("code",[e._v("/usr/local/include")]),e._v(" to any other location you want by changing the "),a("code",[e._v("CMAKE_INSTALL_PREFIX")]),e._v(" during cmake configuration. Alternatively point the "),a("code",[e._v("-L...")]),e._v(" and "),a("code",[e._v("-I...")]),e._v(" to the cmake build folder.")])}],!1,null,null,null);s.options.__file="INSTALL.md";t.default=s.exports}}]);