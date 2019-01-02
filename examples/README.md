# Examples

The following are examples from <https://github.com/matusnovak/finegui/blob/master/examples>.

## All Widgets

[All widgets in one window - NanoVG backend](https://github.com/matusnovak/finegui/blob/master/examples/nanovg_backend_all.cpp)

[All widgets in one window - FineGraphics backend](https://github.com/matusnovak/finegui/blob/master/examples/finegraphics_backend_all.cpp)

![gif](https://github.com/matusnovak/finegui/blob/master/examples/all-widgets.gif)

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/finegraphics_backend_all_1.png)

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/finegraphics_backend_all_2.png)

## Align

[Different ways of aligning widgets - FineGraphics backend](https://github.com/matusnovak/finegui/blob/master/examples/finegraphics_backend_align.cpp)

![gif](https://github.com/matusnovak/finegui/blob/master/examples/align.gif)

# More examples by widgets

## Button

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();
    
auto button = new ffw::GuiButton(&gui, "Button");
button->setLabel("Button #1"); // Overwrites "Button"
button->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));
button->addEventCallback([](ffw::GuiEvent e) {
    std::cout << "Clicked!" << std::endl;
}, ffw::GuiEventType::ACTION);

root->addWidget(button);
// Do not free the created widgets!
// They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_button.png)

## Button Toggle

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();
    
auto button = new ffw::GuiButtonToggle(&gui, "Button");
button->setLabel("Button #1"); // Overwrites "Button"
button->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));
button->addEventCallback([](ffw::GuiEvent e) {
    std::cout << "Clicked! Status: " << e.data.action.value << std::endl;
}, ffw::GuiEventType::ACTION);
auto isPressed = button->getValue(); // Programatically get on/off state
button->setValue(true); // Programatically set on/off state

root->addWidget(button);
// Do not free the created widgets!
// They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_button.png)

## Checkbox

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg); 
auto root = gui.getLayout();

auto checkbox = new ffw::GuiCheckbox(&gui, "I am a checkbox");
checkbox->setLabel("I am a new label");
checkbox->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));
checkbox->addEventCallback([](ffw::GuiEvent e) {
    std::cout << "Clicked! Status: " << e.data.action.value << std::endl;
}, ffw::GuiEventType::ACTION);
auto isPressed = checkbox->getValue(); // Programatically get on/off state
checkbox->setValue(true); // Programatically set on/off state

root->addWidget(checkbox);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_checkbox.png)

## Image Viewer

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg); 
auto root = gui.getLayout();

// Load pixels
std::unique_ptr<unsigned char[]> pixels(new unsigned char[360 * 240 * 4]);
std::ifstream input("owl.raw", std::ios::in | std::ios::binary);
input.read((char*)pixels.get(), 360 * 240 * 4);

// Create image
// Make sure the image is alive while the window is being rendered!
// Depending on your backend implementation, you can free the pixels
// after creating the image! When using NanoVG or FineGraphics
// the pixels are copied into the GPU memory.
auto image = ffw::GuiImageNanoVG(nvg, 360, 240, 0, pixels.get());
pixels.reset();

auto viewer = new ffw::GuiImageViewer(&gui, &image);
viewer->setSize(ffw::guiPercent(50.0f), ffw::guiWrap());
viewer->setLabel("Hello World!");
viewer->setAlign(ffw::GuiAlign::TOP_LEFT);

root->addWidget(label);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_image.png)

## Label

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

auto label = new ffw::GuiLabel(&gui, "Hello World");
label->setLabel("Hello World!"); // Overwrite label
label->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));

root->addWidget(label);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_label.png)

## Layout

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();
     
// Create two columns with 47.5% width each and 5% margin between...
auto left = new ffw::GuiLayout(&gui, ffw::GuiOrientation::VERTICAL);
left->setSize(ffw::guiPercent(47.5f), ffw::guiPercent(100.0));
left->setMarginRight(ffw::guiPercent(2.5f)); // 2.5% margin on right

auto right = new ffw::GuiLayout(&gui, ffw::GuiOrientation::VERTICAL);
right->setSize(ffw::guiPercent(47.5f), ffw::guiPercent(100.0));
right->setMarginLeft(ffw::guiPercent(2.5f)); // 2.5% margin on left

auto button1 = new ffw::GuiButton(&gui, "I am on the left!");
left->addWidget(button1);
auto button2 = new ffw::GuiButton(&gui, "I am on the right!");
right->addWidget(button2);

root->setOrientation(ffw::GuiOrientation::HORIZONTAL);
root->addWidget(left);
root->addWidget(right);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_layout.png)

## List

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

auto list = new ffw::GuiList(&gui);
list->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));
ffw::GuiList::Item* second = nullptr;
for (auto i = 0; i < 30; i++) {
    const auto item = list->addItem("List Item number #" + std::to_string(i));
    if (i == 1) second = item;

    item->addEventCallback([=](ffw::GuiEvent e) {
        std::cout << "callback from item index: " << i << std::endl;
    }, ffw::GuiEventType::ACTION);
}
list->setSelected(second);
list->addEventCallback([=](ffw::GuiEvent e) {
    std::cout << "callback from list index: " << e.data.action.value << std::endl;
}, ffw::GuiEventType::ACTION);

root->addWidget(list);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_list.png)


## Progress Bar

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

auto progress = new ffw::GuiProgressBar(&gui);
progress->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));
progress->setValue(75.0f);
auto percent = progress->getValue(); // Programatically get value

root->addWidget(progress);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_progressbar.png)

## Progress Circle

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

auto progress = new ffw::GuiProgressCircle(&gui);
progress->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(100.0f));
progress->setValue(75.0f);
auto percent = progress->getValue(); // Programatically get value

root->addWidget(progress);

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_progresscircle.png)

## Radio

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

// Create three radios that will belong to the same group.
// To group radios, simply add first of the group member as
// the 4th parameter. The base value is the 3rd parameter.
// This is similar as in HTML: <input type="radio" value="100" .../>
auto radio1 = new ffw::GuiRadio(&gui, "Radio #1", 100);
auto radio2 = new ffw::GuiRadio(&gui, "Radio #2", 200, radio1);
auto radio3 = new ffw::GuiRadio(&gui, "Radio #3", 300, radio1);

radio1->addEventCallback([](ffw::GuiEvent e) {
    // The "e.data.action.value" will be
    // the base value, either 100, 200, or 300
    std::cout << "Radio selected value: " << e.data.action.value << std::endl;
}, ffw::GuiEventType::ACTION);

// To change which radio is set, simply call setValue()
// on any of the grouped radios. This also works on
// getting the value via getValue().
radio1->setValue(200);

root->addWidget(radio1);
root->addWidget(radio2);
root->addWidget(radio3);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_radio.png)

## Scrollable (layout)

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

// Creates a verticall layout with a scrollbar on the right.
// 3rd parameter -> bottom scrollbar
// 4th parameter -> right scrollbar
auto scrollable = new ffw::GuiScrollableLayout(&gui, ffw::GuiOrientation::VERTICAL, false, true);
scrollable->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));

// Get the inner widget that will be scrolled.
// In this case it's the layout.
auto layout = scrollable->getInner();

const auto goDown = new ffw::GuiButton(&gui, "Click to scroll to 50%");
goDown->addEventCallback([=](ffw::GuiEvent e) {
    // Returns the maximum scroll values.
    // Note that the returned type is ffw::Pointf and the x 
    // component (minimum scrollbar range) is always going to be zero!
    // The y component (maximum scroll range) is what you need.
    const auto max = scrollable->getVscroll()->getRange();

    // Scroll down 50%
    // This only works after gui.update() has been called
    // at least once! The update() function will update 
    // the scrollbars.
    // Therefore we are putting this in a button callback.
    scrollable->getVscroll()->setValue(max.y / 2.0f);
}, ffw::GuiEventType::ACTION);

layout->addWidget(goDown);

for (auto i = 0; i < 32; i++) {
    const auto button = new ffw::GuiButton(&gui, "Button #" + std::to_string(i));
    layout->addWidget(button);
}

root->addWidget(scrollable);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_scrollablelayout.png)

## Scrollbar

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

// To make it vertical, change the second parameter to true
auto scrollbar = new ffw::GuiScrollBar(&gui, false);
scrollbar->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(30.0f));
scrollbar->setRange(50.0f, 100.0f);
scrollbar->setIncrements(5.0f); // Affects the left and right buttons
scrollbar->setValue(75.0f); // The scroll button will be in the middle
auto value = scrollbar->getValue(); // Returns 75.0f
scrollbar->addEventCallback([](ffw::GuiEvent e) {
    // The value is between the 50.0 and 100.0 range
    std::cout << "Value changed: " << e.data.action.value << std::endl;
}, ffw::GuiEventType::ACTION);

root->addWidget(scrollbar);
// Do not free the created widgets!
// They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_scrollbar.png)

## Slider

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

// To make it vertical, change the second parameter to true
auto slider = new ffw::GuiSlider(&gui, false);
slider->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(30.0f));
slider->setRange(50.0f, 100.0f);
slider->setValue(75.0f); // The scroll button will be in the middle
auto value = slider->getValue(); // Returns 75.0f
slider->addEventCallback([](ffw::GuiEvent e) {
    // The value is between the 50.0 and 100.0 range
    std::cout << "Value changed: " << e.data.action.value << std::endl;
}, ffw::GuiEventType::ACTION);

root->addWidget(slider);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_slider.png)

## Switch

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

auto button = new ffw::GuiSwitch(&gui);
button->setSize(ffw::guiPixels(50.0f), ffw::guiPixels(25.0f));
button->addEventCallback([](ffw::GuiEvent e) {
    std::cout << "Clicked! Status: " << e.data.action.value << std::endl;
}, ffw::GuiEventType::ACTION);
auto isPressed = button->getValue(); // Programatically get on/off state
button->setValue(true); // Programatically set on/off state

root->addWidget(button);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_switch.png)

## Tabs

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

auto tabs = new ffw::GuiTabs(&gui);
ffw::GuiVerticalLayout* last = nullptr;
for (auto i = 1; i <= 3; i++) {
    auto layout = new ffw::GuiVerticalLayout(&gui);
    auto button = new ffw::GuiButton(&gui, "Button in Tab #" + std::to_string(i));
    layout->addWidget(button);
    auto tab = tabs->addTab("Tab #" + std::to_string(i), layout);
    tab->setSize(ffw::guiPercent(33.33f), tab->getSize().y);
    if (i == 3) last = layout;
}
tabs->showTabByWidget(last);

root->addWidget(tabs);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_tabs.png)

## Text

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

// Make sure these three instances of font
// are alive while the GUI is rendering!
// If you free these fonts before gui.update() or
// gui.render() it will cause the program to crash!
auto fontRegular = ffw::GuiFontFineGraphics(canvas, "FreeSans.ttf", 16.0f))
auto fontBold = ffw::GuiFontFineGraphics(canvas, "FreeSansBold.ttf", 32.0f);
auto fontItalic = ffw::GuiFontFineGraphics(canvas, "FreeSansOblique.ttf", 16.0f);

auto text = new ffw::GuiText(&gui);
text->addParagraph("Title", ffw::rgb(10, 10, 10), fontBold.get());
text->addParagraph("Lorem Ipsum Donor");
text->addParagraph("Italic text", ffw::rgb(10, 90, 180), fontItalic.get());

root->addWidget(text);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_text.png)

## Text Input (single line)

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

auto input = new ffw::GuiTextInput(&gui, false);
input->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));
input->setValue("Lorem Ipsum");
auto text = input->getValue(); // Returns "Lorem Ipsum"

root->addWidget(text);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_textinput_singleline.png)

## Text Input (multi line)

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

auto input = new ffw::GuiTextInput(&gui, true);
input->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(100.0f));
input->setValue("Lorem ipsum dolor sit amet\nconsectetur adipiscing elit.");
auto text = input->getValue(); // Returns the string above

root->addWidget(text);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_textinput_multiline.png)

## Text Input (multi line with scroll)

```cpp
auto gui = ffw::GuiWindowNanoVG(nvg);
auto root = gui.getLayout();

auto input = new ffw::GuiScrollableTextInput(&gui);
input->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(100.0f));
input->setValue("Lorem ipsum dolor sit amet....");
auto text = input->getValue(); // Returns the string above

root->addWidget(text);
// Do not free the created widgets! They will be deleted by the gui window!

while(true){
    // Render the gui
}
```

![screenshot](https://github.com/matusnovak/finegui/blob/master/examples/widgets_textinput_scroll.png)
