# FineGui

|         | CircleCI | TravisCI | AppVeyor |
|---------|----------|----------|----------|
| master  | [![CircleCI](https://circleci.com/gh/matusnovak/finegui/tree/master.svg?style=svg)](https://circleci.com/gh/matusnovak/finegui/tree/master) | [![Build Status](https://travis-ci.org/matusnovak/finegui.svg?branch=master)](https://travis-ci.org/matusnovak/finegui) | [![Build status](https://ci.appveyor.com/api/projects/status/7ptts9y3grin6jqs/branch/master?svg=true)](https://ci.appveyor.com/project/matusnovak/finegui/branch/master) |
| devel  | [![CircleCI](https://circleci.com/gh/matusnovak/finegui/tree/devel.svg?style=svg)](https://circleci.com/gh/matusnovak/finegui/tree/devel) | [![Build Status](https://travis-ci.org/matusnovak/finegui.svg?branch=devel)](https://travis-ci.org/matusnovak/finegui) | [![Build status](https://ci.appveyor.com/api/projects/status/7ptts9y3grin6jqs/branch/devel?svg=true)](https://ci.appveyor.com/project/matusnovak/finegui/branch/devel) |

*The following compilers are tested in the CI above: Visual Studio 2013, Visual Studio 2013 Win64, Visual Studio 2015, Visual Studio 2015 Win64, Visual Studio 2017, Visual Studio 2017 Win64, MinGW-w64 i686, MinGW-w64 x86_64, Linux GCC 5.5.0, Linux GCC 6.4.0, Linux GCC 5.5.0, Linux GCC 7.3.0, and OSX Clang 3.7*

## Introduction 

![gif](https://github.com/matusnovak/finegui/blob/master/examples/align.gif)

The FineGui is a standalone library that provides a simple utf8 enabled graphical user interface with a linear layout system similar to Android GUI development. The rendering and updating logic behind this library is done as a framebuffer. For example, when looping inside your render function, the gui window will not render each frame, instead it will update and render only when necessary (user clicks on a button -> change color). The library also offers experimental XML parser that generates GUI structure for you. This library is not meant to be the best GUI library in the world. Instead, it offers a simple backend API that can be integrated into any renderer you want. The purpose of this abstract backend is to enable embeding this library into IoT devices that, for example, do not use hardware acceleration. The backend would be your custom CPU based renderer that writes pixels directly into, for example, an LCD. However, there is FineGraphics and NanoVG backends included. See the example folder for more.

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

## Code example

![screenshot](https://github.com/matusnovak/finegui/blob/master/screenshot.png)

Looking for more examples? Try the [examples folder](examples/README.md).

```cpp
// This defines the theme of the entire window.
// You can modify (or copy) the theme as you want.
// You can also apply a specific theme for any of the 
// widgets by calling widget->setTheme(&customTheme);
// Or by widget->setStyle(&customStyle);
ffw::GuiThemeSimpleLight theme;

// This is a GUI window, you can create many of them,
// they are independent! We are using NanoVG as an example,
// but creating your own backend is very easy!
auto gui = ffw::GuiWindowNanoVG(nvg);

// Creating a font is backend specific, we will use FreeSans.ttf
auto font = ffw::GuiFontNanoVG(nvg, "FreeSans.ttf", 16.0f);

// Default parameters
gui.setTheme(&theme);
gui.setPos(0, 0);
gui.setDefaultFont(&font);

// Each window comes with it's own ffw::GuiBody
// Think of it as <body></body> in html.
auto root = gui.getLayout();

// Warping enables that if there is not enough space
// to fit the widgets horizontally, it will be moved
// to the next row.
// When using verticall layout, widgets will be moved
// to the right (imagine columns).
root->setWrap(true);

// Create two columns with 47.5% width each and 5% margin between...
auto left = new ffw::GuiLayout(&gui, ffw::GuiOrientation::VERTICAL);
left->setSize(ffw::guiPercent(47.5f), ffw::guiPercent(50.0f));
left->setMarginRight(ffw::guiPercent(2.5f)); // 2.5% margin on right

auto right = new ffw::GuiLayout(&gui, ffw::GuiOrientation::VERTICAL);
right->setSize(ffw::guiPercent(47.5f), ffw::guiPercent(50.0f));
right->setMarginLeft(ffw::guiPercent(2.5f)); // 2.5% margin on left

auto bottom = new ffw::GuiHorizontalLayout(&gui);
bottom->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(45.0f));
bottom->setMarginTop(ffw::guiPercent(5.0f));
bottom->setAlign(ffw::GuiAlign::CENTER);
bottom->setWrap(true);

// Start of left column
auto label1 = new ffw::GuiLabel(&gui, "Left column 50% width:");
left->addWidget(label1);

auto button1 = new ffw::GuiButton(&gui, "I am on the left!");
button1->addEventCallback([](const ffw::GuiEvent e) {
    const auto btn = dynamic_cast<const ffw::GuiButton*>(e.widget);
    std::cout << "Button with label: " << btn->getLabel() << " clicked!" << std::endl;
}, ffw::GuiEventType::ACTION);
left->addWidget(button1);

auto checkbox1 = new ffw::GuiCheckbox(&gui, "Hello World");
checkbox1->setValue(true);
left->addWidget(checkbox1);

auto radio1 = new ffw::GuiRadio(&gui, "Radio A", 100);
auto radio2 = new ffw::GuiRadio(&gui, "Radio A", 200, radio1);
auto radio3 = new ffw::GuiRadio(&gui, "Radio A", 300, radio1);
radio1->setValue(300);
left->addWidget(radio1);
left->addWidget(radio2);
left->addWidget(radio3);

// Start of right column
auto label2 = new ffw::GuiLabel(&gui, "Right column 50% width:");
right->addWidget(label2);

auto button2 = new ffw::GuiButton(&gui, "I am on the right!");
right->addWidget(button2);

auto input = new ffw::GuiScrollableTextInput(&gui);
input->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(100.0f));
input->setValue(
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit"
    "\n"
    "\n"
    "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
);
right->addWidget(input);

// Start of bottom column
auto label3 = new ffw::GuiLabel(&gui, "Another column 100% width with align \"CENTER\"");
label3->setSize(ffw::guiWrap(), ffw::guiWrap());
bottom->addWidget(label3);

for (auto i = 0; i < 3; i++) {
    auto button = new ffw::GuiButtonToggle(&gui, "Button #" + std::to_string(i));
    button->setSize(ffw::guiPercent(30.0f), ffw::guiWrap());
    if (i != 2) button->setMarginRight(ffw::guiPercent(5.0f));
    bottom->addWidget(button);
}

// Add everything together
root->setOrientation(ffw::GuiOrientation::HORIZONTAL);
root->addWidget(left);
root->addWidget(right);
root->addWidget(bottom);

// We do not DELETE ANY widgets! The lifetime of
// widgets is handled by the window and parent widgets.

while (true) {
    // Rendering loop
    gui->update();
    gui->poolEvents();
    gui->render();

    // Render the framebuffer from the GuiWindow.
    // This example uses NanoVG, or you can use your own backend.
    nvgBeginFrame(nvg, viewport.x, viewport.y, 1.0f);
    const auto img = nvgImagePattern(nvg, 0, 0, viewport.x, viewport.y, 0, /* ---> */ gui.getFbo()->image, 1.0f);
    nvgBeginPath(nvg);
    nvgRect(nvg, 0.0f, 0.0f, viewport.x, viewport.y);
    nvgFillPaint(nvg, img);
    nvgFill(nvg);
    nvgEndFrame(nvg);
}

// No manual cleanup necessary!
// All widgets will be freed once the ffw::GuiWindow 
// falls out of the scope.
```

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