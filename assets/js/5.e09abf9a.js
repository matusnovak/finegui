(window.webpackJsonp=window.webpackJsonp||[]).push([[5],{201:function(e,t,i){"use strict";i.r(t);var r=i(0),n=Object(r.a)({},function(){var e=this,t=e.$createElement,i=e._self._c||t;return i("div",{staticClass:"content"},[e._m(0),e._v(" "),i("table",[e._m(1),e._v(" "),i("tbody",[i("tr",[i("td",[e._v("master")]),e._v(" "),i("td",[i("a",{attrs:{href:"https://circleci.com/gh/matusnovak/finegui/tree/master",target:"_blank",rel:"noopener noreferrer"}},[i("img",{attrs:{src:"https://circleci.com/gh/matusnovak/finegui/tree/master.svg?style=svg",alt:"CircleCI"}}),i("OutboundLink")],1)]),e._v(" "),i("td",[i("a",{attrs:{href:"https://travis-ci.org/matusnovak/finegui",target:"_blank",rel:"noopener noreferrer"}},[i("img",{attrs:{src:"https://travis-ci.org/matusnovak/finegui.svg?branch=master",alt:"Build Status"}}),i("OutboundLink")],1)]),e._v(" "),i("td",[i("a",{attrs:{href:"https://ci.appveyor.com/project/matusnovak/finegui/branch/master",target:"_blank",rel:"noopener noreferrer"}},[i("img",{attrs:{src:"https://ci.appveyor.com/api/projects/status/7ptts9y3grin6jqs/branch/master?svg=true",alt:"Build status"}}),i("OutboundLink")],1)])]),e._v(" "),i("tr",[i("td",[e._v("devel")]),e._v(" "),i("td",[i("a",{attrs:{href:"https://circleci.com/gh/matusnovak/finegui/tree/devel",target:"_blank",rel:"noopener noreferrer"}},[i("img",{attrs:{src:"https://circleci.com/gh/matusnovak/finegui/tree/devel.svg?style=svg",alt:"CircleCI"}}),i("OutboundLink")],1)]),e._v(" "),i("td",[i("a",{attrs:{href:"https://travis-ci.org/matusnovak/finegui",target:"_blank",rel:"noopener noreferrer"}},[i("img",{attrs:{src:"https://travis-ci.org/matusnovak/finegui.svg?branch=devel",alt:"Build Status"}}),i("OutboundLink")],1)]),e._v(" "),i("td",[i("a",{attrs:{href:"https://ci.appveyor.com/project/matusnovak/finegui/branch/devel",target:"_blank",rel:"noopener noreferrer"}},[i("img",{attrs:{src:"https://ci.appveyor.com/api/projects/status/7ptts9y3grin6jqs/branch/devel?svg=true",alt:"Build status"}}),i("OutboundLink")],1)])])])]),e._v(" "),e._m(2),e._v(" "),e._m(3),e._v(" "),i("p",[e._v("The FineGui is a standalone library that provides a simple utf8 enabled graphical user interface with a linear layout system similar to Android GUI development. The library also offers experimental XML parser that generates GUI structure for you. This library is not meant to be the best GUI library in the world. Instead, it offers a simple backend API that can be integrated into any renderer you want. The purpose of this abstract backend is to enable embeding this library into IoT devices that, for example, do not use hardware acceleration. The backend would be your custom CPU based renderer that writes pixels directly into, for example, an LCD. However, there is FineGraphics and NanoVG backends included. See the example folder for more.")]),e._v(" "),e._m(4),e._v(" "),i("p",[i("strong",[e._v("API Documentation is provided at "),i("a",{attrs:{href:"http://matusnovak.github.io/finegui/",target:"_blank",rel:"noopener noreferrer"}},[e._v("http://matusnovak.github.io/finegui/"),i("OutboundLink")],1)])]),e._v(" "),e._m(5),e._v(" "),i("p",[e._v("All dependencies listed here are already included as a git submodule and will be statically linked to the examples. Therefore, no need to compile them manually, nor link them manually! Everything is automated via CMake.")]),e._v(" "),i("ul",[i("li",[i("a",{attrs:{href:"https://github.com/ledger/utfcpp",target:"_blank",rel:"noopener noreferrer"}},[e._v("utfcpp"),i("OutboundLink")],1),e._v(" - For handling utf8 strings (header only library)")]),e._v(" "),i("li",[i("a",{attrs:{href:"https://github.com/leethomason/tinyxml2.git",target:"_blank",rel:"noopener noreferrer"}},[e._v("tinyxml2"),i("OutboundLink")],1),e._v(" - For parsing XML files (included directly)")]),e._v(" "),i("li",[i("a",{attrs:{href:"https://www.freetype.org/",target:"_blank",rel:"noopener noreferrer"}},[e._v("freetype2"),i("OutboundLink")],1),e._v(" - Examples only")]),e._v(" "),i("li",[i("a",{attrs:{href:"https://www.glfw.org/",target:"_blank",rel:"noopener noreferrer"}},[e._v("glfw"),i("OutboundLink")],1),e._v(" - Examples only")]),e._v(" "),i("li",[i("a",{attrs:{href:"https://github.com/glennrp/libpng",target:"_blank",rel:"noopener noreferrer"}},[e._v("libpng"),i("OutboundLink")],1),e._v(" - Examples only")]),e._v(" "),i("li",[i("a",{attrs:{href:"https://github.com/memononen/nanovg",target:"_blank",rel:"noopener noreferrer"}},[e._v("nanovg"),i("OutboundLink")],1),e._v(" - Examples only")]),e._v(" "),i("li",[i("a",{attrs:{href:"https://github.com/syoyo/tinyobjloader.git",target:"_blank",rel:"noopener noreferrer"}},[e._v("tinyobjloader"),i("OutboundLink")],1),e._v(" - Examples only")]),e._v(" "),i("li",[i("a",{attrs:{href:"https://github.com/madler/zlib",target:"_blank",rel:"noopener noreferrer"}},[e._v("zlib"),i("OutboundLink")],1),e._v(" - Examples only")]),e._v(" "),i("li",[i("a",{attrs:{href:"https://github.com/enthought/bzip2-1.0.6",target:"_blank",rel:"noopener noreferrer"}},[e._v("bzip2"),i("OutboundLink")],1),e._v(" - Examples only")])]),e._v(" "),e._m(6),e._v(" "),e._m(7),e._v(" "),e._m(8),e._v(" "),i("p",[e._v("TODO")]),e._v(" "),e._m(9),e._v(" "),i("p",[e._v("One of the following compilers:")]),e._v(" "),e._m(10),e._v(" "),e._m(11),e._v(" "),i("p",[e._v("You can "),i("a",{attrs:{href:"https://github.com/matusnovak/finegui/releases",target:"_blank",rel:"noopener noreferrer"}},[e._v("use one of the automatically built releases from GitHub Releases"),i("OutboundLink")],1),e._v(" or compile it manually by following the "),i("router-link",{attrs:{to:"./INSTALL.html"}},[e._v("Install Guide")]),e._v(" (Don't worry, it's easy).")],1),e._v(" "),e._m(12),e._v(" "),e._m(13),e._v(" "),e._m(14),e._v(" "),e._m(15),e._v(" "),e._m(16),e._v(" "),e._m(17),e._v(" "),e._m(18),e._v(" "),i("p",[e._v("Documentation can be found at "),i("a",{attrs:{href:"http://matusnovak.github.io/finegui/",target:"_blank",rel:"noopener noreferrer"}},[e._v("http://matusnovak.github.io/finegui/"),i("OutboundLink")],1)]),e._v(" "),e._m(19),e._v(" "),i("p",[e._v("All examples are located in the "),i("router-link",{attrs:{to:"./examples/"}},[e._v("examples folder")]),e._v(".")],1),e._v(" "),e._m(20),e._v(" "),i("p",[e._v("Looking for alternative library or framework? Try OpenFrameworks, SFML, or Cinder (be warned, they are much more bigger, but feature rich).")]),e._v(" "),e._m(21),e._v(" "),i("p",[e._v("Feel free to post a question in GitHub issues. Pull requests are welcome!")]),e._v(" "),e._m(22),e._v(" "),i("p",[e._v("Feel free to contact me on my email (see my GitHub profile).")]),e._v(" "),e._m(23),e._v(" "),i("p",[i("a",{attrs:{href:"https://en.wikipedia.org/wiki/MIT_License",target:"_blank",rel:"noopener noreferrer"}},[e._v("https://en.wikipedia.org/wiki/MIT_License"),i("OutboundLink")],1)]),e._v(" "),e._m(24)])},[function(){var e=this.$createElement,t=this._self._c||e;return t("h1",{attrs:{id:"finegui"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#finegui","aria-hidden":"true"}},[this._v("#")]),this._v(" FineGui")])},function(){var e=this.$createElement,t=this._self._c||e;return t("thead",[t("tr",[t("th"),this._v(" "),t("th",[this._v("CircleCI")]),this._v(" "),t("th",[this._v("TravisCI")]),this._v(" "),t("th",[this._v("AppVeyor")])])])},function(){var e=this.$createElement,t=this._self._c||e;return t("p",[t("em",[this._v("The following compilers are tested in the CI above: Visual Studio 2013, Visual Studio 2013 Win64, Visual Studio 2015, Visual Studio 2015 Win64, Visual Studio 2017, Visual Studio 2017 Win64, MinGW-w64 i686, MinGW-w64 x86_64, Linux GCC 5.5.0, Linux GCC 6.4.0, Linux GCC 5.5.0, Linux GCC 7.3.0, and OSX Clang 3.7")])])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"introduction"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#introduction","aria-hidden":"true"}},[this._v("#")]),this._v(" Introduction")])},function(){var e=this.$createElement,t=this._self._c||e;return t("p",[this._v("This library uses only header only utfcpp library and tinyxml2, all other libraries are only needed to run the examples. The third party libraries are optional, can be disabled through cmake "),t("code",[this._v("-DBUILD_EXAMPLES:BOOL=OFF")]),this._v(" and are compiled automatically though cmake.")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"dependencies"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#dependencies","aria-hidden":"true"}},[this._v("#")]),this._v(" Dependencies")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"todo"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#todo","aria-hidden":"true"}},[this._v("#")]),this._v(" TODO")])},function(){var e=this.$createElement,t=this._self._c||e;return t("ul",[t("li",[this._v("More examples, documentation, and tutorials")]),this._v(" "),t("li",[this._v("More unit tests")]),this._v(" "),t("li",[this._v("More backends such as a simple CPU pixel renderer")])])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"quick-example"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#quick-example","aria-hidden":"true"}},[this._v("#")]),this._v(" Quick example")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"requirements"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#requirements","aria-hidden":"true"}},[this._v("#")]),this._v(" Requirements")])},function(){var e=this,t=e.$createElement,i=e._self._c||t;return i("ul",[i("li",[e._v("(Windows) Visual Studio 2013 32-bit or 64-bit")]),e._v(" "),i("li",[e._v("(Windows) Visual Studio 2015 32-bit or 64-bit")]),e._v(" "),i("li",[e._v("(Windows) Visual Studio 2017 32-bit or 64-bit")]),e._v(" "),i("li",[e._v("(Windows) MinGW-w64 i686")]),e._v(" "),i("li",[e._v("(Windows) MinGW-w64 x86_64")]),e._v(" "),i("li",[e._v("(Linux) GCC 4.9 or newer")]),e._v(" "),i("li",[e._v("(OSX) Clang 3.7 or newer")])])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"compiling-finegui"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#compiling-finegui","aria-hidden":"true"}},[this._v("#")]),this._v(" Compiling FineGui")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"using-finegui"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#using-finegui","aria-hidden":"true"}},[this._v("#")]),this._v(" Using FineGui")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h3",{attrs:{id:"windows"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#windows","aria-hidden":"true"}},[this._v("#")]),this._v(" Windows")])},function(){var e=this,t=e.$createElement,i=e._self._c||t;return i("p",[e._v("First, compile the library (see section above), next to use the finegui in your project, simply include the "),i("code",[e._v("C:/path/to/finegui/include")]),e._v(" and link the "),i("code",[e._v("finegui.lib")]),e._v(". You will also need the "),i("code",[e._v("finegui.dll")]),e._v(" in order to run the application. Simply copy the DLL into the executable folder. You can find the "),i("code",[e._v(".lib")]),e._v(" and "),i("code",[e._v(".dll")]),e._v(" files in the cmake build folder.")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h3",{attrs:{id:"linux-osx"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#linux-osx","aria-hidden":"true"}},[this._v("#")]),this._v(" Linux/OSX")])},function(){var e=this,t=e.$createElement,i=e._self._c||t;return i("p",[e._v("First, compile the library (see section above), next to use the finegui in your project, simply include the "),i("code",[e._v("~/finegui/include")]),e._v(" (or "),i("code",[e._v("/usr/local/include")]),e._v(" if you have installed it) and link the "),i("code",[e._v("finegui.so")]),e._v(". You can find the "),i("code",[e._v(".so")]),e._v(" files in the cmake build folder (or at the installed path provided by CMAKE_INSTALL_PREFIX).")])},function(){var e=this.$createElement,t=this._self._c||e;return t("p",[this._v("If you are planning to distribute your application with FineGui, you will need to copy the "),t("code",[this._v("finegui.so")]),this._v(" and include it within your application. For example, the most simple way, copy it into the executable folder (same as in Windows).")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"documentation"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#documentation","aria-hidden":"true"}},[this._v("#")]),this._v(" Documentation")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"examples"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#examples","aria-hidden":"true"}},[this._v("#")]),this._v(" Examples")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"alternatives"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#alternatives","aria-hidden":"true"}},[this._v("#")]),this._v(" Alternatives")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"contributing"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#contributing","aria-hidden":"true"}},[this._v("#")]),this._v(" Contributing")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"contact"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#contact","aria-hidden":"true"}},[this._v("#")]),this._v(" Contact")])},function(){var e=this.$createElement,t=this._self._c||e;return t("h2",{attrs:{id:"license"}},[t("a",{staticClass:"header-anchor",attrs:{href:"#license","aria-hidden":"true"}},[this._v("#")]),this._v(" License")])},function(){var e=this.$createElement,t=this._self._c||e;return t("div",{staticClass:"language- extra-class"},[t("pre",{pre:!0,attrs:{class:"language-text"}},[t("code",[this._v('The MIT License (MIT)\n\nCopyright (c) 2018 Matus Novak\n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files (the "Software"), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.\n')])])])}],!1,null,null,null);n.options.__file="README.md";t.default=n.exports}}]);