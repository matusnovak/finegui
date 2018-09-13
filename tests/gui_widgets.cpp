#include <ffw/gui.h>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "nullrenderer.h"
#include <list>

#define CLICK_AND_UPDATE \
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED); \
    TEST_UPDATE_AND_RENDER; \
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED); \
    TEST_UPDATE_AND_RENDER;

class EventCallbackListener {
public:
    void addWidget(ffw::GuiWidget* widget) {
        widget->addEventCallback([=](ffw::GuiEvent e) -> void {
            events.push_back(e);
        }, ffw::GuiEventType::ALL);
    }

    void clear() {
        events.clear();
    }

    int count(ffw::GuiEventType type, ffw::GuiWidget* widget) {
        int total = 0;
        for(const auto& e : events) {
            if(e.type == type && e.widget == widget) {
                total++;
            }
        }
        return total;
    }

    const ffw::GuiEvent::Data* getLast(ffw::GuiEventType type, ffw::GuiWidget* widget) {
        const ffw::GuiEvent::Data* ptr = nullptr;
        for(const auto& e : events) {
            if(e.type == type && e.widget == widget) {
                ptr = &e.data;
            }
        }
        return ptr;
    }

    std::list<ffw::GuiEvent> events;
};

///=============================================================================
TEST_CASE("Gui Button") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto button = new ffw::GuiButton(&gui, "Hello World");
    button->setSize(ffw::guiPercent(100), ffw::guiWrap());
    body->addWidget(button);
    listener.addWidget(button);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->getRealSize() == ffw::Pointf(100.0f, 12.0f));
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == false);

    gui.injectMousePos(50.0f, 6.0f);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == true);
    REQUIRE(listener.count(ffw::GuiEventType::HOVER, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::HOVER, button)->hover.gained == true);
    listener.clear();

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == true);
    listener.clear();

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == false);
    listener.clear();
}


///=============================================================================
TEST_CASE("Gui Button Toggle") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto button = new ffw::GuiButtonToggle(&gui, "Hello World");
    button->setSize(ffw::guiPercent(100), ffw::guiWrap());
    body->addWidget(button);
    listener.addWidget(button);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->getRealSize() == ffw::Pointf(100.0f, 12.0f));
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == false);

    // Hover over the button
    gui.injectMousePos(50.0f, 6.0f);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == false);
    REQUIRE(listener.count(ffw::GuiEventType::HOVER, button) == 1);
    listener.clear();

    // Press
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    listener.clear();

    // Release
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 0);
    listener.clear();

    // Move away and click
    gui.injectMousePos(150.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;

    // Toggle button must not lose its focus
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 0);
    listener.clear();

    // Move back and click
    gui.injectMousePos(50.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 0);
    listener.clear();

    button->setValue(true);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == true);
    listener.clear();
}

///=============================================================================
TEST_CASE("Gui Checkbox") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto button = new ffw::GuiCheckbox(&gui, "Hello World");
    button->setSize(ffw::guiPercent(100), ffw::guiWrap());
    body->addWidget(button);
    listener.addWidget(button);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->getRealSize() == ffw::Pointf(100.0f, 16.0f));
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == false);

    // Hover over the checkbox label
    gui.injectMousePos(50.0f, 8.0f);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == false);
    listener.clear();

    // Hover over the checkbox button
    gui.injectMousePos(8.0f, 8.0f);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == false);
    listener.clear();

    // Click the checkbox
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    listener.clear();

    // Click again to uncheck
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == false);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 0);
    listener.clear();

    // Click again to check and then move away mouse
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMousePos(8.0f, 50.0f); // Move mouse
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    listener.clear();

    button->setValue(false);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == false);
    listener.clear();

    button->setValue(true);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == true);
    listener.clear();

    button->setFocus(false);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == false);
    listener.clear();

    button->setFocus(true);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == true);
    listener.clear();
}

///=============================================================================
TEST_CASE("Gui Label") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto label = new ffw::GuiLabel(&gui, "Hello World");
    label->setSize(ffw::guiPercent(100), ffw::guiWrap());
    body->addWidget(label);
    listener.addWidget(label);

    REQUIRE(label->getLabel() == "Hello World");

    TEST_UPDATE_AND_RENDER;
    REQUIRE(label->getRealSize() == ffw::Pointf(100.0f, 12.0f));
    REQUIRE(label->hasFocus() == false);
    REQUIRE(label->hasHover() == false);
    REQUIRE(gui.renderCounter() == 2);
    gui.clearCounter();

    // Hover or click is enabled but must not trigger a redraw
    gui.injectMousePos(50.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(label->hasFocus() == false);
    REQUIRE(label->hasHover() == true);
    REQUIRE(gui.renderCounter() == 0);
    gui.clearCounter();

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(label->hasFocus() == true);
    REQUIRE(label->hasHover() == true);
    REQUIRE(gui.renderCounter() == 0);
    gui.clearCounter();
}

///=============================================================================
TEST_CASE("Gui List") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto list = new ffw::GuiList(&gui);
    list->setSize(ffw::guiPercent(100), ffw::guiWrap());
    auto itemOne = list->addItem("One");
    auto itemTwo = list->addItem("Two");
    auto itemThree = list->addItem("Three");
    body->addWidget(list);
    listener.addWidget(list);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(itemOne->getRealSize() == ffw::Pointf(86.0f, 12.0f));
    REQUIRE(itemTwo->getRealSize() == ffw::Pointf(86.0f, 12.0f));
    REQUIRE(itemThree->getRealSize() == ffw::Pointf(86.0f, 12.0f));

    REQUIRE(list->getInner()->getRealSize() == ffw::Pointf(86.0f, 36.0f));

    REQUIRE(list->getRealSize() == ffw::Pointf(100.0f, 36.0f));
    REQUIRE(list->hasFocus() == false);
    REQUIRE(list->hasHover() == false);
    //REQUIRE(gui.renderCounter() == 10);
    gui.clearCounter();

    REQUIRE(list->getSelectedItem() == NULL);
    REQUIRE(list->getSelectedIndex() == -1);

    // Hover over first item
    gui.injectMousePos(50.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(itemOne->hasHover() == true);
    REQUIRE(itemOne->hasFocus() == false);
    REQUIRE(list->getSelectedItem() == NULL);
    REQUIRE(list->getSelectedIndex() == -1);

    // Click on the item
    CLICK_AND_UPDATE;
    REQUIRE(itemOne->hasHover() == true);
    REQUIRE(itemOne->hasFocus() == true);
    REQUIRE(list->getSelectedItem() == itemOne);
    REQUIRE(list->getSelectedIndex() == 0);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, list) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, list) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, list)->action.value == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, list)->focus.gained == true);
    listener.clear();

    // Hover over second item
    gui.injectMousePos(50.0f, 18.0f);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(itemOne->hasHover() == false);
    REQUIRE(itemOne->hasFocus() == true);
    REQUIRE(itemTwo->hasHover() == true);
    REQUIRE(itemTwo->hasFocus() == false);
    REQUIRE(list->getSelectedItem() == itemOne);
    REQUIRE(list->getSelectedIndex() == 0);

    // Click on the item
    CLICK_AND_UPDATE;
    REQUIRE(itemTwo->hasHover() == true);
    REQUIRE(itemTwo->hasFocus() == true);
    REQUIRE(list->getSelectedItem() == itemTwo);
    REQUIRE(list->getSelectedIndex() == 1);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, list) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, list) == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, list)->action.value == 1);
    listener.clear();

    // Hover over third item
    gui.injectMousePos(50.0f, 30.0f);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(itemTwo->hasHover() == false);
    REQUIRE(itemTwo->hasFocus() == true);
    REQUIRE(itemThree->hasHover() == true);
    REQUIRE(itemThree->hasFocus() == false);
    REQUIRE(list->getSelectedItem() == itemTwo);
    REQUIRE(list->getSelectedIndex() == 1);

    // Click on the item
    CLICK_AND_UPDATE;
    REQUIRE(itemThree->hasHover() == true);
    REQUIRE(itemThree->hasFocus() == true);
    REQUIRE(list->getSelectedItem() == itemThree);
    REQUIRE(list->getSelectedIndex() == 2);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, list) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, list) == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, list)->action.value == 2);
    listener.clear();

    // Reset selection
    list->resetSelected();
    TEST_UPDATE_AND_RENDER;

    REQUIRE(itemThree->hasHover() == true);
    REQUIRE(itemThree->hasFocus() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, list) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, list) == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, list)->action.value == -1);
    listener.clear();

    // Manually select item via index
    list->setSelectedIndex(1);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(itemTwo->hasHover() == false);
    REQUIRE(itemTwo->hasFocus() == true);
    REQUIRE(itemThree->hasHover() == true);
    REQUIRE(itemThree->hasFocus() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, list) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, list) == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, list)->action.value == 1);
    listener.clear();

    // Manually select item via pointer
    list->setSelected(itemThree);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(itemTwo->hasHover() == false);
    REQUIRE(itemTwo->hasFocus() == false);
    REQUIRE(itemThree->hasHover() == true);
    REQUIRE(itemThree->hasFocus() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, list) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, list) == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, list)->action.value == 2);
    listener.clear();

    // Manually select via focus
    itemOne->setFocus(true);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(itemOne->hasHover() == false);
    REQUIRE(itemOne->hasFocus() == true);
    REQUIRE(itemTwo->hasHover() == false);
    REQUIRE(itemTwo->hasFocus() == false);
    REQUIRE(itemThree->hasHover() == true);
    REQUIRE(itemThree->hasFocus() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, list) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, list) == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, list)->action.value == 0);
    listener.clear();
}

///=============================================================================
TEST_CASE("Gui Progress Bar") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto progressbar = new ffw::GuiProgressBar(&gui);
    progressbar->setSize(ffw::guiPercent(100), ffw::guiWrap());
    body->addWidget(progressbar);
    listener.addWidget(progressbar);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(progressbar->getRealSize() == ffw::Pointf(100.0f, 8.0f));
    REQUIRE(progressbar->hasFocus() == false);
    REQUIRE(progressbar->hasHover() == false);
    REQUIRE(gui.renderCounter() == 2);
    gui.clearCounter();

    REQUIRE(progressbar->getValue() == Approx(0.0f));
    
    // Hover over
    gui.injectMousePos(50.0f, 4.0f);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(progressbar->hasFocus() == false);
    REQUIRE(progressbar->hasHover() == true);
    REQUIRE(gui.renderCounter() == 0);
    gui.clearCounter();

    // Click on the progress bar
    CLICK_AND_UPDATE;
    REQUIRE(progressbar->hasFocus() == true);
    REQUIRE(progressbar->hasHover() == true);
    REQUIRE(gui.renderCounter() == 0);
    gui.clearCounter();

    progressbar->setValue(50.0f);
    CLICK_AND_UPDATE;
    REQUIRE(gui.renderCounter() == 1);
    gui.clearCounter();

    CLICK_AND_UPDATE;
    REQUIRE(gui.renderCounter() == 0);
    gui.clearCounter();
}

///=============================================================================
TEST_CASE("Gui Progress Circle") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto progressbar = new ffw::GuiProgressCircle(&gui);
    progressbar->setSize(ffw::guiPercent(100), ffw::guiWrap());
    body->addWidget(progressbar);
    listener.addWidget(progressbar);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(progressbar->getRealSize() == ffw::Pointf(100.0f, 70.0f));
    REQUIRE(progressbar->hasFocus() == false);
    REQUIRE(progressbar->hasHover() == false);
    REQUIRE(gui.renderCounter() == 2);
    gui.clearCounter();

    REQUIRE(progressbar->getValue() == Approx(0.0f));
    
    // Hover over
    gui.injectMousePos(50.0f, 4.0f);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(progressbar->hasFocus() == false);
    REQUIRE(progressbar->hasHover() == true);
    REQUIRE(gui.renderCounter() == 0);
    gui.clearCounter();

    // Click on the progress bar
    CLICK_AND_UPDATE;
    REQUIRE(progressbar->hasFocus() == true);
    REQUIRE(progressbar->hasHover() == true);
    REQUIRE(gui.renderCounter() == 0);
    gui.clearCounter();

    progressbar->setValue(50.0f);
    CLICK_AND_UPDATE;
    REQUIRE(gui.renderCounter() == 1);
    gui.clearCounter();

    CLICK_AND_UPDATE;
    REQUIRE(gui.renderCounter() == 0);
    gui.clearCounter();
}

///=============================================================================
TEST_CASE("Gui Radio") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto radioA = new ffw::GuiRadio(&gui, "Radio A", 10);
    radioA->setSize(ffw::guiPercent(100), ffw::guiWrap());
    body->addWidget(radioA);
    listener.addWidget(radioA);

    auto radioB = new ffw::GuiRadio(&gui, "Radio B", 20, radioA);
    radioB->setSize(ffw::guiPercent(100), ffw::guiWrap());
    body->addWidget(radioB);
    listener.addWidget(radioB);

    auto radioC = new ffw::GuiRadio(&gui, "Radio C", 30, radioA);
    radioC->setSize(ffw::guiPercent(100), ffw::guiWrap());
    body->addWidget(radioC);
    listener.addWidget(radioC);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(radioA->getRealSize() == ffw::Pointf(100.0f, 16.0f));
    REQUIRE(radioA->hasFocus() == false);
    REQUIRE(radioA->hasHover() == false);
    REQUIRE(radioB->getRealSize() == ffw::Pointf(100.0f, 16.0f));
    REQUIRE(radioB->hasFocus() == false);
    REQUIRE(radioB->hasHover() == false);
    REQUIRE(radioC->getRealSize() == ffw::Pointf(100.0f, 16.0f));
    REQUIRE(radioC->hasFocus() == false);
    REQUIRE(radioC->hasHover() == false);

    REQUIRE(radioA->getValue() == -1);

    // Hover over radio A
    gui.injectMousePos(50.0f, 8.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;

    REQUIRE(radioA->hasFocus() == true);
    REQUIRE(radioA->hasHover() == true);

    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioA) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioA) == 1);
    listener.clear();

    // Move to the actual clickable area
    gui.injectMousePos(8.0f, 8.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;

    REQUIRE(radioA->hasFocus() == true);
    REQUIRE(radioA->hasHover() == true);

    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioA) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioA) == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, radioA)->action.value == 10);
    listener.clear();

    // Move to the second radio
    gui.injectMousePos(8.0f, 24.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;

    REQUIRE(radioA->hasFocus() == false);
    REQUIRE(radioA->hasHover() == false);
    REQUIRE(radioB->hasFocus() == true);
    REQUIRE(radioB->hasHover() == true);

    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioA) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioA) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioB) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioB) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, radioB)->action.value == 20);
    listener.clear();

    // Manually select radio
    radioA->setValue(30);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(radioA->hasFocus() == false);
    REQUIRE(radioA->hasHover() == false);
    REQUIRE(radioB->hasFocus() == false);
    REQUIRE(radioB->hasHover() == true);
    REQUIRE(radioC->hasFocus() == true);
    REQUIRE(radioC->hasHover() == false);

    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioA) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioA) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioB) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioB) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioC) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioC) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, radioC)->action.value == 30);
    listener.clear();

    // Deselect all
    radioA->resetValue();
    TEST_UPDATE_AND_RENDER;

    REQUIRE(radioA->hasFocus() == false);
    REQUIRE(radioA->hasHover() == false);
    REQUIRE(radioB->hasFocus() == false);
    REQUIRE(radioB->hasHover() == true);
    REQUIRE(radioC->hasFocus() == false);
    REQUIRE(radioC->hasHover() == false);

    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioA) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioA) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioB) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioB) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, radioC) == 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, radioC) == 1);
    listener.clear();
}

///=============================================================================
TEST_CASE("Gui Slider") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto slider = new ffw::GuiSlider(&gui, false);
    slider->setSize(ffw::guiPercent(100.0f), ffw::guiWrap());
    body->addWidget(slider);
    listener.addWidget(slider);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(slider->getRealSize() == ffw::Pointf(100.0f, 16.0f));
    REQUIRE(slider->hasFocus() == false);
    REQUIRE(slider->hasHover() == false);

    REQUIRE(slider->getValue() == Approx(50.0f));
    REQUIRE(slider->getRange() == ffw::Pointf(0.0f, 100.0f));

    slider->setRange(100.0f, 200.0f);
    REQUIRE(slider->getValue() == Approx(100.0f));

    slider->setRange(-100.0f, 0.0f);
    REQUIRE(slider->getValue() == Approx(0.0f));

    TEST_UPDATE_AND_RENDER;
    listener.clear();
    gui.clearCounter();

    // Move to the center of the slider
    gui.injectMousePos(50.0f, 8.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;

    REQUIRE(slider->hasHover() == true);
    REQUIRE(slider->hasFocus() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, slider) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, slider) == 2);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, slider)->action.value == -50);
    REQUIRE(gui.renderCounter() == 3);
    gui.clearCounter();
    listener.clear();

    // Manually set the value
    slider->setValue(-25.0f);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(slider->hasHover() == true);
    REQUIRE(slider->hasFocus() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, slider) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, slider) == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, slider)->action.value == -25);
    REQUIRE(gui.renderCounter() == 1);
    gui.clearCounter();
    listener.clear();
}

///=============================================================================
TEST_CASE("Gui Scrollbar") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto scrollbar = new ffw::GuiScrollBar(&gui, false);
    scrollbar->setSize(ffw::guiPercent(100.0f), ffw::guiWrap());
    scrollbar->setIncrements(10.0f);
    body->addWidget(scrollbar);
    listener.addWidget(scrollbar);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(scrollbar->getRealSize() == ffw::Pointf(100.0f, 12.0f));
    REQUIRE(scrollbar->hasFocus() == false);
    REQUIRE(scrollbar->hasHover() == false);

    REQUIRE(scrollbar->getValue() == Approx(50.0f));
    REQUIRE(scrollbar->getRange() == ffw::Pointf(0.0f, 100.0f));

    REQUIRE(scrollbar->getButtonFirst()->getRealSize() == ffw::Pointf(12.0f, 12.0f));
    REQUIRE(scrollbar->getButtonSecond()->getRealSize() == ffw::Pointf(12.0f, 12.0f));
    REQUIRE(scrollbar->getSlider()->getRealSize() == ffw::Pointf(100.0f - 24.0f, 12.0f));

    // Move to the center of the scrollbar
    gui.injectMousePos(50.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;

    REQUIRE(scrollbar->hasHover() == true);
    REQUIRE(scrollbar->hasFocus() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, scrollbar) != 0);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, scrollbar) == 2);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, scrollbar)->action.value == 48);
    listener.clear();

    // Click the button on the left
    gui.injectMousePos(6.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;
    REQUIRE(scrollbar->hasHover() == true);
    REQUIRE(scrollbar->hasFocus() == false);
    REQUIRE(scrollbar->getButtonFirst()->hasHover() == true);
    REQUIRE(scrollbar->getButtonSecond()->hasHover() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, scrollbar) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, scrollbar) == 2);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, scrollbar)->action.value == 38);
    listener.clear();

    // Click the button on the right
    gui.injectMousePos(94.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;
    REQUIRE(scrollbar->hasHover() == true);
    REQUIRE(scrollbar->hasFocus() == false);
    REQUIRE(scrollbar->getButtonFirst()->hasHover() == false);
    REQUIRE(scrollbar->getButtonSecond()->hasHover() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, scrollbar) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, scrollbar) == 2);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, scrollbar)->action.value == 48);
    listener.clear();

    REQUIRE(scrollbar->getInversed() == false);
    scrollbar->setInversed(true);
    REQUIRE(scrollbar->getInversed() == true);

    // Manually set the value
    scrollbar->setValue(50.0f);
    REQUIRE(scrollbar->getValue() == Approx(50.0f));

    gui.injectMousePos(50.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(scrollbar->hasHover() == true);
    REQUIRE(scrollbar->hasFocus() == false);
    REQUIRE(scrollbar->getButtonFirst()->hasHover() == false);
    REQUIRE(scrollbar->getButtonSecond()->hasHover() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, scrollbar) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, scrollbar) == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, scrollbar)->action.value == 50);
    listener.clear();

    // Click away
    gui.injectMousePos(50.0f, 50.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;
    REQUIRE(scrollbar->hasHover() == false);
    REQUIRE(scrollbar->hasFocus() == false);
    REQUIRE(scrollbar->getButtonSecond()->hasHover() == false);
    REQUIRE(scrollbar->getButtonFirst()->hasHover() == false);

    // Click the button on the left
    gui.injectMousePos(6.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;
    REQUIRE(scrollbar->getButtonSecond()->hasHover() == false);
    REQUIRE(scrollbar->getButtonFirst()->hasHover() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, scrollbar) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, scrollbar) == 2);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, scrollbar)->action.value == 60);
    listener.clear();

    // Click the button on the right
    gui.injectMousePos(94.0f, 6.0f);
    TEST_UPDATE_AND_RENDER;
    CLICK_AND_UPDATE;
    REQUIRE(scrollbar->hasHover() == true);
    REQUIRE(scrollbar->hasFocus() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, scrollbar) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, scrollbar) == 2);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, scrollbar)->action.value == 50);
    listener.clear();

    // Resize width
    scrollbar->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(24.0f));
    TEST_UPDATE_AND_RENDER;

    REQUIRE(scrollbar->getRealSize() == ffw::Pointf(100.0f, 24.0f));
    REQUIRE(scrollbar->getButtonFirst()->getRealSize() == ffw::Pointf(24.0f, 24.0f));
    REQUIRE(scrollbar->getButtonSecond()->getRealSize() == ffw::Pointf(24.0f, 24.0f));
    REQUIRE(scrollbar->getSlider()->getRealSize() == ffw::Pointf(100.0f - 48.0f, 24.0f));
}

///=============================================================================
TEST_CASE("Gui Switch") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    EventCallbackListener listener;
    auto body = gui.getLayout();

    auto button = new ffw::GuiSwitch(&gui);
    button->setSize(ffw::guiWrap(), ffw::guiWrap());
    body->addWidget(button);
    listener.addWidget(button);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->getRealSize() == ffw::Pointf(16.0f, 8.0f));
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == false);

    // Hover over the checkbox button
    gui.injectMousePos(8.0f, 4.0f);

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == false);
    listener.clear();

    // Click the checkbox
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    listener.clear();

    // Click again to uncheck
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;

    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == true);
    REQUIRE(button->getValue() == false);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 0);
    listener.clear();

    // Click again to check and then move away mouse
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMousePos(8.0f, 50.0f); // Move mouse
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    listener.clear();

    button->setValue(false);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == false);
    listener.clear();

    button->setValue(true);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == true);
    listener.clear();

    button->setFocus(false);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == false);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == false);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 0);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == false);
    listener.clear();

    button->setFocus(true);
    TEST_UPDATE_AND_RENDER;
    REQUIRE(button->hasFocus() == true);
    REQUIRE(button->hasHover() == false);
    REQUIRE(button->getValue() == true);
    REQUIRE(listener.count(ffw::GuiEventType::ACTION, button) == 1);
    REQUIRE(listener.count(ffw::GuiEventType::FOCUS, button) == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::ACTION, button)->action.value == 1);
    REQUIRE(listener.getLast(ffw::GuiEventType::FOCUS, button)->focus.gained == true);
    listener.clear();
}

