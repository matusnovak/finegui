(window.webpackJsonp=window.webpackJsonp||[]).push([[121],{380:function(e,r,t){"use strict";t.r(r);var s=t(0),a=Object(s.a)({},function(){var e=this.$createElement,r=this._self._c||e;return r("div",{staticClass:"content"},[this._m(0),this._v(" "),r("p",[r("strong",[r("router-link",{attrs:{to:"./config_8h.html"}},[this._v("Go to the documentation of this file.")])],1),this._v("\nSource: "),r("code",[this._v("include/ffw/gui/config.h")])]),this._v(" "),this._m(1)])},[function(){var e=this.$createElement,r=this._self._c||e;return r("h1",{attrs:{id:"config-h-file-reference"}},[r("a",{staticClass:"header-anchor",attrs:{href:"#config-h-file-reference","aria-hidden":"true"}},[this._v("#")]),this._v(" config.h File Reference")])},function(){var e=this,r=e.$createElement,t=e._self._c||r;return t("div",{staticClass:"language-cpp extra-class"},[t("pre",{pre:!0,attrs:{class:"language-cpp"}},[t("code",[t("span",{pre:!0,attrs:{class:"token comment"}},[e._v("/*** This file is part of FineFramework project ***/")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("ifndef")]),e._v(" FFW_GUI_CONFIG")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_GUI_CONFIG")]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token comment"}},[e._v("// Using Visual Studio")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("ifdef")]),e._v(" _MSC_VER")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_WINDOWS_MSVC 1")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_WINDOWS 1")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("pragma")]),e._v(" warning( disable: 4251 )")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token comment"}},[e._v("// Using MinGW")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("ifdef")]),e._v(" __MINGW32__")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_WINDOWS_MINGW 1")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_WINDOWS 1")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token comment"}},[e._v("// Using Linux GCC")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("ifdef")]),e._v(" __linux__")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_LINUX_GCC 1")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_LINUX 1")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token comment"}},[e._v("// Using MAX OS X")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("if")]),e._v(" defined(__APPLE__) && defined(__MACH__)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_OSX_CLANG 1")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_OSX 1")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("if")]),e._v(" !defined(FFW_WINDOWS_MSVC) && !defined(FFW_WINDOWS_MINGW) && !defined(FFW_LINUX_GCC) && !defined(FFW_OSX_CLANG)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("error")]),e._v(" Please use Visual Studio, MinGW, Linux GCC, or OS X Clang to compile FineFramework!")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("if")]),e._v(" !defined(FFW_WINDOWS) && !defined(FFW_LINUX) && !defined(FFW_OSX)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("error")]),e._v(" Target platform not selected!")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token comment"}},[e._v("// FineFramework export for Windows")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("if")]),e._v(" defined(FFW_WINDOWS)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("ifdef")]),e._v(" FFW_EXPORTS")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_API __declspec(dllexport)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("else")])]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_API __declspec(dllimport)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("else")])]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" FFW_API")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("if")]),e._v(" !defined(FFW_API)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("error")]),e._v(" FFW_API dllexport not defined!")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("if")]),e._v(" !defined(HAS_NOEXCEPT)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("if")]),e._v(" defined(__clang__)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("if")]),e._v(" __has_feature(cxx_noexcept)")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" HAS_NOEXCEPT")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("else")])]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("if")]),e._v(" defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46 || defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190023026")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" HAS_NOEXCEPT")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("ifdef")]),e._v(" HAS_NOEXCEPT")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" NOEXCEPT noexcept")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("else")])]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("define")]),e._v(" NOEXCEPT")]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n\n"),t("span",{pre:!0,attrs:{class:"token macro property"}},[e._v("#"),t("span",{pre:!0,attrs:{class:"token directive keyword"}},[e._v("endif")])]),e._v("\n")])])])}],!1,null,null,null);a.options.__file="config_8h_source.md";r.default=a.exports}}]);