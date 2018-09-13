/*** This file is part of FineFramework project ***/
#ifndef FFW_GUI_CONFIG
#define FFW_GUI_CONFIG

// Using Visual Studio
#ifdef _MSC_VER
#define FFW_WINDOWS_MSVC 1
#define FFW_WINDOWS 1
#pragma warning( disable: 4251 )
#endif

// Using MinGW
#ifdef __MINGW32__
#define FFW_WINDOWS_MINGW 1
#define FFW_WINDOWS 1
#endif

// Using Linux GCC
#ifdef __linux__
#define FFW_LINUX_GCC 1
#define FFW_LINUX 1
#endif

// Using MAX OS X
#if defined(__APPLE__) && defined(__MACH__)
#define FFW_OSX_CLANG 1
#define FFW_OSX 1
#endif

#if !defined(FFW_WINDOWS_MSVC) && !defined(FFW_WINDOWS_MINGW) && !defined(FFW_LINUX_GCC) && !defined(FFW_OSX_CLANG)
#error Please use Visual Studio, MinGW, Linux GCC, or OS X Clang to compile FineFramework!
#endif
#if !defined(FFW_WINDOWS) && !defined(FFW_LINUX) && !defined(FFW_OSX)
#error Target platform not selected!
#endif

// FineFramework export for Windows
#if defined(FFW_WINDOWS)
#ifdef FFW_EXPORTS
#define FFW_API __declspec(dllexport)
#else
#define FFW_API __declspec(dllimport)
#endif
#else
#define FFW_API
#endif

#if !defined(FFW_API)
#error FFW_API dllexport not defined!
#endif

#if !defined(HAS_NOEXCEPT)
#if defined(__clang__)
#if __has_feature(cxx_noexcept)
#define HAS_NOEXCEPT
#endif
#else
#if defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46 || defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190023026
#define HAS_NOEXCEPT
#endif
#endif

#ifdef HAS_NOEXCEPT
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif
#endif

#endif
