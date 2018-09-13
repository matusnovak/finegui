#include <ffw/gui.h>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "nullrenderer.h"

///=============================================================================
TEST_CASE("Margin in pixels") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));

    widget->setPadding(0.0f);
    widget->setMargin(0.0f);
    gui.getLayout()->setPadding(5);
    gui.getLayout()->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->getRealSize().x == Approx(90.0f));
    REQUIRE(widget->getRealSize().y == Approx(45));

    widget->setMargin(1, 2, 3, 4);
    REQUIRE(widget->getMargin(0) == 1.0f);
    REQUIRE(widget->getMargin(1) == 2.0f);
    REQUIRE(widget->getMargin(2) == 3.0f);
    REQUIRE(widget->getMargin(3) == 4.0f);

    widget->setMargin(5);
    REQUIRE(widget->getMargin(0) == 5.0f);
    REQUIRE(widget->getMargin(1) == 5.0f);
    REQUIRE(widget->getMargin(2) == 5.0f);
    REQUIRE(widget->getMargin(3) == 5.0f);

    widget->setMarginTop(2);
    widget->setMarginBottom(4);
    REQUIRE(widget->getMargin(0) == 2.0f);
    REQUIRE(widget->getMargin(1) == 5.0f);
    REQUIRE(widget->getMargin(2) == 4.0f);
    REQUIRE(widget->getMargin(3) == 5.0f);

    widget->setMarginRight(1);
    widget->setMarginLeft(3);
    REQUIRE(widget->getMargin(0) == 2.0f);
    REQUIRE(widget->getMargin(1) == 1.0f);
    REQUIRE(widget->getMargin(2) == 4.0f);
    REQUIRE(widget->getMargin(3) == 3.0f);

    REQUIRE(widget->getMarginInPixels(0) == Approx(2.0f));
    REQUIRE(widget->getMarginInPixels(1) == Approx(1.0f));
    REQUIRE(widget->getMarginInPixels(2) == Approx(4.0f));
    REQUIRE(widget->getMarginInPixels(3) == Approx(3.0f));
}

///=============================================================================
TEST_CASE("Margin in percent") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));

    widget->setPadding(0.0f);
    widget->setMargin(0.0f);
    gui.getLayout()->setPadding(0.0f);
    gui.getLayout()->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->getRealSize().x == Approx(100.0f));
    REQUIRE(widget->getRealSize().y == Approx(50.0f));

    widget->setMargin(ffw::guiPercent(1), ffw::guiPercent(2), ffw::guiPercent(3), ffw::guiPercent(4));
    REQUIRE(widget->getMargin(0) == ffw::guiPercent(1));
    REQUIRE(widget->getMargin(1) == ffw::guiPercent(2));
    REQUIRE(widget->getMargin(2) == ffw::guiPercent(3));
    REQUIRE(widget->getMargin(3) == ffw::guiPercent(4));

    widget->setMargin(ffw::guiPercent(5));
    REQUIRE(widget->getMargin(0) == ffw::guiPercent(5));
    REQUIRE(widget->getMargin(1) == ffw::guiPercent(5));
    REQUIRE(widget->getMargin(2) == ffw::guiPercent(5));
    REQUIRE(widget->getMargin(3) == ffw::guiPercent(5));

    widget->setMarginTop(ffw::guiPercent(2));
    widget->setMarginBottom(ffw::guiPercent(4));
    REQUIRE(widget->getMargin(0) == ffw::guiPercent(2));
    REQUIRE(widget->getMargin(1) == ffw::guiPercent(5));
    REQUIRE(widget->getMargin(2) == ffw::guiPercent(4));
    REQUIRE(widget->getMargin(3) == ffw::guiPercent(5));

    widget->setMarginRight(ffw::guiPercent(1));
    widget->setMarginLeft(ffw::guiPercent(3));
    REQUIRE(widget->getMargin(0) == ffw::guiPercent(2));
    REQUIRE(widget->getMargin(1) == ffw::guiPercent(1));
    REQUIRE(widget->getMargin(2) == ffw::guiPercent(4));
    REQUIRE(widget->getMargin(3) == ffw::guiPercent(3));

    // The widget's parent inner box size is 100x100 (no padding)
    REQUIRE(widget->getMarginInPixels(0) == Approx(100 * 0.02));
    REQUIRE(widget->getMarginInPixels(1) == Approx(100 * 0.01));
    REQUIRE(widget->getMarginInPixels(2) == Approx(100 * 0.04));
    REQUIRE(widget->getMarginInPixels(3) == Approx(100 * 0.03));
}

///=============================================================================
TEST_CASE("Padding in pixels") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));

    widget->setPadding(0.0f);
    widget->setMargin(0.0f);
    gui.getLayout()->setPadding(5);
    gui.getLayout()->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->getRealSize().x == Approx(90.0f));
    REQUIRE(widget->getRealSize().y == Approx(45));

    widget->setPadding(1, 2, 3, 4);
    REQUIRE(widget->getPadding(0) == 1.0f);
    REQUIRE(widget->getPadding(1) == 2.0f);
    REQUIRE(widget->getPadding(2) == 3.0f);
    REQUIRE(widget->getPadding(3) == 4.0f);

    widget->setPadding(5);
    REQUIRE(widget->getPadding(0) == 5.0f);
    REQUIRE(widget->getPadding(1) == 5.0f);
    REQUIRE(widget->getPadding(2) == 5.0f);
    REQUIRE(widget->getPadding(3) == 5.0f);

    widget->setPaddingTop(2);
    widget->setPaddingBottom(4);
    REQUIRE(widget->getPadding(0) == 2.0f);
    REQUIRE(widget->getPadding(1) == 5.0f);
    REQUIRE(widget->getPadding(2) == 4.0f);
    REQUIRE(widget->getPadding(3) == 5.0f);

    widget->setPaddingRight(1);
    widget->setPaddingLeft(3);
    REQUIRE(widget->getPadding(0) == 2.0f);
    REQUIRE(widget->getPadding(1) == 1.0f);
    REQUIRE(widget->getPadding(2) == 4.0f);
    REQUIRE(widget->getPadding(3) == 3.0f);

    REQUIRE(widget->getPaddingInPixels(0) == Approx(2.0f));
    REQUIRE(widget->getPaddingInPixels(1) == Approx(1.0f));
    REQUIRE(widget->getPaddingInPixels(2) == Approx(4.0f));
    REQUIRE(widget->getPaddingInPixels(3) == Approx(3.0f));
}

///=============================================================================
TEST_CASE("Padding in percent") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));

    widget->setPadding(0.0f);
    widget->setMargin(0.0f);
    gui.getLayout()->setPadding(0.0f);
    gui.getLayout()->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->getRealSize().x == Approx(100.0f));
    REQUIRE(widget->getRealSize().y == Approx(50.0f));

    widget->setPadding(ffw::guiPercent(1), ffw::guiPercent(2), ffw::guiPercent(3), ffw::guiPercent(4));
    REQUIRE(widget->getPadding(0) == ffw::guiPercent(1));
    REQUIRE(widget->getPadding(1) == ffw::guiPercent(2));
    REQUIRE(widget->getPadding(2) == ffw::guiPercent(3));
    REQUIRE(widget->getPadding(3) == ffw::guiPercent(4));

    widget->setPadding(ffw::guiPercent(5));
    REQUIRE(widget->getPadding(0) == ffw::guiPercent(5));
    REQUIRE(widget->getPadding(1) == ffw::guiPercent(5));
    REQUIRE(widget->getPadding(2) == ffw::guiPercent(5));
    REQUIRE(widget->getPadding(3) == ffw::guiPercent(5));

    widget->setPaddingTop(ffw::guiPercent(2));
    widget->setPaddingBottom(ffw::guiPercent(4));
    REQUIRE(widget->getPadding(0) == ffw::guiPercent(2));
    REQUIRE(widget->getPadding(1) == ffw::guiPercent(5));
    REQUIRE(widget->getPadding(2) == ffw::guiPercent(4));
    REQUIRE(widget->getPadding(3) == ffw::guiPercent(5));

    widget->setPaddingRight(ffw::guiPercent(1));
    widget->setPaddingLeft(ffw::guiPercent(3));
    REQUIRE(widget->getPadding(0) == ffw::guiPercent(2));
    REQUIRE(widget->getPadding(1) == ffw::guiPercent(1));
    REQUIRE(widget->getPadding(2) == ffw::guiPercent(4));
    REQUIRE(widget->getPadding(3) == ffw::guiPercent(3));

    // The widget's parent inner box size is 100x100 (no padding)
    REQUIRE(widget->getPaddingInPixels(0) == Approx(50 * 0.02));
    REQUIRE(widget->getPaddingInPixels(1) == Approx(100 * 0.01));
    REQUIRE(widget->getPaddingInPixels(2) == Approx(50 * 0.04));
    REQUIRE(widget->getPaddingInPixels(3) == Approx(100 * 0.03));
}

///=============================================================================
TEST_CASE("Changing the size") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);
    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));

    widget->setPadding(0.0f);
    widget->setMargin(0.0f);
    gui.getLayout()->setPadding(0.0f);
    gui.getLayout()->addWidget(widget);

    SECTION("set the size of the widget first") {
        // First run, always invalidate and update
        // the real size
        widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));

        TEST_UPDATE_AND_RENDER;

        REQUIRE(widget->getRealSize().x == Approx(100.0f));
        REQUIRE(widget->getRealSize().y == Approx(50.0f));

        // Second run, should update the real size
        widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));

        TEST_UPDATE_AND_RENDER;

        REQUIRE(widget->getRealSize().x == Approx(100.0f));
        REQUIRE(widget->getRealSize().y == Approx(100.0f));
    }

    SECTION("set the size of the window first") {
        // First run, always invalidate and update
        // the real size
        widget->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));

        TEST_UPDATE_AND_RENDER;

        REQUIRE(widget->getRealSize().x == Approx(100.0f));
        REQUIRE(widget->getRealSize().y == Approx(50.0f));

        // Second run, should update the real size
        // But this time update the window
        gui.getLayout()->setSize(ffw::guiPixels(200.0f), ffw::guiPixels(200.0f));

        TEST_UPDATE_AND_RENDER;

        REQUIRE(widget->getRealSize().x == Approx(200.0f));
        REQUIRE(widget->getRealSize().y == Approx(100.0f));
    }
}

///=============================================================================
TEST_CASE("Changing the size and position #1") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiHorizontalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(0.0f);

    gui.getLayout()->addWidget(layout);

    GuiWidgetNull* widget[2];
    widget[0] = new GuiWidgetNull(&gui);
    widget[1] = new GuiWidgetNull(&gui);
    widget[0]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(100.0f));
    widget[1]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(100.0f));
    widget[0]->setMargin(0.0f);
    widget[0]->setPadding(0.0f);
    widget[1]->setMargin(0.0f);
    widget[1]->setPadding(0.0f);

    layout->addWidget(widget[0]);
    layout->addWidget(widget[1]);

    TEST_UPDATE_AND_RENDER;

    // getLayout should be 100x100 pixels
    // and each widget should be 50x100 pixels

    REQUIRE(layout->getRealSize().x == Approx(100.0f));
    REQUIRE(layout->getRealSize().y == Approx(100.0f));

    REQUIRE(widget[0]->getRealSize().x == Approx(50.0f));
    REQUIRE(widget[0]->getRealSize().y == Approx(100.0f));

    REQUIRE(widget[1]->getRealSize().x == Approx(50.0f));
    REQUIRE(widget[1]->getRealSize().y == Approx(100.0f));

    SECTION("Changing the size of the layout should change childrens' sizes") {
        layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));

        TEST_UPDATE_AND_RENDER;

        REQUIRE(layout->getRealSize().x == Approx(100.0f));
        REQUIRE(layout->getRealSize().y == Approx(50.0f));

        REQUIRE(widget[0]->getRealSize().x == Approx(50.0f));
        REQUIRE(widget[0]->getRealSize().y == Approx(50.0f));

        REQUIRE(widget[1]->getRealSize().x == Approx(50.0f));
        REQUIRE(widget[1]->getRealSize().y == Approx(50.0f));
    }

    SECTION("Changing the size of the layout should change childrens' abs positions") {
        layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(50.0f));

        TEST_UPDATE_AND_RENDER;

        REQUIRE(layout->getRealSize().x == Approx(100.0f));
        REQUIRE(layout->getRealSize().y == Approx(50.0f));

        REQUIRE(widget[0]->getAbsolutePos().x == Approx(0.0f));
        REQUIRE(widget[0]->getAbsolutePos().y == Approx(0.0f));

        REQUIRE(widget[1]->getAbsolutePos().x == Approx(50.0f));
        REQUIRE(widget[1]->getAbsolutePos().y == Approx(0.0f));
    }

    SECTION("Changing the size of one child should not affter size of the other one") {
        widget[0]->setSize(ffw::guiPercent(20.0f), ffw::guiPercent(100.0f));
        // the other child stays at X: 50% Y: 100%

        TEST_UPDATE_AND_RENDER;

        REQUIRE(layout->getRealSize().x == Approx(100.0f));
        REQUIRE(layout->getRealSize().y == Approx(100.0f));

        REQUIRE(widget[0]->getRealSize().x == Approx(20.0f));
        REQUIRE(widget[0]->getRealSize().y == Approx(100.0f));

        REQUIRE(widget[1]->getRealSize().x == Approx(50.0f));
        REQUIRE(widget[1]->getRealSize().y == Approx(100.0f));
    }

    SECTION("Changing the size of one child should affter position of the other one") {
        widget[0]->setSize(ffw::guiPercent(20.0f), ffw::guiPercent(100.0f));
        // the other child stays at X: 50% Y: 100%

        TEST_UPDATE_AND_RENDER;

        REQUIRE(layout->getRealSize().x == Approx(100.0f));
        REQUIRE(layout->getRealSize().y == Approx(100.0f));

        REQUIRE(widget[0]->getAbsolutePos().x == Approx(0.0f));
        REQUIRE(widget[0]->getAbsolutePos().y == Approx(0.0f));

        REQUIRE(widget[1]->getAbsolutePos().x == Approx(20.0f));
        REQUIRE(widget[1]->getAbsolutePos().y == Approx(0.0f));
    }
}

///=============================================================================
TEST_CASE("Changing the size and position #2") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    ffw::GuiHorizontalLayout* layout[3];
    GuiWidgetNull* widget[4][2];

    layout[0] = new ffw::GuiHorizontalLayout(&gui);
    layout[0]->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout[0]->setMargin(0.0f);
    layout[0]->setPadding(0.0f);
    gui.getLayout()->addWidget(layout[0]);

    layout[1] = new ffw::GuiHorizontalLayout(&gui);
    layout[1]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(100.0f));
    layout[1]->setMargin(0.0f);
    layout[1]->setPadding(0.0f);
    layout[1]->setWrap(true);
    layout[0]->addWidget(layout[1]);

    layout[2] = new ffw::GuiHorizontalLayout(&gui);
    layout[2]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(100.0f));
    layout[2]->setMargin(0.0f);
    layout[2]->setPadding(0.0f);
    layout[2]->setWrap(true);
    layout[0]->addWidget(layout[2]);

    for(int l = 0; l < 2; l++) {
        for(int w = 0; w < 4; w++) {
            widget[w][l] = new GuiWidgetNull(&gui);
            widget[w][l]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(50.0f));
            widget[w][l]->setMargin(0.0f);
            layout[l+1]->addWidget(widget[w][l]);
        }
    }

    TEST_UPDATE_AND_RENDER;

    // First run must set both sizes
    REQUIRE(layout[1]->getRealSize().x == Approx(50.0f));
    REQUIRE(layout[1]->getRealSize().y == Approx(100.0f));

    REQUIRE(layout[2]->getRealSize().x == Approx(50.0f));
    REQUIRE(layout[2]->getRealSize().y == Approx(100.0f));
        
    for (int l = 0; l < 2; l++) {
        for (int w = 0; w < 4; w++) {
            REQUIRE(widget[w][l]->getRealSize().x == Approx(25));
            REQUIRE(widget[w][l]->getRealSize().y == Approx(50.0f));
        }
    }

    SECTION("changing the size of one child should affect position of the other one") {
        layout[1]->setSize(ffw::guiPercent(30.0f), ffw::guiPercent(100.0f));

        TEST_UPDATE_AND_RENDER;

        REQUIRE(layout[1]->getRealSize().x == Approx(30.0f));
        REQUIRE(layout[1]->getRealSize().y == Approx(100.0f));

        REQUIRE(layout[2]->getRealSize().x == Approx(50.0f));
        REQUIRE(layout[2]->getRealSize().y == Approx(100.0f));

        REQUIRE(layout[2]->getRealPos().x == Approx(30.0f));
        REQUIRE(layout[2]->getRealPos().y == Approx(0.0f));
    }

    SECTION("changing the size of one grand-child should affect its neighbours") {
        widget[0][1]->setSize(ffw::guiPercent(25), ffw::guiPercent(50.0f));

        TEST_UPDATE_AND_RENDER;

        // layout must stay same
        REQUIRE(layout[1]->getRealSize().x == Approx(50.0f));
        REQUIRE(layout[1]->getRealSize().y == Approx(100.0f));

        // relative position of the right neighbour must change
        // window's width is 100
        // left layout is 50
        // 25% from 50 is 12.5 -> to int -> 12
        REQUIRE(widget[1][1]->getRealPos().x == Approx(12.0f));
        REQUIRE(widget[1][1]->getRealPos().y == Approx(0.0f));

        // all other neighbours are unchanged
        REQUIRE(widget[2][1]->getRealPos().x == Approx(0.0f));
        REQUIRE(widget[2][1]->getRealPos().y == Approx(50.0f));

        REQUIRE(widget[3][1]->getRealPos().x == Approx(25));
        REQUIRE(widget[3][1]->getRealPos().y == Approx(50.0f));
    }
}

///=============================================================================
TEST_CASE("Changing the padding and margin") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiHorizontalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(0.0f);

    gui.getLayout()->addWidget(layout);

    GuiWidgetNull* widget[2];
    widget[0] = new GuiWidgetNull(&gui);
    widget[1] = new GuiWidgetNull(&gui);
    widget[0]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(100.0f));
    widget[1]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(100.0f));
    widget[0]->setMargin(0.0f);
    widget[0]->setPadding(0.0f);
    widget[1]->setMargin(0.0f);
    widget[1]->setPadding(0.0f);

    layout->addWidget(widget[0]);
    layout->addWidget(widget[1]);

    TEST_UPDATE_AND_RENDER;

    // getLayout should be 100x100 pixels
    // and each widget should be 50x100 pixels

    REQUIRE(layout->getRealSize().x == Approx(100.0f));
    REQUIRE(layout->getRealSize().y == Approx(100.0f));

    REQUIRE(widget[0]->getRealSize().x == Approx(50.0f));
    REQUIRE(widget[0]->getRealSize().y == Approx(100.0f));

    REQUIRE(widget[1]->getRealSize().x == Approx(50.0f));
    REQUIRE(widget[1]->getRealSize().y == Approx(100.0f));

    SECTION("changing the layout's padding") {
        layout->setPadding(5);
        // Now the inner size is 90x90 px

        TEST_UPDATE_AND_RENDER;

        REQUIRE(widget[0]->getRealSize().x == Approx(45));
        REQUIRE(widget[0]->getRealSize().y == Approx(90.0f));

        REQUIRE(widget[1]->getRealSize().x == Approx(45));
        REQUIRE(widget[1]->getRealSize().y == Approx(90.0f));

        REQUIRE(widget[0]->getRealPos().x == Approx(0.0f));
        REQUIRE(widget[0]->getRealPos().y == Approx(0.0f));

        REQUIRE(widget[1]->getRealPos().x == Approx(45));
        REQUIRE(widget[1]->getRealPos().y == Approx(0.0f));
    }

    SECTION("changing the widgets's margin") {
        widget[0]->setMargin(0.0f, 5, 0.0f, 0.0f);
        // Second widget must move to right by 5 pixels

        TEST_UPDATE_AND_RENDER;

        REQUIRE(widget[0]->getRealSize().x == Approx(50.0f));
        REQUIRE(widget[0]->getRealSize().y == Approx(100.0f));

        REQUIRE(widget[1]->getRealSize().x == Approx(50.0f));
        REQUIRE(widget[1]->getRealSize().y == Approx(100.0f));

        REQUIRE(widget[0]->getRealPos().x == Approx(0.0f));
        REQUIRE(widget[0]->getRealPos().y == Approx(0.0f));

        REQUIRE(widget[1]->getRealPos().x == Approx(55.0f));
        REQUIRE(widget[1]->getRealPos().y == Approx(0.0f));
    }
}


///=============================================================================
TEST_CASE("Changing the padding and margin #2") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    ffw::GuiHorizontalLayout* layout[3];
    GuiWidgetNull* widget[4][2];

    layout[0] = new ffw::GuiHorizontalLayout(&gui);
    layout[0]->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    layout[0]->setMargin(0.0f);
    layout[0]->setPadding(0.0f);
    gui.getLayout()->addWidget(layout[0]);

    layout[1] = new ffw::GuiHorizontalLayout(&gui);
    layout[1]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(100.0f));
    layout[1]->setMargin(0.0f);
    layout[1]->setPadding(0.0f);
    layout[1]->setWrap(true);
    layout[0]->addWidget(layout[1]);

    layout[2] = new ffw::GuiHorizontalLayout(&gui);
    layout[2]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(100.0f));
    layout[2]->setMargin(0.0f);
    layout[2]->setPadding(0.0f);
    layout[2]->setWrap(true);
    layout[0]->addWidget(layout[2]);

    for (int l = 0; l < 2; l++) {
        for (int w = 0; w < 4; w++) {
            widget[w][l] = new GuiWidgetNull(&gui);
            widget[w][l]->setSize(ffw::guiPercent(50.0f), ffw::guiPercent(50.0f));
            widget[w][l]->setMargin(0.0f);
            layout[l + 1]->addWidget(widget[w][l]);
        }
    }

    TEST_UPDATE_AND_RENDER;

    // First run must set both sizes
    REQUIRE(layout[1]->getRealSize().x == Approx(50.0f));
    REQUIRE(layout[1]->getRealSize().y == Approx(100.0f));

    REQUIRE(layout[2]->getRealSize().x == Approx(50.0f));
    REQUIRE(layout[2]->getRealSize().y == Approx(100.0f));

    for (int l = 0; l < 2; l++) {
        for (int w = 0; w < 4; w++) {
            REQUIRE(widget[w][l]->getRealSize().x == Approx(25.0f));
            REQUIRE(widget[w][l]->getRealSize().y == Approx(50.0f));
        }
    }

    SECTION("changing the padding of the main layout") {
        layout[0]->setPadding(5);

        TEST_UPDATE_AND_RENDER;

        REQUIRE(layout[1]->getRealSize().x == Approx(45.0f));
        REQUIRE(layout[1]->getRealSize().y == Approx(90.0f));

        REQUIRE(layout[2]->getRealSize().x == Approx(45.0f));
        REQUIRE(layout[2]->getRealSize().y == Approx(90.0f));

        for (int l = 0; l < 2; l++) {
            for (int w = 0; w < 4; w++) {
                REQUIRE(widget[w][l]->getRealSize().x == Approx(22.0f));
                REQUIRE(widget[w][l]->getRealSize().y == Approx(45.0f));
            }
        }
    }
}

///=============================================================================
TEST_CASE("Wrapping size #1") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiVerticalLayout(&gui);
    layout->setSize(ffw::guiPercent(100.0f), ffw::guiWrap());
    layout->setMargin(0.0f);
    layout->setPadding(0.0f);
    gui.getLayout()->addWidget(layout);

    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiWrap());
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    layout->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(layout->getRealSize().x == Approx(100.0f));
    REQUIRE(layout->getRealSize().y == Approx(0.0f));

    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(20.0f));

    TEST_UPDATE_AND_RENDER;

    REQUIRE(layout->getRealSize().x == Approx(100.0f));
    REQUIRE(layout->getRealSize().y == Approx(20.0f));

    widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(20.0f));
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    layout->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(layout->getRealSize().x == Approx(100.0f));
    REQUIRE(layout->getRealSize().y == Approx(40.0f));
}

///=============================================================================
TEST_CASE("Wrapping size #2") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto layout = new ffw::GuiHorizontalLayout(&gui);
    layout->setSize(ffw::guiWrap(), ffw::guiPercent(100.0f));
    layout->setMargin(0.0f);
    layout->setPadding(0.0f);
    gui.getLayout()->addWidget(layout);

    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiWrap(), ffw::guiPercent(100.0f));
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    layout->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(layout->getRealSize().x == Approx(0.0f));
    REQUIRE(layout->getRealSize().y == Approx(100.0f));

    widget->setSize(ffw::guiPixels(20.0f), ffw::guiPercent(100.0f));

    TEST_UPDATE_AND_RENDER;

    REQUIRE(layout->getRealSize().x == Approx(20.0f));
    REQUIRE(layout->getRealSize().y == Approx(100.0f));

    widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPixels(20.0f), ffw::guiPercent(100.0f));
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    layout->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(layout->getRealSize().x == Approx(40.0f));
    REQUIRE(layout->getRealSize().y == Approx(100.0f));
}

///=============================================================================
TEST_CASE("Wrapping size #3") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    auto outer = new ffw::GuiVerticalLayout(&gui);
    outer->setSize(ffw::guiPercent(100.0f), ffw::guiWrap());
    outer->setMargin(0.0f);
    outer->setPadding(0.0f);
    gui.getLayout()->addWidget(outer);

    auto inner = new ffw::GuiVerticalLayout(&gui);
    inner->setSize(ffw::guiPercent(100.0f), ffw::guiWrap());
    inner->setMargin(0.0f);
    inner->setPadding(0.0f);
    outer->addWidget(inner);

    auto widget = new GuiWidgetNull(&gui);
    widget->setSize(ffw::guiPercent(100.0f), ffw::guiWrap());
    widget->setMargin(0.0f);
    widget->setPadding(0.0f);
    inner->addWidget(widget);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(outer->getRealSize().x == Approx(100.0f));
    REQUIRE(outer->getRealSize().y == Approx(0.0f));

    widget->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(50.0f));

    TEST_UPDATE_AND_RENDER;

    REQUIRE(outer->getRealSize().x == Approx(100.0f));
    REQUIRE(outer->getRealSize().y == Approx(50.0f));
}

///=============================================================================
TEST_CASE("Offset") {
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

    REQUIRE(widget->getRealSize().x == Approx(80.0f));
    REQUIRE(widget->getRealSize().y == Approx(20.0f));

    REQUIRE(widget->getRealPos().x == Approx(0.0f));
    REQUIRE(widget->getRealPos().y == Approx(0.0f));

    REQUIRE(widget->getVisibleContentPos().x == Approx(0.0f));
    REQUIRE(widget->getVisibleContentPos().y == Approx(0.0f));

    REQUIRE(widget->getInnerContentPos().x == Approx(0.0f));
    REQUIRE(widget->getInnerContentPos().y == Approx(0.0f));

    REQUIRE(widget->getAbsolutePos().x == Approx(10.0f));
    REQUIRE(widget->getAbsolutePos().y == Approx(10.0f));

    layout->setOffset(ffw::Pointf(10.0f, 20.0f));

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->getRealSize().x == Approx(80.0f));
    REQUIRE(widget->getRealSize().y == Approx(20.0f));

    REQUIRE(widget->getRealPos().x == Approx(0.0f));
    REQUIRE(widget->getRealPos().y == Approx(0.0f));

    REQUIRE(layout->getVisibleContentPos().x == Approx(10.0f));
    REQUIRE(layout->getVisibleContentPos().y == Approx(10.0f));

    REQUIRE(layout->getInnerContentPos().x == Approx(20.0f));
    REQUIRE(layout->getInnerContentPos().y == Approx(30.0f));

    REQUIRE(widget->getAbsolutePos().x == Approx(20.0f));
    REQUIRE(widget->getAbsolutePos().y == Approx(30.0f));

    layout->setOffset(ffw::Pointf(10.0f, -20.0f));

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->getRealSize().x == Approx(80.0f));
    REQUIRE(widget->getRealSize().y == Approx(20.0f));

    REQUIRE(widget->getRealPos().x == Approx(0.0f));
    REQUIRE(widget->getRealPos().y == Approx(0.0f));

    REQUIRE(layout->getVisibleContentPos().x == Approx(10.0f));
    REQUIRE(layout->getVisibleContentPos().y == Approx(10.0f));

    REQUIRE(layout->getInnerContentPos().x == Approx(20.0f));
    REQUIRE(layout->getInnerContentPos().y == Approx(-10.0f));

    REQUIRE(widget->getAbsolutePos().x == Approx(20.0f));
    REQUIRE(widget->getAbsolutePos().y == Approx(-10.0f));

    gui.getLayout()->setPadding(10.0f);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widget->getRealSize().x == Approx(60.0f));
    REQUIRE(widget->getRealSize().y == Approx(15));

    REQUIRE(widget->getRealPos().x == Approx(0.0f));
    REQUIRE(widget->getRealPos().y == Approx(0.0f));

    REQUIRE(layout->getVisibleContentPos().x == Approx(10.0f));
    REQUIRE(layout->getVisibleContentPos().y == Approx(10.0f));

    REQUIRE(layout->getInnerContentPos().x == Approx(20.0f));
    REQUIRE(layout->getInnerContentPos().y == Approx(-10.0f));

    REQUIRE(widget->getAbsolutePos().x == Approx(30.0f));
    REQUIRE(widget->getAbsolutePos().y == Approx(0.0f));
}

///=============================================================================
TEST_CASE("Wrapping layout #1") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    gui.getLayout()->setWrap(false);
    gui.getLayout()->setOrientation(ffw::GuiOrientation::HORIZONTAL);

    GuiWidgetNull* widgets[4];
    for(int i = 0; i < 4; i++) {
        widgets[i] = new GuiWidgetNull(&gui);
        widgets[i]->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
        widgets[i]->setPadding(0.0f);
        widgets[i]->setMargin(0.0f);
        gui.getLayout()->addWidget(widgets[i]);
    }

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[0]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[1]->getRealPos().x == Approx(100.0f));
    REQUIRE(widgets[1]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[2]->getRealPos().x == Approx(200.0f));
    REQUIRE(widgets[2]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[3]->getRealPos().x == Approx(300.0f));
    REQUIRE(widgets[3]->getRealPos().y == Approx(0.0f));

    gui.getLayout()->setWrap(true);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[0]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[1]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[1]->getRealPos().y == Approx(25));

    REQUIRE(widgets[2]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[2]->getRealPos().y == Approx(50.0f));

    REQUIRE(widgets[3]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[3]->getRealPos().y == Approx(75));
}

///=============================================================================
TEST_CASE("Wrapping layout #2") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    gui.getLayout()->setWrap(false);
    gui.getLayout()->setOrientation(ffw::GuiOrientation::VERTICAL);

    GuiWidgetNull* widgets[4];
    for (int i = 0; i < 4; i++) {
        widgets[i] = new GuiWidgetNull(&gui);
        widgets[i]->setSize(ffw::guiPercent(25), ffw::guiPercent(100.0f));
        widgets[i]->setPadding(0.0f);
        widgets[i]->setMargin(0.0f);
        gui.getLayout()->addWidget(widgets[i]);
    }

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[0]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[1]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[1]->getRealPos().y == Approx(100.0f));

    REQUIRE(widgets[2]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[2]->getRealPos().y == Approx(200.0f));

    REQUIRE(widgets[3]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[3]->getRealPos().y == Approx(300.0f));

    gui.getLayout()->setWrap(true);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[0]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[1]->getRealPos().x == Approx(25));
    REQUIRE(widgets[1]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[2]->getRealPos().x == Approx(50.0f));
    REQUIRE(widgets[2]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[3]->getRealPos().x == Approx(75));
    REQUIRE(widgets[3]->getRealPos().y == Approx(0.0f));
}


///=============================================================================
TEST_CASE("hide and show") {
    TEST_SETUP_WINDOW(100.0f, 100.0f);

    gui.getLayout()->setOrientation(ffw::GuiOrientation::VERTICAL);

    GuiWidgetNull* widgets[4];
    for (int i = 0; i < 4; i++) {
        widgets[i] = new GuiWidgetNull(&gui);
        widgets[i]->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(25));
        widgets[i]->setPadding(0.0f);
        widgets[i]->setMargin(0.0f);
        gui.getLayout()->addWidget(widgets[i]);
    }

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[0]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[1]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[1]->getRealPos().y == Approx(25));

    REQUIRE(widgets[2]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[2]->getRealPos().y == Approx(50.0f));

    REQUIRE(widgets[3]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[3]->getRealPos().y == Approx(75));

    widgets[1]->setHidden(true);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[0]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[2]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[2]->getRealPos().y == Approx(25));

    REQUIRE(widgets[3]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[3]->getRealPos().y == Approx(50.0f));

    widgets[2]->setHidden(true);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[0]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[3]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[3]->getRealPos().y == Approx(25));

    widgets[1]->setHidden(false);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[0]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[1]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[1]->getRealPos().y == Approx(25));

    REQUIRE(widgets[3]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[3]->getRealPos().y == Approx(50.0f));

    widgets[2]->setHidden(false);

    TEST_UPDATE_AND_RENDER;

    REQUIRE(widgets[0]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[0]->getRealPos().y == Approx(0.0f));

    REQUIRE(widgets[1]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[1]->getRealPos().y == Approx(25));

    REQUIRE(widgets[2]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[2]->getRealPos().y == Approx(50.0f));

    REQUIRE(widgets[3]->getRealPos().x == Approx(0.0f));
    REQUIRE(widgets[3]->getRealPos().y == Approx(75));
}
