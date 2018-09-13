#include <ffw/gui.h>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "nullrenderer.h"


///=============================================================================
TEST_CASE("Mouse position #1") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    layout->addWidget(widget);

    gui.injectMousePos(15, 25);

    TEST_UPDATE_AND_RENDER;

    // Originally at [15, 25]
    // but the padding moves it by [-10.0f, -10]
    REQUIRE(widget->getMousePos().x == 5);
    REQUIRE(widget->getMousePos().y == 15);

    layout->setOffset(ffw::Pointi(2, 5));

    gui.injectMousePos(15, 25);

    TEST_UPDATE_AND_RENDER;

    // Offset moves it further by [-2, -5]
    REQUIRE(widget->getMousePos().x == 3);
    REQUIRE(widget->getMousePos().y == 10.0f);
}

///=============================================================================
TEST_CASE("Mouse position and mouse button") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    GuiWidgetNull* widgets[4];

    for (int i = 0; i < 4; i++) {
        widgets[i] = new GuiWidgetNull(&gui);
        widgets[i]->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
        widgets[i]->setMargin(0.0f);
        widgets[i]->setPadding(0.0f);
        layout->addWidget(widgets[i]);
    }

    gui.injectMousePos(15, 25);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getMousePos().x == 5);
    REQUIRE(widgets[0]->getMousePos().y == 15);

    REQUIRE(widgets[0]->hasHover() == true);
    REQUIRE(widgets[1]->hasHover() == false);
    REQUIRE(widgets[2]->hasHover() == false);
    REQUIRE(widgets[3]->hasHover() == false);

    gui.injectMousePos(25, 35);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getMousePos().x == 5);
    REQUIRE(widgets[0]->getMousePos().y == 15);

    REQUIRE(widgets[1]->getMousePos().x == 15);
    REQUIRE(widgets[1]->getMousePos().y == 5);

    REQUIRE(widgets[0]->hasHover() == false);
    REQUIRE(widgets[1]->hasHover() == true);
    REQUIRE(widgets[2]->hasHover() == false);
    REQUIRE(widgets[3]->hasHover() == false);

    REQUIRE(widgets[0]->hasFocus() == false);
    REQUIRE(widgets[1]->hasFocus() == false);
    REQUIRE(widgets[2]->hasFocus() == false);
    REQUIRE(widgets[3]->hasFocus() == false);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getMousePos().x == 5);
    REQUIRE(widgets[0]->getMousePos().y == 15);

    REQUIRE(widgets[1]->getMousePos().x == 15);
    REQUIRE(widgets[1]->getMousePos().y == 5);

    REQUIRE(widgets[0]->hasHover() == false);
    REQUIRE(widgets[1]->hasHover() == true);
    REQUIRE(widgets[2]->hasHover() == false);
    REQUIRE(widgets[3]->hasHover() == false);

    REQUIRE(widgets[0]->hasFocus() == false);
    REQUIRE(widgets[1]->hasFocus() == true);
    REQUIRE(widgets[2]->hasFocus() == false);
    REQUIRE(widgets[3]->hasFocus() == false);

    gui.injectMousePos(25, 55);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[2]->getMousePos().x == 15);
    REQUIRE(widgets[2]->getMousePos().y == 5);

    REQUIRE(widgets[0]->hasHover() == false);
    REQUIRE(widgets[1]->hasHover() == false);
    REQUIRE(widgets[2]->hasHover() == true);
    REQUIRE(widgets[3]->hasHover() == false);

    REQUIRE(widgets[0]->hasFocus() == false);
    REQUIRE(widgets[1]->hasFocus() == true);
    REQUIRE(widgets[2]->hasFocus() == false);
    REQUIRE(widgets[3]->hasFocus() == false);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[2]->getMousePos().x == 15);
    REQUIRE(widgets[2]->getMousePos().y == 5);

    REQUIRE(widgets[0]->hasHover() == false);
    REQUIRE(widgets[1]->hasHover() == false);
    REQUIRE(widgets[2]->hasHover() == true);
    REQUIRE(widgets[3]->hasHover() == false);

    REQUIRE(widgets[0]->hasFocus() == false);
    REQUIRE(widgets[1]->hasFocus() == true);
    REQUIRE(widgets[2]->hasFocus() == false);
    REQUIRE(widgets[3]->hasFocus() == false);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[2]->getMousePos().x == 15);
    REQUIRE(widgets[2]->getMousePos().y == 5);

    REQUIRE(widgets[0]->hasHover() == false);
    REQUIRE(widgets[1]->hasHover() == false);
    REQUIRE(widgets[2]->hasHover() == true);
    REQUIRE(widgets[3]->hasHover() == false);

    REQUIRE(widgets[0]->hasFocus() == false);
    REQUIRE(widgets[1]->hasFocus() == false);
    REQUIRE(widgets[2]->hasFocus() == true);
    REQUIRE(widgets[3]->hasFocus() == false);
}

///=============================================================================
TEST_CASE("Event hover") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    GuiEventCatcher events;

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    GuiWidgetNull* widgets[4];

    for (int i = 0; i < 4; i++) {
        widgets[i] = new GuiWidgetNull(&gui);
        widgets[i]->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
        widgets[i]->setMargin(0.0f);
        widgets[i]->setPadding(0.0f);
        widgets[i]->addEventCallback(&GuiEventCatcher::widgetEvent, &events);
        layout->addWidget(widgets[i]);
    }

    gui.injectMousePos(15, 25);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getMousePos().x == 5);
    REQUIRE(widgets[0]->getMousePos().y == 15);

    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[0]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[3]) == 0.0f);

    REQUIRE(events.get(ffw::GuiEventType::HOVER, widgets[0]).data.hover.gained == true);

    events.reset();
    gui.injectMousePos(25, 35);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getMousePos().x == 5);
    REQUIRE(widgets[0]->getMousePos().y == 15);

    REQUIRE(widgets[1]->getMousePos().x == 15);
    REQUIRE(widgets[1]->getMousePos().y == 5);

    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[0]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[1]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[3]) == 0.0f);

    REQUIRE(events.get(ffw::GuiEventType::HOVER, widgets[0]).data.hover.gained == false);
    REQUIRE(events.get(ffw::GuiEventType::HOVER, widgets[1]).data.hover.gained == true);
}

///=============================================================================
TEST_CASE("Event focus") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    GuiEventCatcher events;

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    GuiWidgetNull* widgets[4];

    for (int i = 0; i < 4; i++) {
        widgets[i] = new GuiWidgetNull(&gui);
        widgets[i]->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
        widgets[i]->setMargin(0.0f);
        widgets[i]->setPadding(0.0f);
        widgets[i]->addEventCallback(&GuiEventCatcher::widgetEvent, &events);
        layout->addWidget(widgets[i]);
    }

    gui.injectMousePos(15, 25);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[0]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::HOVER, widgets[3]) == 0.0f);

    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[0]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[3]) == 0.0f);

    REQUIRE(events.get(ffw::GuiEventType::FOCUS, widgets[0]).data.focus.gained == true);

    events.reset();
    gui.injectMousePos(25, 35);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[0]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[3]) == 0.0f);

    events.reset();
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[0]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[1]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::FOCUS, widgets[3]) == 0.0f);

    REQUIRE(events.get(ffw::GuiEventType::FOCUS, widgets[0]).data.focus.gained == false);
    REQUIRE(events.get(ffw::GuiEventType::FOCUS, widgets[1]).data.focus.gained == true);
}

///=============================================================================
TEST_CASE("Event state") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    GuiEventCatcher events;

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    GuiWidgetNull* widgets[4];

    for (int i = 0; i < 4; i++) {
        widgets[i] = new GuiWidgetNull(&gui);
        widgets[i]->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
        widgets[i]->setMargin(0.0f);
        widgets[i]->setPadding(0.0f);
        widgets[i]->addEventCallback(&GuiEventCatcher::widgetEvent, &events);
        layout->addWidget(widgets[i]);
    }

    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[0]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[3]) == 0.0f);

    widgets[0]->setDisabled(true);
    events.reset();
    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[0]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[3]) == 0.0f);

    REQUIRE(events.get(ffw::GuiEventType::STATE, widgets[0]).data.state.disabled == true);

    widgets[0]->setDisabled(false);
    events.reset();
    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[0]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[3]) == 0.0f);

    REQUIRE(events.get(ffw::GuiEventType::STATE, widgets[0]).data.state.disabled == false);

    widgets[0]->setDisabled(false);
    events.reset();
    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[0]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::STATE, widgets[3]) == 0.0f);
}

///=============================================================================
TEST_CASE("Event input") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    GuiEventCatcher events;

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    GuiWidgetNull* widgets[4];

    for (int i = 0; i < 4; i++) {
        widgets[i] = new GuiWidgetNull(&gui);
        widgets[i]->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
        widgets[i]->setMargin(0.0f);
        widgets[i]->setPadding(0.0f);
        widgets[i]->addEventCallback(&GuiEventCatcher::widgetEvent, &events);
        layout->addWidget(widgets[i]);
    }

    gui.injectText('A');

    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[0]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[3]) == 0.0f);

    events.reset();
    gui.injectText('A');
    gui.injectMousePos(15, 25);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[0]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[3]) == 0.0f);

    events.reset();
    gui.injectText('A');
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[0]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[3]) == 0.0f);

    REQUIRE(events.get(ffw::GuiEventType::INPUT, widgets[0]).data.input.chr == 'A');

    events.reset();
    gui.injectText('A');
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[0]) == 1);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[3]) == 0.0f);

    REQUIRE(events.get(ffw::GuiEventType::INPUT, widgets[0]).data.input.chr == 'A');

    events.reset();
    gui.injectText('A');
    gui.injectMousePos(15, 0);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);
    TEST_UPDATE_AND_RENDER;

    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[0]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[1]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[2]) == 0.0f);
    REQUIRE(events.count(ffw::GuiEventType::INPUT, widgets[3]) == 0.0f);
}

///=============================================================================
TEST_CASE("Default focus") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    layout->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);

    gui.injectMousePos(15, 25);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMousePos(15, 55);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);
}

///=============================================================================
TEST_CASE("Sticky focus") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    auto widget = new GuiWidgetNullSticky(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    layout->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);

    gui.injectMousePos(15, 25);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMousePos(15, 55);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);
}


///=============================================================================
TEST_CASE("Drop focus") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    auto widget = new GuiWidgetNullDrop(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    layout->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);

    gui.injectMousePos(15, 25);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);

    gui.injectMousePos(15, 55);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);
}

///=============================================================================
TEST_CASE("Toggle focus") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(10.0f);
    gui.getLayout()->addWidget(layout);

    auto widget = new GuiWidgetNullToggle(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    layout->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);

    gui.injectMousePos(15, 25);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMousePos(15, 55);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::RELEASED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == true);

    gui.injectMousePos(15, 25);
    gui.injectMouseButton(ffw::MouseButton::LEFT, ffw::MouseMode::PRESSED);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->hasFocus() == false);
}

