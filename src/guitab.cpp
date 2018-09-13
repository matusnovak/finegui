/*** This file is part of FineFramework project ***/

#include "ffw/gui/guitab.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiTabs::Button::Button(GuiWindow* context, const std::string& label, GuiWidget* targetWidget):GuiButtonToggle(context, label), targetWidget(targetWidget) {
    setStyle(&context->getTheme()->tabs.topBar.button, true);
    setStickyFocus();
}

///=============================================================================
void ffw::GuiTabs::Button::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->tabs.topBar.button, defaults);
}

///=============================================================================
void ffw::GuiTabs::Button::setStyle(const Button::Style* style, const bool defaults) {
    GuiButton::setStyle(&style->self);
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::GuiTabs::Content::Content(GuiWindow* context) :GuiLayout(context, ffw::GuiOrientation::FIXED) {
    setStyle(&context->getTheme()->tabs.content, true);
}

///=============================================================================
void ffw::GuiTabs::Content::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->tabs.content, defaults);
}

///=============================================================================
void ffw::GuiTabs::Content::setStyle(const Content::Style* style, const bool defaults) {
    GuiLayout::setStyle(&style->self, defaults);
}

///=============================================================================
ffw::GuiTabs::TopBar::TopBar(GuiWindow* context):GuiLayout(context, ffw::GuiOrientation::HORIZONTAL) {
    setStyle(&context->getTheme()->tabs.topBar, true);
    setWrap(true);
}

///=============================================================================
void ffw::GuiTabs::TopBar::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->tabs.topBar, defaults);
}

///=============================================================================
void ffw::GuiTabs::TopBar::setStyle(const TopBar::Style* style, const bool defaults) {
    GuiLayout::setStyle(&style->self, defaults);
    for (auto widget : getAllWidgets()) {
        auto btn = dynamic_cast<GuiTabs::Button*>(widget);
        btn->setStyle(&style->button, defaults);
    }
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::GuiTabs::GuiTabs(GuiWindow* context):GuiWidget(context) {
    bar = new GuiTabs::TopBar(context);
    content = new GuiTabs::Content(context);
    GuiWidget::addWidgetInternal(bar);
    GuiWidget::addWidgetInternal(content);

    setStyle(&context->getTheme()->tabs, true);
}

///=============================================================================
void ffw::GuiTabs::widgetEvent(const GuiEvent e) {
    if (e.type == GuiEventType::ACTION && e.data.action.value) {
        hideAllExcept(e.widget);
    }
}

///=============================================================================
void ffw::GuiTabs::hideAllExcept(GuiWidget* widget) {
    for (const auto w : bar->getAllWidgets()) {
        auto btn = dynamic_cast<GuiTabs::Button*>(w);
        if (btn == widget) {
            btn->setValue(true);
            btn->getTargetWidget()->setHidden(false);
        }
        else {
            btn->setValue(false);
            btn->getTargetWidget()->setHidden(true);
        }
        content->redraw();
    }
}

///=============================================================================
void ffw::GuiTabs::showTabByIndex(const size_t index) {
    for (size_t i = 0; i < bar->getAllWidgets().size(); i++) {
        const auto w = bar->getAllWidgets()[i];
        auto btn = dynamic_cast<GuiTabs::Button*>(w);
        if (i == index) {
            btn->setValue(true);
            btn->getTargetWidget()->setHidden(false);
        }
        else {
            btn->setValue(false);
            btn->getTargetWidget()->setHidden(true);
        }
        content->redraw();
    }
}

///=============================================================================
void ffw::GuiTabs::showTabByWidget(const GuiWidget *widget) {
    for (auto w : bar->getAllWidgets()) {
        auto btn = dynamic_cast<GuiTabs::Button*>(w);
        if (btn->getTargetWidget() == widget) {
            btn->setValue(true);
            btn->getTargetWidget()->setHidden(false);
        }
        else {
            btn->setValue(false);
            btn->getTargetWidget()->setHidden(true);
        }
        content->redraw();
    }
}

///=============================================================================
ffw::GuiTabs::Button* ffw::GuiTabs::addTab(GuiTabs::Button* button, GuiWidget* widget) {
    if (widget != nullptr) {
        button->addEventCallback(&GuiTabs::widgetEvent, this, GuiEventType::ACTION, true);
        button->setValue(bar->getAllWidgets().empty());
        widget->setHidden(!bar->getAllWidgets().empty());
        content->addWidget(widget);
        bar->addWidget(button);
    }
    return button;
}

///=============================================================================
ffw::GuiTabs::Button* ffw::GuiTabs::addTab(const std::string& label, GuiWidget* widget) {
    return addTab(new ffw::GuiTabs::Button(context, label, widget), widget);
}

///=============================================================================
void ffw::GuiTabs::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    (void)contentoffset;
    (void)contentsize;
}

///=============================================================================
void ffw::GuiTabs::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->tabs, defaults);
}

///=============================================================================
void ffw::GuiTabs::setStyle(const GuiTabs::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    bar->setStyle(&style->topBar, defaults);
    content->setStyle(&style->content, defaults);
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiTabs::getMinimumWrapSize() {
    return 0;
}