#include <ffw/gui.h>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "nullrenderer.h"

///=============================================================================
TEST_CASE("Align to top left") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::TOP_LEFT);
    layout->setOrientation(ffw::GuiOrientation::HORIZONTAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(70.0f), ffw::guiPixels(25.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(10.0f, 10.0f));
    CHECK(second->getRealPos() == ffw::Pointf(55.0f, 10.0f));
    CHECK(third->getRealPos() == ffw::Pointf(10.0f, 55.0f));
}

///=============================================================================
TEST_CASE("Align to top right") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::TOP_RIGHT);
    layout->setOrientation(ffw::GuiOrientation::HORIZONTAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(70.0f), ffw::guiPixels(25.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(20.0f, 10.0f));
    CHECK(second->getRealPos() == ffw::Pointf(65.0f, 10.0f));
    CHECK(third->getRealPos() == ffw::Pointf(20.0f, 55.0f));
}

///=============================================================================
TEST_CASE("Align to top center") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::TOP_CENTER);
    layout->setOrientation(ffw::GuiOrientation::HORIZONTAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(70.0f), ffw::guiPixels(25.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(15.0f, 10.0f));
    CHECK(second->getRealPos() == ffw::Pointf(60.0f, 10.0f));
    CHECK(third->getRealPos() == ffw::Pointf(15.0f, 55.0f));
}

///=============================================================================
TEST_CASE("Align to left") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::LEFT);
    layout->setOrientation(ffw::GuiOrientation::HORIZONTAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(70.0f), ffw::guiPixels(25.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(10.0f, 15.0f));
    CHECK(second->getRealPos() == ffw::Pointf(55.0f, 15.0f));
    CHECK(third->getRealPos() == ffw::Pointf(10.0f, 60.0f));
}

///=============================================================================
TEST_CASE("Align to right") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::RIGHT);
    layout->setOrientation(ffw::GuiOrientation::HORIZONTAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(70.0f), ffw::guiPixels(25.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(20.0f, 15.0f));
    CHECK(second->getRealPos() == ffw::Pointf(65.0f, 15.0f));
    CHECK(third->getRealPos() == ffw::Pointf(20.0f, 60.0f));
}

///=============================================================================
TEST_CASE("Align to center") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::CENTER);
    layout->setOrientation(ffw::GuiOrientation::HORIZONTAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(70.0f), ffw::guiPixels(25.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(15.0f, 15.0f));
    CHECK(second->getRealPos() == ffw::Pointf(60.0f, 15.0f));
    CHECK(third->getRealPos() == ffw::Pointf(15.0f, 60.0f));
}

///=============================================================================
TEST_CASE("Align to bottom left") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::BOTTOM_LEFT);
    layout->setOrientation(ffw::GuiOrientation::HORIZONTAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(70.0f), ffw::guiPixels(25.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(10.0f, 20.0f));
    CHECK(second->getRealPos() == ffw::Pointf(55.0f, 20.0f));
    CHECK(third->getRealPos() == ffw::Pointf(10.0f, 65.0f));
}

///=============================================================================
TEST_CASE("Align to bottom right") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::BOTTOM_RIGHT);
    layout->setOrientation(ffw::GuiOrientation::HORIZONTAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(70.0f), ffw::guiPixels(25.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(20.0f, 20.0f));
    CHECK(second->getRealPos() == ffw::Pointf(65.0f, 20.0f));
    CHECK(third->getRealPos() == ffw::Pointf(20.0f, 65.0f));
}

///=============================================================================
TEST_CASE("Align to bottom center") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::BOTTOM_CENTER);
    layout->setOrientation(ffw::GuiOrientation::HORIZONTAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(70.0f), ffw::guiPixels(25.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(15.0f, 20.0f));
    CHECK(second->getRealPos() == ffw::Pointf(60.0f, 20.0f));
    CHECK(third->getRealPos() == ffw::Pointf(15.0f, 65.0f));
}

///=============================================================================
TEST_CASE("Align to top left vertical") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::TOP_LEFT);
    layout->setOrientation(ffw::GuiOrientation::VERTICAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(70.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(10.0f, 10.0f));
    CHECK(second->getRealPos() == ffw::Pointf(10.0f, 55.0f));
    CHECK(third->getRealPos() == ffw::Pointf(55.0f, 10.0f));
}

///=============================================================================
TEST_CASE("Align to top right vertical") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::TOP_RIGHT);
    layout->setOrientation(ffw::GuiOrientation::VERTICAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(70.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(65.0f, 10.0f));
    CHECK(second->getRealPos() == ffw::Pointf(65.0f, 55.0f));
    CHECK(third->getRealPos() == ffw::Pointf(110.0f, 10.0f));
}

///=============================================================================
TEST_CASE("Align to top center vertical") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::TOP_CENTER);
    layout->setOrientation(ffw::GuiOrientation::VERTICAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(70.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(37.0f, 10.0f));
    CHECK(second->getRealPos() == ffw::Pointf(37.0f, 55.0f));
    CHECK(third->getRealPos() == ffw::Pointf(37.0f, 10.0f));
}

///=============================================================================
TEST_CASE("Align to left vertical") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::LEFT);
    layout->setOrientation(ffw::GuiOrientation::VERTICAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(70.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(10.0f, 15.0f));
    CHECK(second->getRealPos() == ffw::Pointf(10.0f, 60.0f));
    CHECK(third->getRealPos() == ffw::Pointf(55.0f, 15.0f));
}

///=============================================================================
TEST_CASE("Align to right vertical") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::RIGHT);
    layout->setOrientation(ffw::GuiOrientation::VERTICAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(70.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(65.0f, 15.0f));
    CHECK(second->getRealPos() == ffw::Pointf(65.0f, 60.0f));
    CHECK(third->getRealPos() == ffw::Pointf(110.0f, 15.0f));
}

///=============================================================================
TEST_CASE("Align to center vertical") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::CENTER);
    layout->setOrientation(ffw::GuiOrientation::VERTICAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(70.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(37.0f, 15.0f));
    CHECK(second->getRealPos() == ffw::Pointf(37.0f, 60.0f));
    CHECK(third->getRealPos() == ffw::Pointf(37.0f, 15.0f));
}

///=============================================================================
TEST_CASE("Align to bottom left vertical") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::BOTTOM_LEFT);
    layout->setOrientation(ffw::GuiOrientation::VERTICAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(70.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(10.0f, 20.0f));
    CHECK(second->getRealPos() == ffw::Pointf(10.0f, 65.0f));
    CHECK(third->getRealPos() == ffw::Pointf(55.0f, 20.0f));
}

///=============================================================================
TEST_CASE("Align to bottom right vertical") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::BOTTOM_RIGHT);
    layout->setOrientation(ffw::GuiOrientation::VERTICAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(70.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(65.0f, 20.0f));
    CHECK(second->getRealPos() == ffw::Pointf(65.0f, 65.0f));
    CHECK(third->getRealPos() == ffw::Pointf(110.0f, 20.0f));
}

///=============================================================================
TEST_CASE("Align to bottom center vertical") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = gui.getLayout();
    layout->setAlign(ffw::GuiAlign::BOTTOM_CENTER);
    layout->setOrientation(ffw::GuiOrientation::VERTICAL);
    layout->setWrap(true);

    auto first = new ffw::GuiVerticalLayout(&gui);
    first->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    first->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(first);

    auto second = new ffw::GuiVerticalLayout(&gui);
    second->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(25.0f));
    second->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(second);

    auto third = new ffw::GuiVerticalLayout(&gui);
    third->setSize(ffw::guiPixels(25.0f), ffw::guiPixels(70.0f));
    third->setMargin(ffw::guiPixels(10.0f));
    layout->addWidget(third);

    TEST_UPDATE_AND_RENDER;

    CHECK(first->getRealPos() == ffw::Pointf(37.0f, 20.0f));
    CHECK(second->getRealPos() == ffw::Pointf(37.0f, 65.0f));
    CHECK(third->getRealPos() == ffw::Pointf(37.0f, 20.0f));
}