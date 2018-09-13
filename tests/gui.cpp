#include <ffw/gui.h>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "nullrenderer.h"

///=============================================================================
TEST_CASE("Gui Units") {
    ffw::GuiUnits u;

    u = 42.0f;
    REQUIRE(u == 42.0f);
    REQUIRE(u == ffw::guiPixels(42));
    REQUIRE(u != ffw::guiPercent(42));

    u = ffw::guiPercent(25);
    REQUIRE(u != 25.0f);
    REQUIRE(u != ffw::guiPixels(25));
    REQUIRE(u == ffw::guiPercent(25));

    REQUIRE(u.toReal(100.0f) == 25);
    REQUIRE(u.toReal(150.0f) == 37.5f);

    u.setPercent(50.0f);
    REQUIRE(u != 50.0f);
    REQUIRE(u != ffw::guiPixels(50.0f));
    REQUIRE(u == ffw::guiPercent(50.0f));

    u.setPixels(50.0f);
    REQUIRE(u == 50.0f);
    REQUIRE(u == ffw::guiPixels(50.0f));
    REQUIRE(u != ffw::guiPercent(50.0f));

    REQUIRE(u.toReal(100.0f) == 50.0f);
}

///=============================================================================
TEST_CASE("Gui Units 2D") {
    ffw::GuiUnits2D vec;
    vec.set(20.0f, 40.0f);

    REQUIRE(vec.x == 20.0f);
    REQUIRE(vec.y == 40.0f);

    REQUIRE(vec.x == ffw::guiPixels(20.0f));
    REQUIRE(vec.y == ffw::guiPixels(40.0f));

    vec.set(ffw::guiPercent(25), ffw::guiPercent(50.0f));
    REQUIRE(vec.x != ffw::guiPixels(25));
    REQUIRE(vec.y != ffw::guiPixels(50.0f));

    REQUIRE(vec.x == ffw::guiPercent(25));
    REQUIRE(vec.y == ffw::guiPercent(50.0f));

    REQUIRE(vec.toReal(ffw::Pointf(200.0f, 200.0f)).x == Approx(50.0f));
    REQUIRE(vec.toReal(ffw::Pointf(200.0f, 200.0f)).y == Approx(100.0f));

    vec.set(ffw::guiPixels(25), ffw::guiPixels(50.0f));
    REQUIRE(vec.toReal(ffw::Pointf(200.0f, 200.0f)).x == Approx(25.0f));
    REQUIRE(vec.toReal(ffw::Pointf(200.0f, 200.0f)).y == Approx(50.0f));
}

///=============================================================================
TEST_CASE("Testing window functionality") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    const auto size = font.getStringSize("Hello", -1.0f, 1.5f);
    REQUIRE(size.x == Approx(5.0f * 8.0f));
    REQUIRE(size.y == Approx(12.0f));
}

///=============================================================================
TEST_CASE("Testing window size") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(gui.getLayout()->getRealSize().x == Approx(100.0f));
    REQUIRE(gui.getLayout()->getRealSize().y == Approx(100.0f));

    REQUIRE(gui.getLayout()->getVisibleContentSize().x == Approx(100.0f));
    REQUIRE(gui.getLayout()->getVisibleContentSize().y == Approx(100.0f));
}

///=============================================================================
TEST_CASE("Basic functionality") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    auto widget = new GuiWidgetNull(&gui);

    REQUIRE(widget->getAlign() == ffw::GuiAlign::TOP_LEFT);
    widget->setAlign(ffw::GuiAlign::CENTER);
    REQUIRE(widget->getAlign() == ffw::GuiAlign::CENTER);

    // set default font to whole window
    GuiFontNull font1;
    font1.create(8);
    gui.setDefaultFont(&font1);
    REQUIRE(widget->getCurrentFont() == &font1);

    // set default font to widget only
    GuiFontNull font2;
    font2.create(8);
    widget->setFont(&font2);
    REQUIRE(widget->getCurrentFont() == &font2);

    widget->setLineHeight(1.2f);
    REQUIRE(widget->getLineHeight() == Approx(1.2f));

    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));
    REQUIRE(widget->getSize().x == ffw::guiPercent(100.0f));
    REQUIRE(widget->getSize().y == ffw::guiPercent(50.0f));

    widget->setPadding(0.0f);
    widget->setMargin(0.0f);
    gui.getLayout()->setPadding(5);
    gui.getLayout()->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(gui.getLayout()->getRealSize().x == Approx(100.0f));
    REQUIRE(gui.getLayout()->getRealSize().y == Approx(100.0f));

    REQUIRE(gui.getLayout()->getVisibleContentSize().x == Approx(90.0f));
    REQUIRE(gui.getLayout()->getVisibleContentSize().y == Approx(90.0f));

    REQUIRE(widget->getRealSize().x == Approx(90.0f));
    REQUIRE(widget->getRealSize().y == Approx(45));

    REQUIRE(widget->getAbsolutePos().x == Approx(5));
    REQUIRE(widget->getAbsolutePos().y == Approx(5));
}
